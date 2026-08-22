# Hardware

## Controller

OpenSlip currently targets the **LilyGO T-Motor**: ESP32-PICO-D4 (4 MB flash), TMC2209 stepper driver, MT6816 magnetic encoder interface, three buttons, I2C for a 0.49" OLED.

Manufacturer repo and schematic: [Xinyuan-LilyGO/T-Motor](https://github.com/Xinyuan-LilyGO/T-Motor)

That board is a **closed-loop stepper driver module**, not a complete tribometer. OpenSlip adds firmware and (soon) mechanics around it.

## Power

| Rail | Use |
| --- | --- |
| V+ / GND on the JST-XH style power connector | 5–12 V motor + board regulator. **Required** for TMC2209 UART and motion. 12 V max on many T-Motor listings — do not assume 24 V. |
| 3.3 V | ESP32, encoder, OLED. Usually derived from V+. Can be fed from a USB-TTL **3.3 V** pin for programming only. |

TMC2209 will not enumerate on UART without V+. Firmware still boots Wi‑Fi/OTA so you can recover a board that has no motor supply.

## Motor

- NEMA17 bipolar stepper, typical 1.8° / 200 steps/rev
- Firmware uses 16 microsteps → 3200 steps/rev
- Default RMS current **800 mA** (configurable). Factory T-Motor demos often use 2000 mA; that is hot and unnecessary for a mast.
- Enable pin is **active low**. OpenSlip keeps the driver **disabled** until the UI arms it.

Phase order (A+ A− B+ B−) varies by motor. Wrong order usually just runs poorly or backwards — use **Invert direction** rather than guessing current.

## Encoder (MT6816)

14-bit absolute magnetic encoder, 16384 counts/rev, SPI on the T-Motor.

The chip reads a diametric magnet on the motor (or mast) shaft. No magnet → stuck or garbage counts. Firmware treats a non-changing encoder as “not tracking” and will not closed-loop hunt forever.

**Calibration**

1. Set the mast vertical. **Set vertical zero.**
2. Move to a known angle (digital inclinometer on the mast, or a known SI).
3. **Calibrate from degrees** or **from SI** so gear ratio (mast degrees / motor degrees) is learned.

Direct drive: gear ratio = 1. A reduction gearbox or leadscrew on an adjusting wheel will be ≪ 1.

## OLED

0.49" SSD1306, 64×32, I2C.

- SDA = GPIO **22**, SCL = GPIO **21** (LilyGO T-Motor README)
- 7-bit addresses 0x3C or 0x3D
- **No backlight.** If it is working you see a tiny self-lit rectangle.

Firmware scans I2C on the normal pinout and with SDA/SCL swapped, then blinks the panel white. If the phone UI says `No I2C device`, the ESP32 never got an ACK — check VDD/GND/SDA/SCL solder before chasing software. See [oled.md](oled.md).

## Buttons (optional)

| PCB | GPIO | Firmware |
| --- | --- | --- |
| B1 | 36 | +0.01 SI |
| B2 | 34 | −0.01 SI |
| B3 | 35 | stop; long press = zero |

GPIO 34–36 are input-only (no internal pull-up). The PCB should provide pull-ups.

## Programming header

UART0 (GPIO1 TX, GPIO3 RX) plus BOOT (IO0) and RST/EN. 3.3 V. Details in [getting-started.md](getting-started.md).
