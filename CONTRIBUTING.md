**Published:** 2026-08-27  
**Author:** Michael Vredenburgh / OpenSlip (Vantage Forensics)  
**Licenses:** Firmware and in-repo documentation AGPL-3.0. Written architecture / methods disclosure CC BY-SA 4.0. Hardware CAD, when it exists, CERN-OHL-S.

# Contributing to OpenSlip

The goal is a **reproducible, inspectable dual-purpose tribometer and penetrometer**, and an open method people can argue about with data.

**Be prolific at every phase.** Firmware, mechanics, method, wet protocol, CAD, validation, photos of real builds — all of it is wanted. CAD-does-not-exist-yet is already a named phase; finishing CAD is completing that phase, not inventing a new machine. Same for automated foot actuation, wet protocol, two-build validation, encoder-magnet confirmation, OLED ACK, mechanical BOM, and manufacturing/QC. Those later phases are **already disclosed** as the same object. Do the work in the open rather than sitting on it.

Public firmware repository: https://github.com/MVredenburgh/OpenSlip  
Enabling disclosure: [docs/defensive-publication.md](docs/defensive-publication.md)

## New art never in a comment

If something is worth locking down — a hinge detail, a cassette geometry, a StallGuard subtract trick, a wet-film residence-time rule — it belongs in a **dated enabling pack** (disclosure + these docs), **not** in:

- a GitHub issue
- a pull-request comment
- a review bubble
- a chat thread
- a “quick question” on a forum

Do not sit the maintainer in comment threads to “discuss” unreleased geometry. Open an issue only for bring-up of **already disclosed** art (OLED I2C, TMC UART, encoder magnet on a spinning shaft, backlash on a published hinge). If you have **new** art, write a dated enabling disclosure and publish it as a dated pack — not a comment.

## PLA is banned

**PLA is banned** for load-bearing parts (struts, hinge ears, foot, cassette frame, turnbuckle hub). It creeps under sustained compression and under M8 pre-tension. Use **PETG, ABS, or ASA** (or another creep-resistant thermoplastic, or metal). PLA is acceptable only for non-structural jigs and dust covers. PRs that specify PLA for structure will be rejected.

## Ways to help (pick one)

- **Firmware:** AS5600 as hinge \(\theta\) truth, StallGuard penetrometer + zero-load subtract, motor control, UI, logging, OTA, tests. Bump `kVersion` when behavior changes. Target firmware **0.2.0** lineage at https://github.com/MVredenburgh/OpenSlip
- **Electronics:** OLED ACK, USB-TTL notes, current tuning, PD trigger bring-up. Solderless field stack is the example, not a fence. Firmware 0.2.0 is still electronics-first (MT6816 on the board; Phase 1 hinge truth is AS5600).
- **Mechanics:** hinge / 608ZZ / AS5600, pre-tensioned M8 struts, turnbuckle wheel, distal foot, reel-to-reel cassette, CAD/STEP/STL under **CERN-OHL-S** when CAD exists.
- **Method:** test-foot prep, wet vs dry, directional surfaces, uncertainty, StallGuard calibration sheets.
- **Validation:** two independent builds; reference-surface round robin; raw CSV. Do **not** claim “equivalent to” a commercial brand.
- **Docs:** photos of working builds (photograph the OpenSlip machine; do not mimic commercial trade dress).

## Ground rules

1. **No trademarked commercial-meter branding** in UI, AP names, filenames, or housings. Describe the physics (inclined strut, variable incidence, slip index, distal-weight heel-strike). Copy principles, not trade dress.
2. **Do not paste copyrighted user manuals** into the repo.
3. **Say what you measured.** A PR that adds a number should say geometry, test foot, contamination, firmware version, and encoder (AS5600 hinge vs any audit sensor).
4. **Safety first.** Default motor disabled. Do not silently raise RMS current to 2 A. Public default is 800 mA.
5. **Keep the first USB flash OTA-capable.** Partition scheme must remain an OTA layout (`min_spiffs` or equivalent).
6. **Do not invent CAD, patent numbers, or measurements** that were not built or given. If CAD is missing, say CAD is missing.
7. **Default is publish** under the license map. PRs are AGPL-3.0 for firmware/docs; CAD is CERN-OHL-S; written disclosures are CC BY-SA 4.0.

## Firmware PRs

- Target `firmware/OpenSlip/`
- Board: ESP32 Pico (T-Motor), Arduino-ESP32 2.0.x recommended
- Angle truth in Phase 1 is the **hinge AS5600**, not the onboard MT6816
- If you add libraries, list them in getting-started docs

## Hardware PRs

- Prefer STEP/STL/source CAD, not only screenshots, licensed **CERN-OHL-S**
- Include fastener list and a photo of a real print/machine
- Call out anything that must be square, stiff, or calibrated
- Inner-race-only 608ZZ stacking; printed faces must not drag the outer race
- Travel example envelope: about 17.3 in retracted, about 7 in width — not a fence on other sizes

## Issues

Use issues for: OLED I2C ACK, TMC UART, encoder magnet on shaft, mechanical backlash, protocol questions, and “I built one.”

A useful issue includes firmware version (yellow badge on the phone UI), whether V+ is powered, and whether the TMC / encoder / OLED pills are green.
