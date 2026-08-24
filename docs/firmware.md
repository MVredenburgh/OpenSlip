# Firmware notes

License: AGPL-3.0-or-later. The phone UI must keep a link to the source repository.

Sketch: `firmware/OpenSlip/`

| Constant | Default |
| --- | --- |
| Version | 0.2.0 |
| AP SSID | `OpenSlip` |
| AP password | `openslip` (8 characters, required by ESP32 AP) |
| OTA password | `openslip` |
| mDNS | `openslip.local` |
| Preferences namespace | `oslip` |

## Architecture

- Wi‑Fi **AP + STA**. The AP stays up so a phone can always reach the device in the field, even if home Wi‑Fi is wrong.
- `WebServer` on port 80, captive-style catch-all to the UI.
- `ArduinoOTA` (Arduino IDE network port) and HTTP `.bin` upload at `/update`.
- `AccelStepper` on STEP/DIR; TMC2209 configured over UART after an address scan.
- MT6816 over SPI; slip index from encoder after zero + gear ratio.
- Motor **disarmed** at boot (`EN` high).

## Closed loop

`Go to SI` and ±0.01 use encoder \(\theta\) as truth. If the encoder does not change, the move aborts instead of spinning a blind motor. Jog is open-loop and still requires **Enable motor** plus a TMC ACK.

## Partition

Must be OTA-capable (`min_spiffs` on ESP32 2.0.x Pico). The upstream T-Motor PlatformIO default `no_ota.csv` is **wrong** for this project.

## OTA binary

Upload `OpenSlip.ino.bin` (application image), not bootloader, not partitions, not a merged 0x0 dump.

## Libraries

Tested with copies from LilyGO T-Motor `lib/` plus Arduino-ESP32 2.0.17. U8g2 is large; do not vendor it unless you have a reason.
