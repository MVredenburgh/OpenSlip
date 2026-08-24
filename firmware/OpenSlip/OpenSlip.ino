// OpenSlip — open walkway traction meter firmware
// Copyright (C) 2026 Michael Vredenburgh and OpenSlip contributors
// SPDX-License-Identifier: AGPL-3.0-or-later
// Source: https://github.com/MVredenburgh/OpenSlip

#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>
#include <ESPmDNS.h>
#include <ArduinoOTA.h>
#include <Update.h>
#include <DNSServer.h>
#include <Preferences.h>
#include <SPI.h>
#include <Wire.h>
#include <math.h>
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif
#include <TMCStepper.h>
#include <AccelStepper.h>
#include <OneButton.h>
#include <U8g2lib.h>
#include "webpage.h"

static const char *kVersion = "0.2.0";
static const char *kBuild = __DATE__ " " __TIME__;
static const char *kApSsid = "OpenSlip";
static const char *kApPass = "openslip";
static const char *kOtaPass = "openslip";
static const char *kHost = "openslip";

#define R_SENSE 0.11f
#define EN_PIN 2
#define DIR_PIN 18
#define STEP_PIN 23
#define CLK_PIN 19
#define SPREAD_PIN 4
#define SW_RX 26
#define SW_TX 27
#define BTN1 36
#define BTN2 34
#define BTN3 35
#define SPI_MT_CS 15
#define SPI_CLK 14
#define SPI_MISO 12
#define SPI_MOSI 13
#define IIC_SCL 21
#define IIC_SDA 22
#define ENC_CPR 16384
#define MOTOR_STEPS_REV 3200

HardwareSerial SerialDriver(1);
TMC2209Stepper drv00(&SerialDriver, R_SENSE, 0b00);
TMC2209Stepper drv01(&SerialDriver, R_SENSE, 0b01);
TMC2209Stepper drv10(&SerialDriver, R_SENSE, 0b10);
TMC2209Stepper drv11(&SerialDriver, R_SENSE, 0b11);
TMC2209Stepper *driver = nullptr;
uint8_t tmcAddr = 0xFF;

AccelStepper stepper(AccelStepper::DRIVER, STEP_PIN, DIR_PIN);
OneButton button1(BTN1, true, false);
OneButton button2(BTN2, true, false);
OneButton button3(BTN3, true, false);
U8G2_SSD1306_64X32_1F_F_HW_I2C u8g2(U8G2_R0, U8X8_PIN_NONE, IIC_SCL, IIC_SDA);
U8G2_SSD1306_64X32_1F_F_HW_I2C u8g2swap(U8G2_R0, U8X8_PIN_NONE, IIC_SDA, IIC_SCL);
U8G2 *disp = &u8g2;
SPIClass MT6816;
WebServer server(80);
DNSServer dns;
Preferences prefs;

struct Cfg {
  float gear = 1.0f;
  bool invert = false;
  uint16_t rmsMa = 800;
  int zeroEnc = 0;
  String ssid;
  String wifiPass;
} cfg;

struct Reading {
  char dir;
  char result[8];
  float si;
  float deg;
};

Reading readings[48];
uint8_t nReadings = 0;

int lastEnc = 0;
int encAtMoveStart = 0;
float targetSi = 0;
bool moving = false;
bool motorArmed = false;
bool encoderLive = false;
uint32_t moveDeadline = 0;
uint32_t moveStartMs = 0;
bool otaBusy = false;
bool oledOk = false;
char staIp[16] = "0.0.0.0";
char statusMsg[96] = "OpenSlip 0.2.0 — motor disabled until enabled";
char oledInfo[96] = "OLED not scanned yet";
uint32_t oledBlinkUntil = 0;

static void setMsg(const char *s) {
  strncpy(statusMsg, s, sizeof(statusMsg) - 1);
  statusMsg[sizeof(statusMsg) - 1] = 0;
  Serial.println(statusMsg);
}

static float degToSi(float deg) {
  return tanf(deg * (float)M_PI / 180.0f);
}
static float siToDeg(float si) {
  return atanf(si) * 180.0f / (float)M_PI;
}
static int wrap14(int v) {
  v %= ENC_CPR;
  if (v < 0) v += ENC_CPR;
  return v;
}
static int signedDelta(int now, int zero) {
  int d = wrap14(now) - wrap14(zero);
  if (d > ENC_CPR / 2) d -= ENC_CPR;
  if (d < -ENC_CPR / 2) d += ENC_CPR;
  return d;
}

