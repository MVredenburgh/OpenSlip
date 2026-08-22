# Contributing to OpenSlip

The goal is a **reproducible, inspectable walkway traction meter** and an open method people can argue about with data.

## Ways to help (pick one)

- **Firmware:** motor control, encoder fusion, UI, logging, OTA, tests
- **Electronics:** OLED bring-up, USB-TTL notes, current tuning, limit switches
- **Mechanics:** mast geometry, test-foot ankle, chassis, CAD/STEP/STL
- **Method:** test-foot preparation, wet vs dry, directional surfaces, uncertainty
- **Validation:** side-by-side with other meters on published reference surfaces; share raw CSV
- **Docs:** photos of working builds, translations, accessibility of the phone UI

## Ground rules

1. **No trademarked commercial-meter branding** in UI, AP names, or filenames. Describe the physics (inclined strut, variable incidence, slip index) instead.
2. **Do not paste copyrighted user manuals** into the repo.
3. **Say what you measured.** A PR that adds a number should say geometry, test foot, contamination, and firmware version.
4. **Safety first.** Default motor disabled. Do not silently raise RMS current to 2 A.
5. **Keep the first USB flash OTA-capable.** Partition scheme must remain an OTA layout (`min_spiffs` or equivalent). A `no_ota` factory image is a trap.

## Firmware PRs

- Target `firmware/OpenSlip/`
- Bump `kVersion` when behavior changes
- Board: ESP32 Pico (T-Motor), Arduino-ESP32 2.0.x recommended
- If you add libraries, list them in `docs/getting-started.md`

## Hardware PRs

- Prefer STEP/STL/source CAD, not only screenshots
- Include fastener list and a photo of a real print/machine
- Call out anything that must be square, stiff, or calibrated

## Issues

Use issues for: OLED I2C, TMC UART, encoder magnet, mechanical backlash, protocol questions, and “I built one.”

A useful issue includes firmware version (yellow badge on the phone UI), whether V+ is powered, and whether the TMC / encoder / OLED pills are green.
