**Published:** 2026-08-27  
**Author:** Michael Vredenburgh / OpenSlip (Vantage Forensics)  
**Licenses:** Firmware and in-repo documentation AGPL-3.0. Written architecture / methods disclosure CC BY-SA 4.0. Hardware CAD, when it exists, CERN-OHL-S.

Enabling disclosure: [defensive-publication.md](defensive-publication.md)  
Public firmware: https://github.com/MVredenburgh/OpenSlip

# Hardware

CAD **does not exist yet**. This document is the architecture of the machine as designed (Phase 1). A person of skill can make a first unit from this text plus public firmware **0.2.0**. When CAD later appears under CERN-OHL-S, it freezes dimensions of **this** object; it is not a new invention.

Firmware **0.2.0** is still electronics-first: the T-Motor’s onboard **MT6816** is what the sketch reads today. Phase 1 hinge truth is the **AS5600**. This is not a certified instrument and not a legal-opinion instrument.

The following bill is a **first example**, not a fence. Variants (size, PETG vs ABS vs ASA, Heim vs TPU flexure, die spring vs TPU block, slip-only vs dual-purpose, other PD voltages, other lead screws, other I2C encoders) are in-family. **PLA is banned** for load-bearing parts.

## 1. Controller (already public)

**LilyGO TTGO T-Motor.** ESP32-PICO-D4, onboard **TMC2209**, optional 0.49" SSD1306 OLED, JST-style V+ power, three buttons.

Manufacturer reference: https://github.com/Xinyuan-LilyGO/T-Motor

That board is a closed-loop stepper driver module, not a complete tribometer. OpenSlip puts firmware and mechanics around it.

| Item | Phase 1 use |
| --- | --- |
| Onboard TMC2209 | Mast / penetrometer drive; StallGuard for method M2 |
| Onboard **MT6816** (SPI, 14-bit) | **Not** mast/hinge angle truth. May sit unused, or later track a motor-shaft magnet (not yet confirmed on a spinning shaft) |
| I2C (SDA GPIO 22, SCL GPIO 21) | **AS5600 hinge encoder** (angle truth) and optional OLED |
| V+ / GND JST | 5–12 V. Worked example: **12 V** from a PD trigger cable. Do not assume 24 V |
| Motor connector | NEMA 17 bipolar, 310 mm Tr8x8 in the worked example |

Firmware: OpenSlip **0.2.0**, https://github.com/MVredenburgh/OpenSlip — Wi-Fi AP `OpenSlip` / `openslip`, phone UI http://192.168.4.1, CSV, OTA. Motor stays **disabled** until armed. Default **1/16** microstep; default RMS **800 mA**. Libraries: TMCStepper, AccelStepper, U8g2, OneButton.

**Solderless field stack:** T-Motor power is JST; AS5600 is pre-soldered **JST SH**; stepper uses the T-Motor motor connector / terminals as shipped. No custom PCB required in this example. Soldered pigtails are an anticipated variant, not a different machine.

## 2. Angle truth — AS5600 on the hinge

**AS5600** 12-bit magnetic encoder on **I2C**, module with **pre-soldered JST SH**, reading a **diametric magnet** on the main hinge axis. This is the metrology for \(\theta\). Typical 7-bit address 0x36; it shares the bus with the OLED if both are present.

Do **not** treat the T-Motor MT6816 as the mast sensor in this design.

Firmware 0.2.0 still talks to the MT6816. A person of skill either extends the sketch to read the AS5600 angle register (4096 counts/rev) as \(\theta\), or records AS5600 angle alongside the existing \(SI=\tan\theta\) math. Later firmware that prefers AS5600 is a later phase of the **same** object.

**Calibration (method M5):** zero at surface-normal; map counts to a known angle with an independent inclinometer; direct-on-hinge ⇒ ratio ≈ 1. Repeat after travel and after magnet air-gap changes.

## 3. Motion and power

- **Mast actuator:** NEMA 17 bipolar **linear stepper**, **310 mm Tr8x8** (8 mm diameter, 8 mm lead per revolution). Same screw (a) changes geometry / travel collapse and (b) drives the penetrometer stroke.
- **Field power:** **65 W USB-C PD** laptop power bank + **200 cm** USB-C PD trigger cable negotiating **12 V** on a **5.5×2.1 mm** barrel into the T-Motor V+ path. The pack **detaches** for screening (method M4).
- Bench 5–12 V supply remains valid (Phase 0). Other PD trigger voltages (9 / 12 / 15 / 20 V, with or without a buck to 12 V) are in-family.

## 4. Structure

