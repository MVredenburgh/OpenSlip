# Getting started

## What you need

- LilyGO **T-Motor** (ESP32-PICO-D4, TMC2209, MT6816 footprint)
- USB-TTL adapter, **3.3 V logic** (CH340/CP2102/FTDI). The T-Motor has **no** USB-serial chip.
- Dupont / jumper wires for one programming session
- 5–12 V DC on the T-Motor **V+** connector (required for the TMC2209; also powers the ESP32 in normal use)
- Optional: 0.49" SSD1306 OLED on the I2C header, NEMA17 stepper, magnet for the MT6816

## Arduino IDE (first flash)

1. Install [Arduino IDE 2](https://www.arduino.cc/en/software).
2. Preferences → Additional boards manager URLs:

   `https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json`

3. Boards Manager: install **esp32 by Espressif Systems**. **2.0.17** is known to work. 3.x may work; if it does not, pin 2.0.17.
4. Libraries (Library Manager, or copy from the [LilyGO T-Motor `lib` folder](https://github.com/Xinyuan-LilyGO/T-Motor)):
   - TMCStepper
   - AccelStepper
   - U8g2
   - OneButton
5. Open `firmware/OpenSlip/OpenSlip.ino`.
6. Tools:
   - Board: **ESP32 Pico Kit** (or ESP32 PICO-D4)
   - Partition scheme: **Minimal SPIFFS (Large APPS with OTA)**
   - Upload speed: **115200** if jumpers are flaky; 460800+ if the adapter is solid
   - Port: the USB-TTL COM port

Do **not** use a “No OTA” partition. If you flash a no-OTA image, you need USB again to recover OTA.

## Wiring the USB-TTL (once)

Cross TX and RX. 3.3 V logic only.

| Adapter | T-Motor |
| --- | --- |
| GND | GND |
| TXD | RX (ESP32 U0RXD / GPIO3) |
| RXD | TX (ESP32 U0TXD / GPIO1) |

- If **12 V is already on V+**: do **not** also feed 5 V or 3.3 V from the adapter. GND + TX + RX only.
- If **no motor supply**: adapter **3.3 V** to board 3.3 V/VD. Never 5 V into 3.3 V.

**Do not** use the TMC2209 pads labeled RX/TX (GPIO26/27). Those are the motor-driver UART.

The board has **BOOT** and **RST** buttons:

1. Hold **BOOT**
2. Tap **RST**
3. Release **BOOT**
4. Click Upload
5. Tap **RST** to run

After a successful flash, unplug the jumpers. Further updates are wireless.

## First boot

1. Apply 5–12 V on V+.
2. Join Wi‑Fi **`OpenSlip`**, password **`openslip`**.
3. Open http://192.168.4.1 (or http://openslip.local/ if mDNS works).
4. Leave **Enable motor** off until a motor is mounted and the mast is free.

OTA: http://192.168.4.1/update — upload the **application** `.ino.bin` only, password `openslip`.

## Command-line flash (optional)

```text
arduino-cli compile --fqbn esp32:esp32:pico32:PartitionScheme=min_spiffs firmware/OpenSlip
arduino-cli upload -p COMx --fqbn esp32:esp32:pico32:PartitionScheme=min_spiffs firmware/OpenSlip
```
