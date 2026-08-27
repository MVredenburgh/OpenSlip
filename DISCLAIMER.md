**Published:** 2026-08-27  
**Author:** Michael Vredenburgh / OpenSlip (Vantage Forensics)  
**Licenses:** Firmware and in-repo documentation AGPL-3.0. Written architecture / methods disclosure CC BY-SA 4.0. Hardware CAD, when it exists, CERN-OHL-S.

# Disclaimer

OpenSlip is experimental open hardware and software, provided **AS IS**.

## Not a certified instrument

OpenSlip is **not ASTM certified**, **not ANSI certified**, and not certified by any other body. A slip index or penetrometer trace produced by this machine is a function of measured geometry and a documented method. It is **not** automatically comparable to a reading from a commercial tribometer, a published safety guideline, or a courtroom exhibit. Those comparisons require a documented method, a prepared test foot, a validated machine, and professional judgment that this project does not supply.

## Not a legal-opinion instrument

Nothing in this repository, the firmware, the CSV log, or the architecture disclosure is legal advice, engineering certification, or a determination that a walking surface is safe or unsafe. OpenSlip is **not by itself a sufficient basis for a legal opinion**. If you are investigating an injury, specifying a floor, or writing a report that others will rely on, use instruments and methods appropriate to that duty and say clearly what you used.

## Not a clone

OpenSlip is an independent project. It is not affiliated with, endorsed by, or derived from any commercial tribometer brand. English XL **principles** (variable incidence, distal weight, heel-strike) are adapted as public physics; utility patents covering that family are understood to have expired. Appearance, branding, trade dress, and copyrighted manuals are **not** copied.

## Hazards

- **Power:** 5–12 V on the motor supply can deliver several amps. The worked example uses a 65 W USB-C PD bank and a 12 V trigger cable. Reverse polarity, shorted phases, and 5 V logic on 3.3 V UART pins can destroy the board.
- **Motion:** A NEMA 17 on a 310 mm Tr8x8 can pinch fingers and drive a mast or probe into a hard stop. Leave **Enable motor** off until the mechanism is clear.
- **Test surfaces:** Wet, oily, or contaminated floors are slip hazards for the operator as well as the meter.
- **Travel / screening:** Detach the PD pack (method M4). Exact carrier rules vary; pack-down is mechanical, not legal advice about what any airline will accept.
- **CO₂ / pneumatics / solenoids** (later-phase actuation): cartridges, regulators, and flying test feet are real injury risks.

## Data

CSV logs are raw operator-tagged events. They are not cleaned, not averaged, and not a complete uncertainty budget. Firmware version, encoder identity (hinge AS5600 vs any other sensor), contaminant, facing, and actuation method belong with any published number.

## Affiliation

OpenSlip is not affiliated with commercial tribometer brands, LilyGO (except as a customer of their published T-Motor board), ASTM, ANSI, or any certification body.
