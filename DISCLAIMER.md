# Disclaimer

OpenSlip is experimental open hardware and software, provided **AS IS**.

## Not a certified instrument

A slip index displayed by this firmware is a function of measured (or commanded) geometry. It is **not** automatically comparable to a reading from a commercial tribometer, a published safety guideline, or a courtroom exhibit. Those comparisons require a documented method, a prepared test foot, a validated machine, and professional judgment.

## Not legal or safety advice

Nothing in this repository is legal advice, engineering certification, or a determination that a walking surface is safe or unsafe. If you are investigating an injury, specifying a floor, or writing a report that others will rely on, use instruments and methods appropriate to that duty and say clearly what you used.

## Hazards

- **Power:** 5–12 V on the motor supply can deliver several amps. Reverse polarity, shorted phases, and 5 V logic on 3.3 V UART pins can destroy the board.
- **Motion:** A NEMA17 can pinch fingers and drive a mast into a hard stop. Leave **Enable motor** off until the mechanism is clear.
- **Test surfaces:** Wet, oily, or contaminated floors are slip hazards for the operator as well as the meter.
- **CO₂ / pneumatics** (if you add them): cartridges, regulators, and flying test feet are real injury risks.

## Data

CSV logs are raw operator-tagged events. They are not cleaned, not averaged, and not a complete uncertainty budget.

## Affiliation

OpenSlip is not affiliated with Excel Tribometers, LilyGO (except as a customer of their published T-Motor board), ASTM, ANSI, or any certification body.