int mt6816Read() {
  uint16_t temp[2];
  digitalWrite(SPI_MT_CS, LOW);
  MT6816.beginTransaction(SPISettings(400000, MSBFIRST, SPI_MODE3));
  temp[0] = MT6816.transfer16(0x8300) & 0xFF;
  MT6816.endTransaction();
  digitalWrite(SPI_MT_CS, HIGH);
  digitalWrite(SPI_MT_CS, LOW);
  MT6816.beginTransaction(SPISettings(400000, MSBFIRST, SPI_MODE3));
  temp[1] = MT6816.transfer16(0x8400) & 0xFF;
  MT6816.endTransaction();
  digitalWrite(SPI_MT_CS, HIGH);
  int v = (int)((temp[0] << 6) | (temp[1] >> 2));
  if (v != lastEnc) encoderLive = true;
  lastEnc = v;
  return lastEnc;
}

float mastDeg() {
  float motorDeg = signedDelta(mt6816Read(), cfg.zeroEnc) * (360.0f / ENC_CPR);
  if (cfg.invert) motorDeg = -motorDeg;
  return motorDeg * cfg.gear;
}

float slipIndex() {
  float d = mastDeg();
  if (d < 0) d = 0;
  return degToSi(d);
}

float stepsPerDeg() {
  float g = cfg.gear == 0 ? 1.0f : cfg.gear;
  return (MOTOR_STEPS_REV / 360.0f) / g;
}

void saveCfg() {
  prefs.begin("oslip", false);
  prefs.putFloat("gear", cfg.gear);
  prefs.putBool("inv", cfg.invert);
  prefs.putUShort("rms", cfg.rmsMa);
  prefs.putInt("zero", cfg.zeroEnc);
  prefs.putString("ssid", cfg.ssid);
  prefs.putString("wpass", cfg.wifiPass);
  prefs.end();
}

void loadCfg() {
  prefs.begin("oslip", true);
  cfg.gear = prefs.getFloat("gear", 1.0f);
  cfg.invert = prefs.getBool("inv", false);
  cfg.rmsMa = prefs.getUShort("rms", 800);
  cfg.zeroEnc = prefs.getInt("zero", 0);
  cfg.ssid = prefs.getString("ssid", "");
  cfg.wifiPass = prefs.getString("wpass", "");
  prefs.end();
}

void applyCurrent() {
  if (!driver) return;
  uint16_t ma = constrain(cfg.rmsMa, 200, 2000);
  driver->rms_current(ma, 0.5f);
}

void scanTmc() {
  TMC2209Stepper *cands[4] = {&drv00, &drv01, &drv10, &drv11};
  for (uint8_t a = 0; a < 4; a++) {
    cands[a]->begin();
    delay(20);
    uint8_t ver = cands[a]->version();
    uint8_t before = cands[a]->IFCNT();
    cands[a]->pdn_disable(true);
    uint8_t after = cands[a]->IFCNT();
    Serial.printf("TMC addr 0b%u%u VER=0x%X IFCNT %u->%u\n", (a >> 1) & 1, a & 1, ver, before, after);
    if (ver == 0x21 && after != before) {
      driver = cands[a];
      tmcAddr = a;
      break;
    }
  }
}

void motorInit() {
  pinMode(CLK_PIN, OUTPUT);
  pinMode(SPREAD_PIN, OUTPUT);
  digitalWrite(CLK_PIN, LOW);
  digitalWrite(SPREAD_PIN, HIGH);
  pinMode(EN_PIN, OUTPUT);
  pinMode(STEP_PIN, OUTPUT);
  pinMode(DIR_PIN, OUTPUT);
  digitalWrite(EN_PIN, HIGH);

  SerialDriver.begin(115200, SERIAL_8N1, SW_RX, SW_TX);
  delay(50);
  scanTmc();
  if (driver) {
    driver->begin();
    driver->pdn_disable(true);
    driver->toff(5);
    driver->microsteps(16);
    driver->en_spreadCycle(false);
    driver->pwm_autoscale(true);
    applyCurrent();
    Serial.printf("TMC2209 ready, address %u\n", tmcAddr);
  } else {
    Serial.println("TMC2209 not found (need 5-12V on V+). WiFi/OTA still work.");
  }

  stepper.setMaxSpeed(600);
  stepper.setAcceleration(1500);
  stepper.setEnablePin(EN_PIN);
  stepper.setPinsInverted(false, false, true);
  stepper.disableOutputs();
}

