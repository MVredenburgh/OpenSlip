**Published:** 2026-08-27  
**Author:** Michael Vredenburgh / OpenSlip (Vantage Forensics)  
**Licenses:** Firmware and in-repo documentation AGPL-3.0. Written architecture / methods disclosure CC BY-SA 4.0. Hardware CAD, when it exists, CERN-OHL-S.

Public firmware repository: https://github.com/MVredenburgh/OpenSlip  
Enabling architecture disclosure (Phase 1): [docs/defensive-publication.md](docs/defensive-publication.md)

---

# OpenSlip

**Open hardware and firmware for a portable dual-purpose tribometer and penetrometer.**

OpenSlip measures walkway traction as a variable-incidence / inclined-strut meter and, on the same battery-powered stack, infers surface/ground resistance as a motorized penetrometer. Angle is read at the hinge. Slip index is a transparent function of that angle. Firmware is inspectable. CAD, when it exists, will be inspectable.

This document describes the machine **as designed** (Phase 1 architecture). Firmware 0.2.0 and the electronics-only prototype are already public. Mechanical CAD **does not exist yet**; that absence is itself a named phase of the same object (see [docs/roadmap.md](docs/roadmap.md) and the enabling disclosure).

This is not a certified instrument. It is not a legal-opinion instrument.

## Machine as designed (first example, not a fence)

One solderless, travel-sized instrument:

- **Tribometer.** Mast incidence \(\theta\) from vertical on a level floor. Distal mass on an articulated foot delivers a heel-strike-like impulse. \(SI = \tan\theta\), reported to 0.01. \(0.50\,SI = 26.57^\circ\).
- **Penetrometer.** The same NEMA 17 **310 mm Tr8x8** lead screw drives a probe or the mast into or against a surface. TMC2209 **StallGuard** (and/or coil current) is the resistance signal, minus a **zero-load stroke** so lead-screw friction is not reported as ground strength.
- **Controller.** LilyGO TTGO **T-Motor** (ESP32, onboard TMC2209, optional OLED, JST power). Flash **firmware 0.2.0** from https://github.com/MVredenburgh/OpenSlip
- **Angle truth.** **AS5600** on I2C at the **hinge** (pre-soldered JST SH, diametric magnet). The board **MT6816 is not** the mast sensor. Firmware 0.2.0 is still electronics-first and talks to the onboard MT6816.
- **Power.** **65 W USB-C PD** power bank + **200 cm** PD-to-**12 V** **5.5×2.1 mm** trigger cable. Pack **detaches** for screening (method M4).
- **Structure.** Printed struts in **PETG / ABS / ASA** (**PLA banned** for load-bearing parts), **M8** rods in constant pre-tension. Hinge = **M8 bolt + two 608ZZ** bearings. Incidence = hardware-store **turnbuckle** + **TPU-over-rigid** adjustment wheel.
- **Foot.** Distal-weight foot; **2-DOF Heim or TPU flexure**; **reel-to-reel cassette** + cam-lock; **die spring or TPU block** behind the platen.
- **Travel envelope (example).** About **17.3 in** retracted, about **7 in** width. Airline personal-item intent. Visual language: professional power tool, not a science prop.

Physics lineage: English XL **principles** adapted (variable incidence, distal weight, heel-strike). Those **utility patents are understood to have expired**. This project copies **physics**, not appearance, branding, trade dress, or any copyrighted manual. Independent of commercial tribometer brands.

Substitutions (sizes, materials, Heim vs flexure, die spring vs TPU, slip-only vs dual-purpose, other PD voltages, other lead screws, other I2C encoders) are in-family. See the enabling disclosure.

## Status