- **Print material:** PETG, ABS, or ASA. **PLA banned** for load-bearing parts (creep under pre-tension and storage).
- **Struts:** Printed tubes or I-sections with a through-bore. An **M8 threaded rod** runs internally. **Nuts on both ends** put the print into **constant compression**; the rod takes tension.
- **Main hinge:** Smooth **M8 bolt** through **two 608ZZ** bearings. **Spacers** so printed faces contact the **inner race only**, not the shield or outer race. AS5600 + diametric magnet live on this pivot. See figure F1.
- **Incidence adjuster:** Hardware-store **turnbuckle, eye/jaw**, spanning **clevis brackets**. Fasteners: **partially threaded bolts + Nyloc nuts**. **No bearings** on the turnbuckle joints in this example. Adjustment wheel = **TPU exterior stretched over a rigid core**, the core stretched or clamped over the turnbuckle body. See figure F2.
- **Travel example:** max retracted length about **17.3 in**; max width about **7 in**. Personal-item intent. Not a limit on other sizes.

## 5. Distal foot

- **Distal weight:** Motors, spools, and metal live **on the articulated foot**, not up the mast (heel-strike analogue). Optional ballast cavities.
- **2-DOF ankle:** **M8 Heim joint** (example A) or **thick TPU flexure** (example B). Locked 0-DOF foot is a debug degenerate case.
- **Reel-to-reel cassette:** Two **micro-spools**, axes **horizontal**. **Thumbwheel ratchet** advances test elastomer across a platen. **Textured cam-lock lever** clamps the strip for the strike. See figure F3. Method M3.
- **Heel-strike spring:** **Die spring** behind the platen (example A) or **TPU block** (example B).

## 6. Penetrometer (same machine)

Same NEMA 17 + 310 mm Tr8x8 drives a vertical or near-vertical stroke. **TMC2209 StallGuard** and/or measured coil current are the resistance signal. **Dynamic zero-load stroke calibration:** run a free stroke, log StallGuard/current vs position, **subtract** that curve from a loaded stroke so lead-screw friction, gravity of the moving mass, and seal drag are not reported as ground resistance. Method M2.

## 7. Figures (described without drawings)

No drawings are included. None should be invented until real CAD or photographs exist.

**F1 — Hinge / 608ZZ / AS5600.** Cross-section: smooth M8 bolt; 608ZZ; spacer; printed ear; spacer; 608ZZ; nut. Plastic contacts inner race only. AS5600 on one ear; diametric magnet on the rotating side, coaxial. Callout: angle truth; not the T-Motor MT6816.

**F2 — Turnbuckle wheel.** Eye/jaw turnbuckle between clevis brackets; partially threaded bolts + Nyloc; no bearings on those joints. Rigid hub on the turnbuckle body; TPU tire stretched over the hub.

**F3 — Distal foot + cassette + cam-lock.** Foot at the far end of the mast. M8 Heim or TPU flexure. Horizontal micro-spools, thumbwheel ratchet, textured cam-lock clamping rubber to platen. Die spring or TPU block behind platen. Distal mass.

**F4 — Lead-screw mast + T-Motor.** NEMA 17 with 310 mm Tr8x8 mounted to the T-Motor along the mast. Travel collapse (retracted ~17.3 in) vs extended penetrometer stroke.

**F5 — PD pack detached.** 65 W USB-C PD bank; 200 cm PD trigger cable; 12 V on 5.5×2.1 mm; T-Motor JST V+. Pack shown detached (screening) and attached (use).

## 8. Phase 0 electronics notes (inherit, do not contradict)

Power, microstep rationale, buttons, and programming header remain as in the public hardware doc: https://github.com/MVredenburgh/OpenSlip/blob/main/docs/hardware.md

- TMC2209 will not enumerate on UART without V+.
- Encoder (whichever chip is the truth) is the metrology, not the microstep table. Report SI to 0.01.
- OLED: 0.49" SSD1306 64×32; first public unit did **not ACK**. No backlight.
- Buttons (optional): B1 GPIO 36 +0.01 SI; B2 GPIO 34 −0.01 SI; B3 GPIO 35 stop, long press zero. GPIO 34–36 are input-only.
- Programming: UART0 (GPIO1 TX, GPIO3 RX) plus BOOT (IO0) and RST/EN. 3.3 V. First flash USB-TTL; then OTA.
- GPIO 21/22 are I2C — do not steal them for limit switches without moving OLED and AS5600.

## 9. What is not here

- No CAD files (none exist).
- No frozen mechanical SKUs (turnbuckle length, magnet diameter, exact JST part numbers) — listed as TBD in [hardware/bom.md](../hardware/bom.md).
- No claim of ASTM/ANSI certification.
- No commercial-meter trade dress.