void setArmed(bool on) {
  motorArmed = on;
  if (on) {
    stepper.enableOutputs();
    applyCurrent();
    setMsg("Motor enabled");
  } else {
    moving = false;
    stepper.stop();
    stepper.disableOutputs();
    setMsg("Motor disabled");
  }
}

bool motionOk() {
  if (otaBusy) {
    setMsg("OTA in progress");
    return false;
  }
  if (!motorArmed) {
    setMsg("Enable motor first");
    return false;
  }
  if (!driver) {
    setMsg("TMC2209 not found — 5-12V on V+ and motor connector");
    return false;
  }
  return true;
}

void startMoveToSi(float si) {
  if (!motionOk()) return;
  si = constrain(si, 0.0f, 1.15f);
  targetSi = si;
  moving = true;
  moveStartMs = millis();
  moveDeadline = millis() + 15000;
  encAtMoveStart = mt6816Read();
}

void serviceMove() {
  if (!moving || otaBusy || !motorArmed) return;
  if ((int32_t)(millis() - moveDeadline) > 0) {
    moving = false;
    stepper.stop();
    setMsg("Move timeout");
    return;
  }
  if (!encoderLive && (millis() - moveStartMs) > 900) {
    moving = false;
    stepper.stop();
    setMsg("Encoder not tracking — magnet/sensor not mounted. Use jog after hardware is on.");
    return;
  }
  float curDeg = mastDeg();
  float tgtDeg = siToDeg(targetSi);
  float errDeg = tgtDeg - curDeg;
  if (fabsf(errDeg) < 0.15f && fabsf(slipIndex() - targetSi) < 0.004f) {
    moving = false;
    stepper.moveTo(stepper.currentPosition());
    setMsg("At target");
    return;
  }
  long steps = lroundf(errDeg * stepsPerDeg());
  if (cfg.invert) steps = -steps;
  if (steps > 250) steps = 250;
  if (steps < -250) steps = -250;
  if (stepper.distanceToGo() == 0 && steps != 0) stepper.move(steps);
}

String jsonStatus() {
  String j = "{";
  j += "\"version\":\"" + String(kVersion) + "\",";
  j += "\"build\":\"" + String(kBuild) + "\",";
  j += "\"si\":" + String(slipIndex(), 4) + ",";
  j += "\"deg\":" + String(mastDeg(), 3) + ",";
  j += "\"enc\":" + String(lastEnc) + ",";
  j += "\"target\":" + String(targetSi, 3) + ",";
  j += "\"moving\":" + String(moving ? "true" : "false") + ",";
  j += "\"armed\":" + String(motorArmed ? "true" : "false") + ",";
  j += "\"encLive\":" + String(encoderLive ? "true" : "false") + ",";
  j += "\"tmcOk\":" + String(driver ? "true" : "false") + ",";
  j += "\"oledOk\":" + String(oledOk ? "true" : "false") + ",";
  j += "\"oledInfo\":\"" + String(oledInfo) + "\",";
  j += "\"msg\":\"" + String(statusMsg) + "\",";
  j += "\"tmc\":";
  if (driver) j += "\"ok addr " + String(tmcAddr) + "\"";
  else j += "\"not found\"";
  j += ",\"gear\":" + String(cfg.gear, 4);
  j += ",\"invert\":" + String(cfg.invert ? "true" : "false");
  j += ",\"rms\":" + String(cfg.rmsMa);
  j += ",\"ip\":\"" + String(staIp) + "\"";
  j += ",\"ap\":\"" + WiFi.softAPIP().toString() + "\"";
  j += ",\"readings\":[";
  for (uint8_t i = 0; i < nReadings; i++) {
    if (i) j += ",";
    j += "{\"dir\":\"";
    j += readings[i].dir;
    j += "\",\"si\":";
    j += String(readings[i].si, 3);
    j += ",\"deg\":";
    j += String(readings[i].deg, 2);
    j += ",\"result\":\"";
    j += readings[i].result;
    j += "\"}";
  }
  j += "]}";
  return j;
}

