# OpenSlip

**Open hardware and firmware for measuring walkway traction.**

Slip-and-fall injury is a public-health problem. The instruments that measure walkway traction are too often closed, expensive, and hard to replicate. Science works best in the open. Safety works best when more people can measure, compare, and improve.

OpenSlip is a starting point: a portable **inclined-strut / variable-incidence** traction meter you can build, flash, inspect, and improve. Angle is set with a stepper and read with a magnetic encoder. Slip index is computed as a transparent function of that angle. Results can be logged on a phone in the field. Firmware updates go over Wi‑Fi after the first USB flash.

This is an early public prototype, not a certified instrument.

## What it is

| Piece | Today |
| --- | --- |
| Controller | [LilyGO T-Motor](https://github.com/Xinyuan-LilyGO/T-Motor) (ESP32-PICO-D4, TMC2209 stepper driver, MT6816 magnetic encoder, optional 0.49" SSD1306 OLED) |
| Firmware | Arduino sketch with always-on Wi‑Fi access point, phone web UI, CSV logging, OTA updates |
| Physics | Slip index \(SI = \tan\theta\), where \(\theta\) is mast angle from vertical on a level floor |
| Protocol | Start more vertical, increase incidence until slip, record SI to 0.01, test orthogonal directions |

## What it is not

- Not a clone of any commercial tribometer
- Not ASTM/ANSI certified and not a drop-in replacement for a calibrated lab or forensic meter
- Not legal advice, and not by itself a sufficient basis for a legal opinion
- Not finished hardware: actuation of the test foot, mechanical frame, and inter-lab validation are still open work

Read [DISCLAIMER.md](DISCLAIMER.md) before you use numbers for anything that matters.

## Why open

Closed meters cannot be audited. Closed methods cannot be improved by people who were not in the room. If walkway safety is a public good, the measurement stack should be inspectable: firmware, geometry, test-foot prep, and data format.

OpenSlip is meant for:

- Researchers who want a reproducible inclined-strut platform
- Practitioners who want to experiment without a black box
- Educators and students
- Anyone who thinks safety instrumentation should be a commons

## Quick start

1. Hardware: T-Motor, NEMA17 stepper, 5–12 V supply, USB-TTL adapter for the **first** flash only. See [docs/hardware.md](docs/hardware.md).
2. Arduino IDE: ESP32 Pico Kit, partition **Minimal SPIFFS (Large APPS with OTA)**. Libraries: TMCStepper, AccelStepper, U8g2, OneButton. See [docs/getting-started.md](docs/getting-started.md).
3. Flash [firmware/OpenSlip](firmware/OpenSlip) over USB-TTL (TX/RX/GND, 3.3 V logic). Hold **BOOT**, tap **RST**, release **BOOT**, upload.
4. Power 5–12 V on V+. Join Wi‑Fi **`OpenSlip`** / password **`openslip`**. Open http://192.168.4.1
5. Later firmware: http://192.168.4.1/update (OTA password `openslip`). USB can stay in a drawer.

Motor output stays **disabled** until you tap Enable on the phone UI.

## Repository layout

```
firmware/OpenSlip/   Arduino sketch (OpenSlip.ino + webpage.h)
docs/                How to flash, measure, and debug
hardware/            Pinout and bill of materials
DISCLAIMER.md        Use and liability
CONTRIBUTING.md      How to help
```

## Current hardware status (first prototype)

| Subsystem | Status |
| --- | --- |
| ESP32 + Wi‑Fi AP + phone UI | Working |
| OTA (web upload + ArduinoOTA) | Working |
| TMC2209 UART scan and stepper enable | Working when 5–12 V is on V+ |
| MT6816 encoder read | Wired on the board; needs magnet / motor mounted |
| OLED 0.49" SSD1306 | Firmware supports it; first unit did not ACK on I2C (likely header solder/power) |
| Mast mechanics + test foot actuation | Not in this repo yet |

## Measurement, in one paragraph

On a level surface, vertical is \(SI = 0\). Tilting the strut (mast) by angle \(\theta\) from the vertical gives a horizontal/vertical force ratio \(\tan\theta\). OpenSlip reports that as **slip index** to 0.01. A value of 0.50 is \(26.57^\circ\) from vertical. Increase \(\theta\) from steep to shallow until the test foot slips; record the SI at first slip. Repeat facing north, east, south, and west when the surface may be directional. Details: [docs/measurement-protocol.md](docs/measurement-protocol.md).

## How to help

Hardware, firmware, mechanics, test-foot chemistry, wet-surface protocol, CAD, and validation data are all needed. See [CONTRIBUTING.md](CONTRIBUTING.md) and [docs/roadmap.md](docs/roadmap.md).

Open an issue. Send a pull request. Publish your builds and your raw numbers.

## License

Apache License 2.0. You can use this commercially; you must keep attribution and the patent grant. See [LICENSE](LICENSE) and [NOTICE](NOTICE).

## Trademarks

OpenSlip is an independent project. Names of commercial tribometers, test-foot materials, and standards bodies are used only to situate the science. No affiliation or endorsement is claimed.
