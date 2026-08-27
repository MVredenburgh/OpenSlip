**Published:** 2026-08-27  
**Author:** Michael Vredenburgh / OpenSlip (Vantage Forensics)  
**Licenses:** Firmware and in-repo documentation AGPL-3.0. Written architecture / methods disclosure CC BY-SA 4.0. Hardware CAD, when it exists, CERN-OHL-S.

# License map

OpenSlip uses **three** licenses on purpose. They attach to different artifacts. Default is publish. There is no closed-source carve-out contemplated by the authors.

## Table

| Artifact | License | When it applies | Today |
| --- | --- | --- | --- |
| Firmware (`firmware/OpenSlip/`, Arduino sketch, phone UI served by the device) | **GNU Affero General Public License v3.0** (AGPL-3.0 / AGPL-3.0-or-later as in the public repo) | Distributed binaries **and** network-offered modified devices (the phone UI is a network use) | **Already public** at https://github.com/MVredenburgh/OpenSlip (created 2026-08-22; relicense commit 2026-08-24, `d69b3b5552142f65696798c4063d5a07d99592ea`) |
| Existing public documentation in that repo (README, docs, CONTRIBUTING, DISCLAIMER, hardware notes) | **AGPL-3.0** (repo-wide) | Same as firmware | **Already public** |
| This documentation tree | **AGPL-3.0** | Same as other in-repo docs | **Published 2026-08-27** |
| Written architecture / methods / enabling disclosure (the defensive-publication pack) | **CC BY-SA 4.0** (Creative Commons Attribution-ShareAlike 4.0 International) | This pack | **Published 2026-08-27** — [docs/defensive-publication.md](docs/defensive-publication.md) |
| Hardware geometry / CAD (STEP, STL, source CAD, parametric models of hinge, struts, foot, cassette, wheel, PD sled) | **CERN Open Hardware Licence Version 2 — Strongly Reciprocal (CERN-OHL-S)** | When CAD exists and is published | **Does not exist yet.** The enabling text *is* the CAD-does-not-exist-yet phase of the same object. |
| NOTICE / trademark independence | Notice file, not a license grant | Always | Already public in the repo |

## What each license means here (plain language)

**AGPL-3.0 — firmware and in-repo docs.** You may use OpenSlip commercially. If you distribute a modified device, or let people use a modified version over a network (including a hosted UI that talks to the meter), you must share your corresponding source under AGPL-3.0. Do not add a closed companion app that is **required** to measure.

**CERN-OHL-S — CAD when it exists.** Reciprocal hardware license. Modifications to the covered hardware design that are conveyed must remain under CERN-OHL-S. Completing CAD of the machine already described is a later phase of the **same** object, not a new proprietary design.

**CC BY-SA 4.0 — written disclosure.** Attribution + share-alike on the enabling text (methods, architecture, figure descriptions). That pack is a separate publication from the firmware repo.

## Independence

OpenSlip is an independent project. It is not affiliated with, endorsed by, or derived from any commercial tribometer brand. Names of commercial tribometers, test-foot materials, and standards bodies are used only to situate the science. Hardware names (LilyGO T-Motor, TMC2209, MT6816, AS5600, SSD1306, NEMA 17, 608ZZ, etc.) remain the property of their manufacturers; they are documented for interoperability.

## Pointers

- Public LICENSE: https://github.com/MVredenburgh/OpenSlip/blob/main/LICENSE
- Public NOTICE: https://github.com/MVredenburgh/OpenSlip/blob/main/NOTICE
- Enabling disclosure: [docs/defensive-publication.md](docs/defensive-publication.md)
- CERN-OHL-S text (upstream): https://ohwr.org/project/cernohl
- CC BY-SA 4.0: https://creativecommons.org/licenses/by-sa/4.0/