void handleStatus() { server.send(200, "application/json", jsonStatus()); }

void handleGoto() {
  if (server.hasArg("si")) startMoveToSi(server.arg("si").toFloat());
  handleStatus();
}
void handleNudge() {
  float dsi = server.hasArg("dsi") ? server.arg("dsi").toFloat() : 0.01f;
  startMoveToSi(constrain(slipIndex() + dsi, 0.0f, 1.15f));
  handleStatus();
}
void handleJog() {
  if (!motionOk()) {
    handleStatus();
    return;
  }
  int dir = server.hasArg("dir") ? server.arg("dir").toInt() : 1;
  long s = 40 * (dir >= 0 ? 1 : -1);
  if (cfg.invert) s = -s;
  stepper.move(s);
  handleStatus();
}
void handleArm() {
  setArmed(server.hasArg("on") && server.arg("on").toInt() != 0);
  handleStatus();
}
void handleOledTest() {
  oledBlinkUntil = millis() + 15000;
  setMsg("OLED white blink 15s — look for a tiny lit rectangle");
  handleStatus();
}
void handleStop() {
  moving = false;
  stepper.stop();
  handleStatus();
}
void handleZero() {
  cfg.zeroEnc = mt6816Read();
  saveCfg();
  targetSi = 0;
  moving = false;
  handleStatus();
}
void handleCalSi() {
  float si = server.arg("si").toFloat();
  if (si > 0.02f) {
    float wantDeg = siToDeg(si);
    int d = abs(signedDelta(mt6816Read(), cfg.zeroEnc));
    float motorDeg = d * (360.0f / ENC_CPR);
    if (motorDeg > 0.05f) {
      cfg.gear = wantDeg / motorDeg;
      saveCfg();
    }
  }
  handleStatus();
}
void handleCalDeg() {
  float wantDeg = server.arg("deg").toFloat();
  int d = abs(signedDelta(mt6816Read(), cfg.zeroEnc));
  float motorDeg = d * (360.0f / ENC_CPR);
  if (wantDeg > 0.2f && motorDeg > 0.05f) {
    cfg.gear = wantDeg / motorDeg;
    saveCfg();
  }
  handleStatus();
}
void handleConfig() {
  if (server.hasArg("gear")) cfg.gear = constrain(server.arg("gear").toFloat(), 0.01f, 20.0f);
  if (server.hasArg("invert")) cfg.invert = server.arg("invert").toInt() != 0;
  if (server.hasArg("rms")) {
    cfg.rmsMa = server.arg("rms").toInt();
    applyCurrent();
  }
  saveCfg();
  handleStatus();
}
void handleRecord() {
  if (nReadings >= 48) nReadings = 0;
  Reading &r = readings[nReadings++];
  r.dir = server.hasArg("dir") && server.arg("dir").length() ? server.arg("dir")[0] : 'N';
  r.si = slipIndex();
  r.deg = mastDeg();
  String res = server.hasArg("result") ? server.arg("result") : "hold";
  res.toCharArray(r.result, sizeof(r.result));
  handleStatus();
}
void handleClear() {
  nReadings = 0;
  handleStatus();
}
void handleCsv() {
  String csv = "dir,si,deg,result\n";
  for (uint8_t i = 0; i < nReadings; i++) {
    csv += readings[i].dir;
    csv += ",";
    csv += String(readings[i].si, 3);
    csv += ",";
    csv += String(readings[i].deg, 2);
    csv += ",";
    csv += readings[i].result;
    csv += "\n";
  }
  server.sendHeader("Content-Disposition", "attachment; filename=openslip_readings.csv");
  server.send(200, "text/csv", csv);
}
void handleWifi() {
  if (server.hasArg("ssid")) cfg.ssid = server.arg("ssid");
  if (server.hasArg("pass")) cfg.wifiPass = server.arg("pass");
  saveCfg();
  if (cfg.ssid.length()) WiFi.begin(cfg.ssid.c_str(), cfg.wifiPass.c_str());
  handleStatus();
}

void handleUpdateGet() { server.send_P(200, "text/html", PAGE_UPDATE); }