| Subsystem | Status | Where |
| --- | --- | --- |
| ESP32 Wi-Fi AP + phone UI + OTA | Working | Public firmware 0.2.0 |
| TMC2209 UART, arm/disarm, jog | Working when 5–12 V is on V+ | Public firmware 0.2.0 |
| \(SI = \tan\theta\) to 0.01, CSV | Working | Public firmware 0.2.0 |
| MT6816 on T-Motor | Wired; **not** Phase 1 mast truth; magnet-on-shaft **not yet confirmed** | Public hardware notes |
| OLED 0.49" SSD1306 | Firmware supports it; first public unit **did not ACK** on I2C | Public hardware notes |
| AS5600 on hinge as \(\theta\) truth | **Designed**; firmware 0.2.0 still talks to MT6816 | This documentation + [disclosure](docs/defensive-publication.md) |
| Dual-purpose penetrometer (StallGuard + zero-load subtract) | **Designed**; not in firmware 0.2.0 | This documentation + [disclosure](docs/defensive-publication.md) |
| Mechanical CAD (STEP/STL/source) | **Does not exist yet** | Later phase of the same object |
| Mechanical BOM (fastener/turnbuckle/magnet SKUs) | **TBD** — architecture listed, shopping SKUs not frozen | [hardware/bom.md](hardware/bom.md) |
| Wet protocol, automated foot actuation, two-build validation | Later phases, **already named** in the disclosure | [docs/roadmap.md](docs/roadmap.md) |

**Phase 0 (already public, 2026-08-22; last commit 2026-08-24):** electronics-only prototype, AGPL firmware/docs.  
**Phase 1 (this documentation + enabling disclosure, published 2026-08-27):** architecture of the machine as designed. CAD-does-not-exist-yet is still a phase. Firmware 0.2.0 remains electronics-first (MT6816 on the board; Phase 1 hinge truth is AS5600).

## Quick start (when building)

1. Read [DISCLAIMER.md](DISCLAIMER.md).
2. Electronics and flashing: public [docs/getting-started.md](https://github.com/MVredenburgh/OpenSlip/blob/main/docs/getting-started.md) and this tree’s [docs/hardware.md](docs/hardware.md). Firmware **0.2.0**.
3. Make the structure solderless (JST / JST-SH / T-Motor motor connector). **PLA is banned** for load-bearing parts.
4. Zero the **hinge** AS5600 at surface-normal. Increase \(\theta\) until slip (method M1). For penetrometer, run a zero-load stroke and subtract (method M2).
5. Full enablement text: [docs/defensive-publication.md](docs/defensive-publication.md) (also deposited as dated markdown + PDF).

Motor output stays **disabled** until the UI arms it.

## Licenses

| Work | License | Status |
| --- | --- | --- |
| Firmware and existing/public docs | **AGPL-3.0** (AGPL-3.0-or-later as in the public repo LICENSE) | Already public |
| This repository documentation | **AGPL-3.0** | Published 2026-08-27 |
| Written architecture / methods disclosure | **CC BY-SA 4.0** | Published 2026-08-27 |
| Hardware CAD (STEP, STL, source) | **CERN-OHL-S** when it exists | Does not exist yet |

Default is publish. Anyone may copy, make, use, sell, and improve the machine under those licenses. See [LICENSE-MAP.md](LICENSE-MAP.md).

## Disclaimer (short)

Not ASTM/ANSI certified. Not a legal-opinion instrument. Not a clone of any commercial tribometer. Experimental, provided AS IS. Full text: [DISCLAIMER.md](DISCLAIMER.md).

## Publication channels

The enabling disclosure is published as markdown and print PDF (dated 2026-08-27) for archival deposit. Intended first-wave venues: Zenodo (DOI; PDF + markdown), Technical Disclosure Commons, a Hackaday.io project log pointing at the DOI and GitHub, and https://github.com/MVredenburgh/OpenSlip. Not first wave: Research Disclosure; FreeCAD forum (relevant once CAD exists). Timestamp stack: Zenodo DOI, Technical Disclosure Commons, GitHub commit hash and date.

New art belongs in a dated enabling disclosure, not in a GitHub issue, pull-request comment, or chat thread.

## This tree

```
README.md
LICENSE-MAP.md
CONTRIBUTING.md
DISCLAIMER.md
docs/defensive-publication.md
docs/hardware.md
docs/measurement-protocol.md
docs/roadmap.md
hardware/bom.md
OpenSlip-defensive-publication-2026-08-27.md
OpenSlip-defensive-publication-2026-08-27.pdf
```

Firmware source remains in the public repository: https://github.com/MVredenburgh/OpenSlip
