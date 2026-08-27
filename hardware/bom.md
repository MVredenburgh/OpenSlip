**Published:** 2026-08-27  
**Author:** Michael Vredenburgh / OpenSlip (Vantage Forensics)  
**Licenses:** Firmware and in-repo documentation AGPL-3.0. Written architecture / methods disclosure CC BY-SA 4.0. Hardware CAD, when it exists, CERN-OHL-S.

Enabling disclosure: [../docs/defensive-publication.md](../docs/defensive-publication.md)  
Public firmware: https://github.com/MVredenburgh/OpenSlip

Do **not** invent part numbers, CAD filenames, or measurements beyond the worked example already given.

# Bill of materials

Two layers: (A) electronics already public in Phase 0; (B) mechanical / field architecture specified 2026-08-26, still **TBD** as shopping SKUs.

Quantities are for **one** prototype. The worked example is a **first example, not a fence**. Firmware **0.2.0** is still electronics-first (MT6816 on the board; Phase 1 hinge truth is AS5600). Not a certified instrument. Not a legal-opinion instrument.

## A. Electronics (Phase 0, already public)

From https://github.com/MVredenburgh/OpenSlip/blob/main/hardware/bom.md — controller stage.

| Item | Example | Notes |
| --- | --- | --- |
| Motion controller | LilyGO TTGO **T-Motor** | ESP32 + onboard **TMC2209** + onboard MT6816 + JST power; optional 0.49" OLED |
| USB-TTL 3.3 V | CH340 / CP2102 / FTDI | First flash only |
| Jumper wires | Dupont | First flash only |
| DC supply | 5–12 V, ≥2 A | Match motor current; 12 V typical. Do not assume 24 V |
| Stepper | NEMA 17 bipolar | Phase 1 example: **linear**, **310 mm Tr8x8** (see B) |
| Magnet (board encoder) | Diametric, for MT6816 | **Not** the mast sensor in Phase 1; motor-shaft use not yet confirmed |
| OLED (optional) | 0.49" SSD1306 64×32 | 4-pin I2C: VDD, GND, SDA, SCL. First public unit did **not ACK** |
| Heat sink | Included with many T-Motor kits | On the TMC2209 |

Firmware to flash: OpenSlip **0.2.0**, https://github.com/MVredenburgh/OpenSlip

## B. Phase 1 field stack — electronics additions

| Item | Worked example | Status |
| --- | --- | --- |
| Hinge angle encoder | **AS5600** I2C module, **pre-soldered JST SH**, diametric magnet on the hinge axis | Designed; firmware 0.2.0 does not yet treat it as \(\theta\) truth |
| I2C harness | JST-SH 4-pin to T-Motor I2C (SDA 22 / SCL 21) | Buy finished harness; solderless example |
| Field power | **65 W USB-C PD** laptop power bank | Detachable (method M4) |
| PD trigger cable | **200 cm**, USB-C PD to **12 V** on **5.5×2.1 mm** barrel, into T-Motor V+ path | Polarity must be confirmed |

## C. Mechanical — TBD list

CAD does not exist. Exact SKUs, lengths of turnbuckle, magnet diameter/thickness, print wall thickness, and fastener grades are **not frozen**. What **is** specified as the first example:

| Subsystem | Specified | Still TBD |
| --- | --- | --- |
| Print material | **PETG or ABS or ASA**. **PLA banned** for load-bearing parts | Color, infill, exact filament brand |
| Struts | Printed tubes/I-sections; **M8** threaded rod internally; nuts both ends; print in **pre-tension** (compression in the plastic) | Rod length, nut/washer SKUs, section geometry (needs CAD) |
| Main hinge | Smooth **M8 bolt** + **two 608ZZ** bearings; spacers so plastic hits **inner race only** | Bolt length, spacer thickness, Nyloc vs double-nut |
| Angle magnet | **Diametric magnet** coaxial with the hinge bolt, air gap per AS5600 datasheet | Magnet size / grade / cup geometry |
| Incidence | Hardware-store **turnbuckle, eye/jaw**; clevis brackets; **partially threaded bolts + Nyloc**; **no bearings** on those joints | Turnbuckle length / thread size |
| Adjustment wheel | **TPU-over-rigid** wheel, core stretched or clamped on the turnbuckle body | Wheel diameter, TPU Shore, hub CAD |
| Mast drive | NEMA 17 **linear stepper**, **310 mm Tr8x8** | Nut material, coupling to T-Motor, mounts (needs CAD) |
| Distal foot | Weight **on the foot** (motors/spools/metal); optional ballast cavities | Ballast type/mass, housing CAD |
| 2-DOF ankle | **M8 Heim** **or** **TPU flexure** (both in-family) | Which first build uses; Heim size variants M6/M10 also in-family |
| Cassette | Reel-to-reel; two **micro-spools**, **horizontal** axes; **thumbwheel ratchet**; **textured cam-lock** onto platen | Spool size, elastomer strip width/compound, cam CAD |
| Heel-strike spring | **Die spring** **or** **TPU block** (both in-family) | Rate, size, Shore |
| Travel envelope | About **17.3 in** retracted; about **7 in** width | How prints actually pack; handle/housing CAD |
| Visual language | Professional power tool, not a science prop | Housing CAD; avoid commercial-meter trade dress |

### Later (not required to run firmware 0.2.0)

- Mast / chassis CAD (CERN-OHL-S when it exists)
- Test-foot blank + elastomer + written prep
- Limit switches (GPIO 21/22 are I2C on this board — do not steal them without moving OLED and AS5600)
- Automated actuator (pneumatic, solenoid, or spring) — **not implemented**; named as a later phase of the same object
- Penetrometer tips (cone, flat, needle) as swappable distal heads

### Consumables when you start measuring

- Prepared test elastomer and a written prep method
- Water / contaminant protocol (wet method is a later named phase)
- Level or known-flat plate for zeroing
- Independent inclinometer for first calibration (method M5)

## D. Explicitly not in this BOM

- No CAD files (none exist; do not invent names)
- No patent numbers
- No claim that a commercial tribometer spare is a required part
- No money, vendors-as-exclusive, or unformed entities