void handleUpdatePost() {
  if (server.arg("pass") != String(kOtaPass)) {
    server.send(401, "text/plain", "bad password");
    return;
  }
  server.sendHeader("Connection", "close");
  server.send(200, "text/plain", Update.hasError() ? "FAIL" : "OK - rebooting. Rejoin OpenSlip Wi-Fi and check version.");
  delay(500);
  ESP.restart();
}

void handleUpdateUpload() {
  HTTPUpload &upload = server.upload();
  if (upload.status == UPLOAD_FILE_START) {
    otaBusy = true;
    moving = false;
    digitalWrite(EN_PIN, HIGH);
    if (!Update.begin(UPDATE_SIZE_UNKNOWN)) Update.printError(Serial);
  } else if (upload.status == UPLOAD_FILE_WRITE) {
    if (Update.write(upload.buf, upload.currentSize) != upload.currentSize) Update.printError(Serial);
  } else if (upload.status == UPLOAD_FILE_END) {
    if (!Update.end(true)) Update.printError(Serial);
  }
}

void setupWifi() {
  WiFi.mode(WIFI_AP_STA);
  WiFi.setHostname(kHost);
  WiFi.softAP(kApSsid, kApPass);
  dns.start(53, "*", WiFi.softAPIP());
  if (cfg.ssid.length()) WiFi.begin(cfg.ssid.c_str(), cfg.wifiPass.c_str());
  MDNS.begin(kHost);

  server.on("/", []() { server.send_P(200, "text/html", PAGE_INDEX); });
  server.on("/api/status", handleStatus);
  server.on("/api/goto", HTTP_POST, handleGoto);
  server.on("/api/nudge", HTTP_POST, handleNudge);
  server.on("/api/jog", HTTP_POST, handleJog);
  server.on("/api/arm", HTTP_POST, handleArm);
  server.on("/api/oledtest", HTTP_POST, handleOledTest);
  server.on("/api/stop", HTTP_POST, handleStop);
  server.on("/api/zero", HTTP_POST, handleZero);
  server.on("/api/cal_si", HTTP_POST, handleCalSi);
  server.on("/api/cal_deg", HTTP_POST, handleCalDeg);
  server.on("/api/config", HTTP_POST, handleConfig);
  server.on("/api/record", HTTP_POST, handleRecord);
  server.on("/api/clear", HTTP_POST, handleClear);
  server.on("/api/readings.csv", handleCsv);
  server.on("/api/wifi", HTTP_POST, handleWifi);
  server.on("/update", HTTP_GET, handleUpdateGet);
  server.on("/update", HTTP_POST, handleUpdatePost, handleUpdateUpload);
  server.onNotFound([]() { server.send_P(200, "text/html", PAGE_INDEX); });
  server.begin();

  ArduinoOTA.setHostname(kHost);
  ArduinoOTA.setPassword(kOtaPass);
  ArduinoOTA.onStart([]() {
    otaBusy = true;
    moving = false;
    digitalWrite(EN_PIN, HIGH);
  });
  ArduinoOTA.begin();
}

static int i2cScan(int sda, int scl, uint8_t *found, int maxFound) {
  Wire.end();
  Wire.begin(sda, scl);
  Wire.setClock(50000);
  delay(30);
  int n = 0;
  for (uint8_t a = 1; a < 127; a++) {
    Wire.beginTransmission(a);
    if (Wire.endTransmission() == 0 && n < maxFound) found[n++] = a;
  }
  Serial.printf("I2C SDA=%d SCL=%d devices=%d", sda, scl, n);
  for (int i = 0; i < n; i++) Serial.printf(" 0x%02X", found[i]);
  Serial.println();
  return n;
}

static bool addrIsOled(uint8_t a) { return a == 0x3C || a == 0x3D; }

void oledFill(bool on) {
  if (!disp) return;
  disp->clearBuffer();
  if (on) disp->drawBox(0, 0, 64, 32);
  disp->sendBuffer();
}

void updateOled() {
  if (!oledOk || !disp) return;
  if ((int32_t)(millis() - oledBlinkUntil) < 0) {
    oledFill(((millis() / 400) % 2) == 0);
    return;
  }
  disp->clearBuffer();
  disp->setFont(u8g2_font_6x10_tf);
  disp->setCursor(0, 10);
  disp->print("SI ");
  disp->print(slipIndex(), 2);
  disp->setCursor(0, 21);
  disp->print(mastDeg(), 1);
  disp->print(" deg");
  disp->setCursor(0, 32);
  disp->print(motorArmed ? "ARM" : "off");
  disp->print(" n");
  disp->print(WiFi.softAPgetStationNum());
  disp->sendBuffer();
}

