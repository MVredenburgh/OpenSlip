**Published:** 2026-08-27  
**Author:** Michael Vredenburgh / OpenSlip (Vantage Forensics)  
**Licenses:** Firmware and in-repo documentation AGPL-3.0. Written architecture / methods disclosure CC BY-SA 4.0. Hardware CAD, when it exists, CERN-OHL-S.

Enabling disclosure: [defensive-publication.md](defensive-publication.md)  
Public firmware: https://github.com/MVredenburgh/OpenSlip

# Roadmap

Every item below is a later phase of the **same** OpenSlip dual-purpose machine. They are **already disclosed** in the enabling pack so that completing them cannot be recast as a separate invention. CAD-does-not-exist-yet is still a phase.

Do not treat this list as new art. **New art never goes in a comment**; if something beyond this list appears, it belongs in a new dated pack, not a GitHub issue.

## Phase table (same object)

| Phase | What it is | Status |
| --- | --- | --- |
| **P0** | Public repo created 2026-08-22; last commit 2026-08-24; firmware **0.2.0**; electronics BOM; \(SI=\tan\theta\); no CAD | **Already live** at https://github.com/MVredenburgh/OpenSlip |
| **P1** | Architecture of the machine as designed: dual-purpose, solderless, AS5600 hinge, pre-tensioned struts, cassette foot, PD travel pack. **Still no CAD.** Firmware 0.2.0 remains electronics-first (MT6816 on the board; Phase 1 hinge truth is AS5600). | This documentation + enabling disclosure. **Published 2026-08-27.** |
| **P2 — CAD** | STEP/STL/source CAD of hinge, struts, foot, cassette, wheel, PD sled, under **CERN-OHL-S** | Not started. Dimensional freeze of P1, not new physics |
| **P3 — mechanical BOM** | Fastener list, bearing list, turnbuckle size, magnet size, exact JST part names | Architecture listed; SKUs TBD |
| **P4 — AS5600 in firmware** | Public sketch reads hinge I2C as \(\theta\) truth; MT6816 optional | Firmware catching up to P1 metrology |
| **P5 — encoder magnet on shaft (MT6816)** | Diametric magnet on the motor / screw; MT6816 actually tracking (public: wired, not yet confirmed on a spinning shaft) | Open |
| **P6 — OLED ACK** | 0.49" SSD1306 ACKing on I2C (public: first unit did not ACK) | Open |
| **P7 — automated foot actuation** | GPIO/MOSFET fire pulse, solenoid / pneumatic / spring release, timestamp vs encoder in CSV | Open (named in public roadmap too) |
| **P8 — wet protocol** | Written wet-film method, residence time, contaminant recipes | Open |
| **P9 — test-foot prep** | Open prep with photographs of a real prep | Open |
| **P10 — StallGuard calibration method** | Force-approx curves, settings table | Open |
| **P11 — CSV schema** | Versioned header: firmware, encoder, SI, SG, baseline ID, facing, contaminant, actuation | Open |
| **P12 — validation / two-build** | Two independent builds; reference-surface round robin; **no** “equivalent to brand X” claim | Open |
| **P13 — soft limits in degrees** | Public roadmap item | Open |
| **P14 — second controller target** | If T-Motor stock dries up | Same mechanics, swapped brain |
| **P15 — manufacturing / QC** | Repeatable print/assembly checks, inner-race-only hinge inspection, pre-tension check, encoder air-gap check | Open |

## Inherit (public P0 checklist, still true)

From https://github.com/MVredenburgh/OpenSlip/blob/main/docs/roadmap.md — already done: ESP32 AP, phone UI, OTA; TMC2209 scan, arm/disarm, jog; MT6816 read, SI = tan(θ), CSV; OLED diagnostic (I2C scan, white blink). Still open there: OLED confirmed on a soldered panel; encoder confirmed with magnet on a spinning shaft; soft limits in degrees. Those open boxes are P5, P6, P13 above.

Public P0 also listed: mast + chassis CAD; test-foot mount / ankle; how the T-Motor couples to the mast; stiffness/backlash budget; first actuator; GPIO fire pulse without stealing I2C; actuation timestamp; written test-foot prep; wet-film protocol; reference-surface list and CSV schema; uncertainty; two independent builds; comparison data without brand-equivalence claims; optional second controller; mechanical license when CAD lands.

**License lock vs public hedge:** the public P0 roadmap hedged “CERN-OHL-W or CC-BY-SA” for CAD. **This documentation locks CAD to CERN-OHL-S.** Firmware/docs stay AGPL-3.0. Written disclosure is CC BY-SA 4.0.

## Anticipatory combinations (already in the pack)

Same machine plus: wet film / residence time; other actuators (pneumatic / solenoid / spring); closed-loop vs open; OLED vs none; gearbox vs direct; dual vs single purpose; other test-foot elastomers; other microstep settings; other screws; other I2C encoders; external load cell; folding / stay-in-place stands; any USB-C PD trigger voltage. Completing one of those is not a new invention.

## What not to do with this list

- Do not invent CAD files, patent numbers, or measurements that were not given.
- Do not dump later phases into GitHub comments “for discussion.”
- Do not claim certification or legal-opinion status as a roadmap milestone.