bool initOled() {
  uint8_t foundA[8], foundB[8];
  int nA = i2cScan(IIC_SDA, IIC_SCL, foundA, 8);
  int nB = i2cScan(IIC_SCL, IIC_SDA, foundB, 8);

  uint8_t addr = 0;
  bool swap = false;
  for (int i = 0; i < nA; i++) if (addrIsOled(foundA[i])) { addr = foundA[i]; }
  if (!addr) {
    for (int i = 0; i < nB; i++) if (addrIsOled(foundB[i])) { addr = foundB[i]; swap = true; }
  }
  if (!addr && nA) addr = foundA[0];
  if (!addr && nB) { addr = foundB[0]; swap = true; }

  disp = swap ? (U8G2 *)&u8g2swap : (U8G2 *)&u8g2;
  if (addr) disp->setI2CAddress(addr * 2);
  disp->begin();
  disp->setBusClock(50000);
  disp->setPowerSave(0);
  disp->setContrast(255);
  disp->setFont(u8g2_font_6x10_tf);

  if (addr) {
    snprintf(oledInfo, sizeof(oledInfo), "I2C 0x%02X %s (SDA%d SCL%d)", addr, swap ? "SWAPPED pins" : "normal",
             swap ? IIC_SCL : IIC_SDA, swap ? IIC_SDA : IIC_SCL);
    oledOk = true;
  } else {
    snprintf(oledInfo, sizeof(oledInfo), "No I2C device. Check OLED VDD/GND/SDA/SCL solder");
    oledOk = false;
  }
  setMsg(oledInfo);
  oledBlinkUntil = millis() + 20000;
  if (oledOk) {
    oledFill(true);
    delay(300);
    oledFill(false);
    delay(300);
    oledFill(true);
  }
  return oledOk;
}

void onPlus() { startMoveToSi(constrain(slipIndex() + 0.01f, 0.0f, 1.15f)); }
void onMinus() { startMoveToSi(constrain(slipIndex() - 0.01f, 0.0f, 1.15f)); }
void onStop() {
  moving = false;
  stepper.stop();
}
void onZero() {
  cfg.zeroEnc = mt6816Read();
  saveCfg();
}

void setup() {
  Serial.begin(115200);
  delay(200);
  Serial.println();
  Serial.println("OpenSlip firmware " + String(kVersion));
  loadCfg();

  pinMode(SPI_MT_CS, OUTPUT);
  digitalWrite(SPI_MT_CS, HIGH);
  MT6816.begin(SPI_CLK, SPI_MISO, SPI_MOSI, SPI_MT_CS);
  mt6816Read();
  if (cfg.zeroEnc == 0) cfg.zeroEnc = lastEnc;

  oledOk = initOled();

  motorInit();
  setupWifi();

  button1.attachClick(onPlus);
  button2.attachClick(onMinus);
  button3.attachClick(onStop);
  button3.attachLongPressStart(onZero);

  Serial.printf("AP SSID %s  pass %s  http://%s\n", kApSsid, kApPass, WiFi.softAPIP().toString().c_str());
  Serial.println("OTA password: openslip   mDNS: http://openslip.local/");
}

void loop() {
  stepper.run();
  serviceMove();
  ArduinoOTA.handle();
  dns.processNextRequest();
  server.handleClient();
  button1.tick();
  button2.tick();
  button3.tick();

  static uint32_t lastUi = 0;
  if (millis() - lastUi > 300) {
    lastUi = millis();
    mt6816Read();
    updateOled();
    if (WiFi.status() == WL_CONNECTED) {
      IPAddress ip = WiFi.localIP();
      snprintf(staIp, sizeof(staIp), "%u.%u.%u.%u", ip[0], ip[1], ip[2], ip[3]);
    }
  }
  static uint32_t lastHb = 0;
  if (millis() - lastHb > 3000) {
    lastHb = millis();
    Serial.printf("v%s SI=%.3f enc=%d tmc=%s armed=%d oled=%s\n", kVersion, slipIndex(), lastEnc,
                  driver ? "ok" : "no", motorArmed, oledInfo);
  }
}
