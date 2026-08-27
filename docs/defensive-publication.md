# OpenSlip — Enabling architecture disclosure

**Published:** 2026-08-27  
**Author:** Michael Vredenburgh / OpenSlip (Vantage Forensics)  
**Licenses:** This written disclosure CC BY-SA 4.0. Firmware AGPL-3.0. Hardware CAD, when it exists, CERN-OHL-S.  
**Document type:** Defensive-publication pack (architecture disclosure, enablement-level)

This document is the public enabling disclosure. It is not a certified-instrument claim and not a legal-opinion instrument. Mechanical CAD does not exist yet. Public firmware **0.2.0** is still electronics-first (onboard MT6816; Phase 1 hinge truth is the AS5600).

---

## LICENSE BLOCK (also restated at the end)

This **written disclosure** is published under **CC BY-SA 4.0** (Creative Commons Attribution-ShareAlike 4.0 International).

| Work | License | Status |
| --- | --- | --- |
| This written architecture / methods disclosure | CC BY-SA 4.0 | **Published 2026-08-27** |
| Firmware and existing repo docs at https://github.com/MVredenburgh/OpenSlip | GNU Affero General Public License v3.0 (AGPL-3.0 / AGPL-3.0-or-later as in the repo LICENSE) | **Already public** |
| Hardware geometry / CAD (STEP, STL, source CAD) | CERN Open Hardware Licence Version 2 — Strongly Reciprocal (**CERN-OHL-S**) | **Does not exist yet.** This disclosure *is* the CAD-does-not-exist-yet phase of the same object. When CAD exists, it publishes under CERN-OHL-S. |
| NOTICE / trademark independence | See §9 and the public NOTICE | Already public in the repo |

Anyone may copy, make, use, sell, and improve the machine described here under those licenses.

---

## 0. What is already public (Phase 0) vs what this publication adds (Phase 1)

### Phase 0 — already public (do not treat as new)

Public GitHub repository: **https://github.com/MVredenburgh/OpenSlip**

| Fact | Public record |
| --- | --- |
| Created | 2026-08-22 (`created_at` 2026-08-22T16:17:55Z). Initial commit `7ad3acc109d574250c8a62a60bb5e901403fee66`, message “Initial public release of OpenSlip.” |
| Last commit as of this publication | 2026-08-24 (`pushed_at` 2026-08-24T15:08:21Z). Commit `d69b3b5552142f65696798c4063d5a07d99592ea`, message “Relicense firmware and docs to AGPL-3.0-or-later.” |
| License | AGPL-3.0 (SPDX on the repo). Firmware/docs stay AGPL-3.0. |
| Firmware | `kVersion = "0.2.0"` in `firmware/OpenSlip/OpenSlip.ino` |
| What it is | Inclined-strut / variable-incidence tribometer. Slip index \(SI = \tan\theta\), \(\theta\) = mast angle from vertical on a level floor, reported to 0.01. |
| Electronics | LilyGO T-Motor (ESP32-PICO-D4, onboard TMC2209, MT6816 magnetic encoder on the board, optional 0.49" SSD1306 OLED, JST-style power). Phone Wi-Fi AP UI, CSV logging, OTA. Electronics BOM only. |
| Mechanics | **No CAD.** Mast, chassis, and test-foot actuation are explicitly “not in this repo yet.” |
| Disclaimer | Not ASTM/ANSI certified. Not a drop-in replacement for a calibrated lab or forensic meter. Not legal advice and not by itself a sufficient basis for a legal opinion. Experimental, provided AS IS. |
| NOTICE | Independent of commercial tribometer brands. Not affiliated with, endorsed by, or derived from any commercial tribometer brand. Names of commercial tribometers are used only to situate the science. |

Public files that already enable Phase 0 (firmware + electronics + protocol sketch):

- https://github.com/MVredenburgh/OpenSlip/blob/main/README.md
- https://github.com/MVredenburgh/OpenSlip/blob/main/LICENSE
- https://github.com/MVredenburgh/OpenSlip/blob/main/NOTICE
- https://github.com/MVredenburgh/OpenSlip/blob/main/DISCLAIMER.md
- https://github.com/MVredenburgh/OpenSlip/blob/main/docs/hardware.md
- https://github.com/MVredenburgh/OpenSlip/blob/main/docs/measurement-protocol.md
- https://github.com/MVredenburgh/OpenSlip/blob/main/docs/getting-started.md
- https://github.com/MVredenburgh/OpenSlip/blob/main/docs/roadmap.md
- https://github.com/MVredenburgh/OpenSlip/blob/main/hardware/bom.md
- https://github.com/MVredenburgh/OpenSlip/blob/main/firmware/OpenSlip/OpenSlip.ino
- https://github.com/MVredenburgh/OpenSlip/blob/main/CONTRIBUTING.md

Phase 0 already teaches: ESP32 AP + phone UI + OTA; TMC2209 UART scan, arm/disarm, jog; MT6816 read; \(SI=\tan\theta\); CSV; 1/16 microstep rationale; electronics BOM; a working (draft) inclined-strut protocol; the intent that hardware CAD, when it exists, is CERN-OHL (the public roadmap hedged CERN-OHL-W or CC-BY-SA; **this pack locks the CAD license to CERN-OHL-S**).

### Phase 1 — this publication (architecture disclosure of the machine as designed)

Specified **2026-08-26**; published **2026-08-27**. This is the prior-art enabling disclosure of the same object as Phase 0, now specified as a dual-purpose portable tribometer **and** penetrometer, with a solderless field architecture, hinge-angle metrology, printed pre-tensioned structure, distal articulated test foot, reel-to-reel cassette, and airline-personal-item envelope.

**CAD still does not exist.** Publishing this text *is* the CAD-does-not-exist-yet phase. A later CAD dump is a later phase of the **same** disclosed object, not a new invention. Firmware 0.2.0 remains electronics-first: MT6816 on the board; Phase 1 hinge truth is AS5600.

---

## 1. High-level idea

**What it is.** OpenSlip is an open, portable, dual-purpose instrument: (A) a variable-incidence / inclined-strut walkway tribometer that reports slip index \(SI=\tan\theta\), and (B) a motorized penetrometer that infers ground / surface resistance from stepper-driver load while a lead screw drives a probe or the same mast into or against the surface. One battery-powered, solderless, travel-sized machine does both.

**Physics lineage, without trade dress.** The tribometer side adapts the public physics of the English XL family of variable-incidence meters: incidence (mast angle from vertical) is the independent variable; a distal mass on an articulated foot delivers a heel-strike-like impulse; slip index is a transparent function of geometry, not a closed firmware table. Those **utility patents are understood to have expired**. This project copies **physics**, not appearance, branding, trade dress, or any copyrighted manual. The machine is digitized (magnetic hinge encoder as angle truth), motorized (lead-screw mast plus phone UI), and built to fly as airline personal item. OpenSlip is an independent project. See the public NOTICE.

**Why this is prior art.** The combination — dual-purpose tribometer/penetrometer; solderless T-Motor + AS5600-on-hinge; pre-tensioned printed struts with internal M8 rods; 608ZZ hinge; hardware-store turnbuckle incidence adjuster with a TPU-over-rigid wheel; distal-weighted 2-DOF foot; reel-to-reel rubber cassette; StallGuard penetrometer with zero-load friction subtract; USB-C PD field power; ~17.3 in × ~7 in travel envelope — is in the open. A person of ordinary skill can make and use it from this text plus the already-public firmware. Later CAD, wet protocols, and automation are **later phases of this same object**, disclosed now as intended, so they cannot be fenced off as “new.”

**Who can copy it.** Anyone, commercially or not, under the licenses in the license block. Firmware modifications that are distributed or offered over a network must remain AGPL-3.0. CAD, when it exists, must remain CERN-OHL-S. This written disclosure is CC BY-SA 4.0. There is no proprietary fork contemplated by the authors.

**What it is not.** Not a certified instrument. Not a legal-opinion instrument. Not a clone of any commercial tribometer. Numbers it produces are functions of measured geometry and a documented method; they are not automatically comparable to a branded meter or a published safety threshold.

---

## 2. Worked example (first example, not a fence)

The following bill and numbers are a **first working example**. They are labeled so a skilled person can buy parts this week. Substitutions are anticipated in §4 and §6; the example is not a limitation.

### 2.1 Controller and firmware (already public, reused)

- **Controller:** LilyGO TTGO **T-Motor**, ESP32-PICO-D4, onboard **TMC2209** stepper driver, optional 0.49" SSD1306 OLED, JST-style V+ power input, three buttons. Manufacturer reference: https://github.com/Xinyuan-LilyGO/T-Motor
- **Onboard encoder chip:** **MT6816** (SPI, 14-bit, 16384 counts/rev) exists on the T-Motor. In this Phase 1 machine it is **not** the mast/hinge angle truth. It may sit unused, or later serve as a motor-shaft / redundant sensor (see §7). Angle truth is the **AS5600** on the main hinge.
- **Firmware:** OpenSlip **0.2.0**, Arduino sketch, always-on Wi-Fi AP `OpenSlip` / password `openslip`, phone UI at http://192.168.4.1, CSV logging, OTA at `/update`. Motor output stays **disabled** until the UI arms it. License AGPL-3.0. Source: https://github.com/MVredenburgh/OpenSlip/blob/main/firmware/OpenSlip/OpenSlip.ino
- **Libraries (public):** TMCStepper, AccelStepper, U8g2, OneButton.
- **Microstep (public default):** 1/16 on the T-Motor dips and over UART. Default RMS current in public firmware is 800 mA (configurable). TMC2209 enable is active-low; firmware keeps it disabled until armed.
- **Power rail on the board:** 5–12 V on V+ / GND (JST). 12 V is the typical field rail in this example. Do not assume 24 V.

### 2.2 Motion, angle truth, power (Phase 1 example)

- **Mast actuator:** NEMA 17 bipolar linear stepper with a **310 mm Tr8x8** lead screw (8 mm diameter, 8 mm lead per revolution). This screw both (a) changes geometry / stroke for tribometer setup and travel collapse, and (b) drives the penetrometer stroke.
- **Hinge-angle truth:** **AS5600** 12-bit magnetic encoder on **I2C**, module with **pre-soldered JST SH** connector, reading a **diametric magnet** on the main hinge axis. This is the metrology for \(\theta\). Do not treat the T-Motor’s MT6816 as the mast sensor in this example.
- **Field power:** **65 W USB-C PD** laptop power bank, plus a **200 cm** USB-C PD **trigger cable** that negotiates PD and presents **12 V** on a **5.5 × 2.1 mm** barrel into the T-Motor V+ pigtail (or an adapter onto the board’s JST). The pack **detaches** for screening (method M4).
- **Solderless rule (this example):** 100% solderless assembly. T-Motor power is JST; AS5600 is JST SH; stepper phases are the T-Motor’s existing motor connector / screw terminals as shipped; no custom PCBs, no field soldering.

### 2.3 Structure (Phase 1 example)

- **Print material:** PETG, ABS, or ASA. **PLA is banned** in this family because of creep under sustained compression and under pre-tension.
- **Struts:** Printed tubes or I-sections with a through-bore. An **M8 threaded rod** runs internally the length of the strut. **Nuts on both ends** put the print into **constant compression**; the rod takes tension. That is the pre-tensioned-strut method.
- **Main hinge:** A **smooth M8 bolt** through **two 608ZZ** bearings (8 mm bore, 22 mm OD, 7 mm width, standard skate bearing). **Spacers** (printed or metal) so printed faces contact the **inner race only**, not the shield or outer race. The AS5600 and its diametric magnet live on this pivot.
- **Incidence coarse/fine adjuster:** A hardware-store **turnbuckle, eye/jaw**, spanning **clevis brackets** on the two sides of the hinge. Fasteners are **partially threaded bolts + Nyloc nuts**. **No bearings** on the turnbuckle joints in this example. An **adjustment wheel** is a **TPU exterior stretched over a rigid core**, the core itself stretched or clamped over the turnbuckle body so a gloved hand can spin incidence without a wrench.
- **Envelope (travel example):** Max retracted length about **17.3 in**. Max width about **7 in**. Intended to pack as airline **personal item** and to read visually as a professional power tool, not as a science prop. PD pack detaches.

### 2.4 Test foot (Phase 1 example)

- **Distal weight:** Motors, spools, and metal live **on the articulated foot**, not up the mast, so the impulse is a heel-strike analogue with mass outboard of the contact patch. Optional **ballast cavities** in the foot print can take extra steel/lead shot or plate.
- **2-DOF ankle (example A):** **M8 Heim joint** (rose joint) giving pitch and roll. **Example B** (variant, not a fence): a **thick TPU flexure** doing the same two degrees of freedom.
- **Reel-to-reel cassette:** Two **micro-spools**, axes **horizontal**, mounted on the foot. A **thumbwheel ratchet** advances a strip of test rubber (or other elastomer) across a platen. A **textured cam-lock lever** clamps the rubber to the platen for the strike. Fresh rubber is rolled forward between tests; used rubber winds onto the take-up spool.
- **Heel-strike spring (example A):** A **die spring** behind the platen. **Example B:** a **TPU block** as the compressible element.

### 2.5 Penetrometer (Phase 1 example)

- Same NEMA 17 + 310 mm Tr8x8 drives a vertical (or near-vertical) stroke.
- **TMC2209 StallGuard** and/or measured coil current are the resistance signal.
- **Dynamic zero-load stroke calibration:** run the screw through a free (in-air or unloaded) stroke, log StallGuard / current vs position, and **subtract that curve** from a loaded stroke so lead-screw friction, gravity of the moving mass, and seal drag are not reported as ground resistance.

### 2.6 Numbers already public that this example inherits

From the public measurement protocol and hardware notes (Phase 0):

| SI | \(\theta\) from vertical |
| --- | --- |
| 0.00 | 0° |
| 0.30 | 16.70° |
| 0.50 | 26.57° |
| 1.00 | 45° |

Firmware constrains SI to about 0–1.15 in v0.2.0. Report SI to 0.01. Encoder, not step counting, is metrology. On a ramp, either level the chassis to the surface or record chassis pitch and correct; do not mix the two.

---

## 3. How to make and use (person of ordinary skill)

A person of ordinary skill is someone who can: model and 3D-print functional mechanical parts; tap/clear M8; seat 608ZZ bearings; wire JST/JST-SH without soldering (crimp or buy finished harnesses); flash an ESP32 with Arduino IDE; and run a written test method without treating the UI as a black box.

CAD files are **not required** to practice the invention. This section plus the public firmware and the worked example are enough to build a first unit. When CAD later appears, it is a convenience and a dimensional lock, not a new idea.

### 3.1 Make the structure

1. **Choose PETG, ABS, or ASA.** Do not use PLA for load-bearing parts.
2. **Print two (or more) struts** with a through-bore that clears an M8 threaded rod. Wall thickness and section are whatever the printer and buckling budget allow; the rod is the tension member. Include flats or pockets at each end for nuts and washers.
3. **Slide an M8 threaded rod** through each strut. Put washers and nuts on both ends. **Tighten until the print is in constant compression** (pre-tension). The print should not carry sustained tension; if a layer bond fails, the rod still holds length.
4. **Print hinge ears / clevises** that accept a smooth M8 bolt and that have counterbores or pockets for **608ZZ** bearings. Design (or file) **spacers** so that when the bolt is torqued, printed plastic bears on the **inner race** only.
5. **Assemble the main hinge:** 608ZZ + spacer + printed ear + spacer + 608ZZ on a smooth M8 bolt, Nyloc or double-nut. Confirm the outer races do not drag on plastic.
6. **Mount the AS5600** on one hinge ear, coaxial with the bolt, and glue or press a **diametric magnet** to the rotating side (bolt head, a printed magnet cup on the moving strut, or a shaft collar). Air gap per the AS5600 datasheet. Connect the module’s **JST SH** to the T-Motor **I2C** header (public T-Motor: SDA GPIO 22, SCL GPIO 21 — same bus as the OLED). Address is typically 0x36; if the OLED is also present, both devices share the bus.
7. **Print or buy clevis brackets** for a hardware-store **eye/jaw turnbuckle**. Attach with **partially threaded bolts and Nyloc nuts**. No bearings required on these joints. Stretch a **TPU tire** over a rigid printed (or metal) hub and press/stretch that hub onto the turnbuckle body. Spinning the wheel changes incidence.
8. **Mount the T-Motor** to the mast side of the hinge so the NEMA 17 **310 mm Tr8x8** linear screw runs along the mast. The screw provides (a) length adjustment / collapse for travel, (b) penetrometer stroke, and (c) optionally a way to set a stop or to change the distal-foot offset. Couple the NEMA 17 with the T-Motor’s motor connector. Apply 12 V from the PD trigger cable to V+.
9. **Print the distal foot** with: pockets for the micro-spools (horizontal axes); a platen; a cam-lock lever with a textured face; optional ballast cavities; and either an **M8 Heim** housing or a thick **TPU flexure** neck. Put the heavy parts (stepper if a second motor is used for the cassette, spools, metal ballast) **on the foot**.
10. **Cassette:** Wind test elastomer from supply micro-spool across the platen to take-up micro-spool. Thumbwheel ratchet on the take-up. Cam-lock clamps the strip to the platen. Behind the platen, install a **die spring** or a **TPU block** so the foot can compress on “heel strike” and then unload.
11. **Power:** Plug the 200 cm PD-to-12 V 5.5×2.1 mm trigger cable into the 65 W PD bank and into the T-Motor power path. Confirm polarity. Leave the motor **disabled** in firmware until the mechanism is clear.

No custom PCB. No solder. If a harness is missing, buy a JST-SH 4-pin I2C cable and a JST-XH (or whatever the T-Motor ships) power pigtail.

### 3.2 Flash and bring up (inherits Phase 0)

Follow the public getting-started document: https://github.com/MVredenburgh/OpenSlip/blob/main/docs/getting-started.md

- Arduino IDE, ESP32 Pico Kit, partition **Minimal SPIFFS (Large APPS with OTA)**. First flash over USB-TTL 3.3 V (TX/RX/GND; hold BOOT, tap RST). Then OTA.
- Join Wi-Fi `OpenSlip` / `openslip`. Open http://192.168.4.1
- Firmware 0.2.0 talks to the **onboard MT6816** today. Phase 1 angle truth is the **AS5600 on I2C**. A person of skill either (a) extends the public sketch to read AS5600 (standard I2C angle register) and use that counts-per-rev (4096) as \(\theta\), or (b) uses the phone UI / serial to record AS5600 angle alongside the existing SI math \(SI=\tan\theta\). The physics does not depend on which magnet encoder is wired; this disclosure makes the hinge AS5600 the intended truth so that mast-motor steps and the T-Motor’s motor-shaft chip are not the metrology chain. Later firmware that prefers AS5600 is a later phase of the **same** object (§7), not a new invention.

### 3.3 Use as a tribometer

See method **M1**. Short form: zero the hinge at surface-normal (vertical on a level floor) using the AS5600; start more vertical (low SI); deliver a heel-strike with the distal foot; if it holds, increase incidence (turnbuckle wheel and/or firmware jog) and repeat until first slip; record \(SI=\tan\theta\) to 0.01; repeat facing N/E/S/W if the surface may be directional; export CSV.

### 3.4 Use as a penetrometer

See method **M2**. Short form: collapse or reorient so the lead screw drives a tip, foot, or probe into the ground or against a surface; run a **zero-load** stroke and store StallGuard/current vs position; run a loaded stroke; subtract; report resistance vs depth. Same battery, same driver, same screw.

### 3.5 Travel

See method **M4**. Retract the 310 mm screw toward the ~17.3 in envelope; keep width under ~7 in; detach the PD pack for screening; carry as personal item.

---

## 4. Family variants

These are the same invention. Listing them is so a later filer cannot patent “OpenSlip but in ABS,” “OpenSlip but with a flexure ankle,” or “OpenSlip but bench-mounted.”

### 4.1 Size / envelope

- **Travel / personal-item** (worked example): ~17.3 in retracted, ~7 in max width.
- **Shorter:** shorter lead screw than 310 mm; envelope under typical under-seat limits of other carriers.
- **Longer / lab:** longer Tr8 screw or a two-piece mast with a joint, for larger incidence geometry or deeper penetrometer stroke. Still the same hinge, foot, and electronics.
- **Break-down:** struts that un-clevis for a smaller case, then re-pre-tension.

### 4.2 Print materials

- PETG, ABS, ASA: in-family.
- Other creep-resistant thermoplastics (PC, PC-ABS, nylon, carbon-filled PETG): in-family.
- **PLA: out of family for load-bearing parts** (creep under pre-tension and under storage). PLA may still be used for non-structural jigs and dust covers.
- Metal struts, carbon tube over M8, or hybrid print-plus-aluminum: in-family (pre-tension / inner tension-member idea survives).

### 4.3 Ankle / 2-DOF

- M8 Heim / rose joint (pitch + roll).
- Other rod-end sizes (M6, M10) and two-Heim stacks.
- Thick TPU flexure (pitch + roll in one printed neck).
- U-joint, gimbal, or stacked pivot pins.
- Locked (0-DOF) foot for a first debug build.

### 4.4 Heel-strike spring

- Die spring behind the platen.
- TPU block / lattice / bellows.
- Coil spring, Belleville stack, foam, pneumatic bumper, or no spring (rigid platen) as degenerate cases.

### 4.5 Stay-in-place vs other deployments

- **Portable field unit** (worked example): operator carries it, sets it, tests, packs.
- **Stay-in-place / bench / fixture:** the same hinge, encoder, foot, and screw, clamped or bolted to a stand, vehicle hitch, or floor jig for repeated lab use.
- **Stay-clamped cassette vs peel-off vs adhesive-backed coupons:** the cam-lock that keeps rubber in place during the strike is one embodiment; clips, vises, and one-shot adhesive coupons are variants of the same “replaceable test surface on a distal foot” idea.
- **Tripod or outrigger stay** vs free-standing distal-mass designs.

### 4.6 Dual-purpose vs single-purpose

- Dual-purpose tribometer + penetrometer (worked example).
- Slip-only (omit StallGuard subtract; still the same machine).
- Penetrometer-only (omit cassette / heel-strike; still the same machine).
- Shared electronics, swappable distal heads (tribometer foot vs cone/flat penetrometer tip).

### 4.7 Incidence adjustment

- Hardware-store turnbuckle + TPU wheel (worked example).
- Lead-screw incidence (the mast Tr8x8 itself, or a second screw across the hinge).
- Linear actuator, servo, ratchet strap, pin-in-hole coarse ladder, or fully manual.

### 4.8 Encoders and drivers

- AS5600 on the hinge (worked example).
- Other absolute magnetics on the same pivot: AS5048A/B, MT6701, TLE5012, the T-Motor’s own **MT6816** relocated or geared to the hinge, optical incremental + index, MEMS inclinometer, IMU fusion, or a digital protractor used as a check standard.
- Dual encoder: hinge AS5600 as truth **plus** MT6816 on the motor for StallGuard/motion diagnostics.

### 4.9 Power

- 65 W USB-C PD laptop bank + 200 cm PD-to-12 V 5.5×2.1 mm trigger cable (worked example).
- Any PD bank that can trigger 9 / 12 / 15 / 20 V, with or without a buck to 12 V.
- Bench 5–12 V supply (already in Phase 0 BOM).
- 3S/4S pack with a UBEC. Detachable energy source remains a feature, not a different invention.

### 4.10 Test-foot consumable path

- Reel-to-reel micro-spools, horizontal, thumbwheel ratchet, cam-lock (worked example).
- Vertical spools, cassette cartridge that drops in as a unit, single-coupon clips, Neolite / leather / rubber tiles, 3D-printed elastomeric skins.

---

## 5. Numbered methods

### M1 — Slip / traction protocol (inclined strut)

This method is already sketched in public `docs/measurement-protocol.md`. It is restated here so Phase 1 hardware (hinge AS5600, distal cassette foot, turnbuckle) is explicitly inside the method.

1. Prepare the test elastomer with a **written** prep (grit, strokes, cleaning). Publish the prep with the data when data are published.
2. Place the instrument on the walking surface. On a **level** floor, set the mast to the surface normal (vertical). **Zero** the AS5600 there. \(SI=\tan\theta\) with \(\theta=0\) at that zero.
3. Confirm against an independent inclinometer at least once per session until the machine is trusted (method M5).
4. Start **more vertical** (lower SI) than the expected slip.
5. Deliver a heel-strike: distal mass + spring (die spring or TPU block) drives the clamped cassette rubber onto the surface. Actuation may be manual (operator lets the foot fall or snaps it), spring-released, or later automated (§7). Residence time on a wet film is a first-order variable; document it.
6. If the foot **holds**, increase incidence by ~0.01 SI (turnbuckle wheel and/or motorized jog) and repeat. Always go from lower SI to higher SI.
7. On **first slip**, record SI to 0.01 and tag Slip. Tag the previous hold as No slip if useful.
8. If the surface may be directional, repeat facing north, east, south, and west.
9. Export CSV (firmware version, SI, encoder, tags). Do not treat a phone-UI average as a complete uncertainty budget.

On a **ramp**, either level the chassis into the surface frame or record chassis pitch and correct. Do not mix the two.

This method does **not** claim equivalence to any commercial tribometer.

### M2 — Penetrometer with StallGuard and zero-load subtract

1. Reconfigure or reorient the same machine so the NEMA 17 **Tr8x8** drives a probe, tip, or the foot **into or against** the material under test (soil, compacted fill, a floor covering, a coating, etc.).
2. **Zero-load calibration (dynamic, per session or per stroke family):** with the probe in air (or on a known-free slide), run a full or representative stroke at the intended speed and current. Log TMC2209 **StallGuard** (and/or RMS current, and/or `SG_RESULT`) against lead-screw position (step count and/or a stroke encoder). Store this as the **friction baseline**. It includes lead-screw efficiency, nut stiction, gravity of the moving stack, and seal drag.
3. **Loaded stroke:** repeat in the material. Log the same signals vs position.
4. **Subtract:** reported resistance\(z\) = loaded\(z\) − baseline\(z\) (interpolated to the same position). Do not report raw StallGuard as “ground strength.”
5. Optional stops: StallGuard threshold as a digital “hit hard stop / hit a stone” event; current cap as a thermal safety.
6. Report: firmware version, RMS current setting, microstep, screw lead (example: Tr8x8), speed, baseline ID, raw and subtracted traces.

The same subtract idea applies if a future phase adds an external load cell (§6, §7): the load cell can replace or audit StallGuard; the zero-load subtract still applies.

### M3 — Reel-to-reel test-foot cassette

1. Mount two micro-spools with **horizontal** axes on the distal foot.
2. Thread elastomer from supply spool across the platen to take-up spool.
3. Advance with a **thumbwheel ratchet** until unused material covers the platen.
4. Close a **textured cam-lock lever** to clamp the strip to the platen so it cannot creep during the strike.
5. Perform M1 (or a dry wipe / wet wipe as documented).
6. Release the cam-lock, ratchet fresh material, re-clamp. Used material winds onto take-up; do not reverse contaminated rubber onto the contact patch.
7. Variants in-family: drop-in cassette cartridge; vertical spools; perforated index holes; a second cam on the supply side.

### M4 — Travel / screening pack-down

1. Retract the **310 mm** lead screw (or the then-current screw) until overall length is about **17.3 in** or less.
2. Confirm max width about **7 in** (hinge ears, foot, wheel).
3. Cam-lock the cassette so the strip cannot unroll in a bag.
4. **Detach the 65 W PD pack** from the instrument. Carry the pack as an ordinary laptop power bank. The machine body then has no large lithium pack inside it.
5. Carry the body as airline **personal item**. The intended visual language is a professional power tool (housing, handle, wheel), not a laboratory jig with exposed wiring.
6. Reattach PD + 200 cm trigger cable at the site; M5 then M1 or M2.

Exact carrier rules vary; this method is the **mechanical** pack-down, not legal advice about what any airline will accept.

### M5 — Calibration

**Angle / SI**

1. Place on a known-level surface. Set hinge to surface normal. Store AS5600 reading as zero. \(SI=\tan\theta\).
2. Move to a known angle (independent digital inclinometer on the mast, or a known SI fixture). Store the mapping (counts per degree). AS5600 is 12-bit (4096 counts/rev) in the worked example; other encoders differ.
3. Optionally learn a gear ratio if a reduction exists between encoder and mast (public firmware already has a gear-ratio calibration path for the MT6816). Direct-on-hinge AS5600 ⇒ ratio ≈ 1.
4. Repeat after travel, after bearing re-pack, and whenever the magnet air gap is disturbed.

**Penetrometer baseline**

5. Run M2 step 2 (zero-load stroke) at the same speed/current as the working stroke. Invalidate the baseline if temperature, orientation (gravity vector on the screw), or nut wear changed.

**StallGuard / current**

6. Note TMC2209 `SGTHRS`, RMS current, and microstep with every subtracted trace. StallGuard is a driver-specific, speed-specific number; it is comparable only under a documented setting. A later published calibration curve (voltage, speed, screw, nut material → approximate force) is a later phase of this **same** method, not a new invention.

**System**

7. Independent inclinometer vs AS5600 vs (optional) MT6816, logged together, is the audit. Firmware version 0.2.0 and successors go in the CSV header.

### M6 — Pre-tensioned printed strut

1. Print the strut around a clearance hole for M8 (or other) rod.
2. Insert rod, washers, nuts.
3. Tighten until the polymer is in **compression** and the rod is in **tension**.
4. Use that member as a mast, a brace, or a turnbuckle-side link.
5. Re-tension after heat cycles. Do not substitute PLA.

### M7 — Inner-race-only hinge

1. Two 608ZZ (or equivalent) on a smooth M8 (or equivalent) bolt.
2. Spacers so printed parts never rub the outer race or shields.
3. AS5600 + diametric magnet coaxial with that bolt.
4. This is the angle-truth pivot for M1 and M5.

### M8 — Dual-purpose mode switch

1. **Tribometer mode:** hinge free to set \(\theta\); cassette foot distal; M1.
2. **Penetrometer mode:** mast aligned to the stroke; screw drives probe; M2.
3. Mode switch is mechanical reorientation and a firmware profile (current, speed, StallGuard vs SI jog). Same battery, same driver, same encoder bus.

---

## 6. Anticipatory combinations

The following combinations are disclosed now so they cannot be patented as “the OpenSlip machine plus X.” Each is the same object with an obvious add-on or swap.

1. **Wet film / contaminant:** water, soap, oil, glycol, known thickness, known residence time, squeeze-film awareness. The public protocol already flags residence time as first-order. A later written wet protocol is Phase 1-next of this object (§7), not a new meter.
2. **Dry, damp, contaminated, and mixed-direction** campaigns on the same machine.
3. **Other encoders** on the hinge or as audit: MT6816, AS5048, optical, IMU, electrolytic tilt, phone-IMU via the AP, dual-encoder fusion.
4. **Other actuators for the heel-strike:** manual drop, spring latch, solenoid, pneumatic cylinder, CO₂ cartridge, servo, second stepper, voice coil. The public roadmap already lists pneumatic / solenoid / spring as open work. Automating M1 actuation is a later phase of this object.
5. **Other penetrometer tips:** cone, flat, needle, the tribometer foot itself, a durometer-like indenter, a CBR-style pug.
6. **External force sensor** in series with the screw or under the foot (load cell, strain on the M8 rod, current-sense amplifier more precise than StallGuard), **with or without** the zero-load subtract of M2.
7. **Slip-only, penetrometer-only, and dual-purpose** SKUs sharing parts.
8. **Other screws:** Tr8x2, Tr8x4, Tr8x8 (example), ball screw, acme, belt-plus-rail. Lead is a scaling constant in M2.
9. **Other drivers / MCUs:** TMC2208/2226/2240, other ESP32 boards if T-Motor stock dries up (already in the public roadmap), STM32 + TMC, a second MCU for the cassette ratchet.
10. **Closed-loop incidence:** firmware already hunts SI using an encoder. Hunting from the **AS5600 hinge** instead of the MT6816 is anticipated.
11. **Logging:** CSV on the phone (public), SD card, BLE, USB MSC, MQTT, automatic N/E/S/W prompts, geotag, photo-of-surface alongside CSV.
12. **Test-foot chemistry:** any elastomer, leather, Neolite-type compounds, 3D-printed TPU of stated Shore, prepared with any published grit/stroke recipe.
13. **Reference surfaces and round-robins:** two independent builds, comparison data **without** claiming “equivalent to” a brand (public roadmap).
14. **Folding, telescoping, break-down, or stay-in-place stand** versions (§4.1, §4.5).
15. **Power:** any USB-C PD trigger voltage, barrel vs XT30 vs JST, isolated vs non-isolated, dual-bank hot-swap.
16. **Human-factors shell:** power-tool-like housing, handle on the mast, the TPU turnbuckle wheel, high-visibility color, OLED on the T-Motor showing live SI.
17. **Safety interlocks:** keep-off default (already public), dead-man on the PD pack, StallGuard as electronic hard-stop, mechanical pins at max incidence.
18. **Software licenses unchanged:** AGPL firmware even if a hosted “results dashboard” is added (AGPL network clause). No closed companion app that is required to measure.
19. **CAD-when-it-exists** under CERN-OHL-S, including parametric OpenSCAD/FreeCAD of the exact hinge/foot/cassette described here. The CAD is not a new invention relative to this disclosure.
20. **Soldered variants** of a machine that was designed to be solderless (soldered pigtails, a custom PCB that still talks to T-Motor/AS5600, potting). Solderless is the field example, not a fence.

---

## 7. Later phases of the SAME object (disclosed now)

CAD **does not exist yet**. **This disclosure is that phase.** Every item below is an intended later phase of the **same** OpenSlip dual-purpose machine, announced now so that completing it cannot be recast as a separate patentable invention.

| Phase | What it is | Why it is the same object |
| --- | --- | --- |
| **P0** | Public repo 2026-08-22 / 2026-08-24, firmware 0.2.0, electronics BOM, SI=tan θ, no CAD | Already live |
| **P1 (this publication)** | Architecture of the machine as designed: dual-purpose, solderless, AS5600 hinge, pre-tensioned struts, cassette foot, PD travel pack. **Still no CAD.** Firmware 0.2.0 remains electronics-first (MT6816 on the board; Phase 1 hinge truth is AS5600). | The enabling text *is* the publication of P1 |
| **P2 — CAD** | STEP/STL/source CAD of hinge, struts, foot, cassette, wheel, PD sled, under CERN-OHL-S | Dimensional freeze of P1, not new physics |
| **P3 — mechanical BOM** | Fastener list, bearing list, turnbuckle size, magnet size, exact JST part names | Shopping list for P1 |
| **P4 — AS5600 in firmware** | Public sketch reads hinge I2C as \(\theta\) truth; MT6816 optional | Firmware catching up to P1 metrology |
| **P5 — encoder-on-shaft (MT6816)** | Diametric magnet on the motor / screw, MT6816 actually tracking (public status: wired, not yet confirmed on a spinning shaft) | Redundant / motor loop for the same mast |
| **P6 — OLED confirmed** | 0.49" SSD1306 ACKing on I2C (public: first unit did not ACK) | Display for the same controller |
| **P7 — automated actuation** | GPIO/MOSFET fire pulse, solenoid/pneumatic/spring release, timestamp vs encoder in CSV (public roadmap) | M1 step 5, mechanized |
| **P8 — wet protocol** | Written wet-film method, residence time, contaminant recipes | M1 + §6.1, written down |
| **P9 — test-foot prep** | Open prep with photos | M1 step 1, written down |
| **P10 — StallGuard calibration method** | Force-approx curves, settings table | M2 / M5, tabulated |
| **P11 — CSV schema** | Versioned header: firmware, encoder, SI, SG, baseline ID, facing, contaminant, actuation | Same data, stabilized |
| **P12 — validation** | Two independent builds; reference-surface round robin; no “equivalent to brand X” claim | Same machine, inter-lab |
| **P13 — soft limits in degrees** | Public roadmap item | Firmware safety on the same hinge |
| **P14 — second controller target** | If T-Motor stock dries up | Same mechanics, swapped brain |

A person who later files on “a 3D-printed tribometer with CAD,” “an OpenSlip with a wet protocol,” “StallGuard penetrometer calibration,” or “automated heel-strike on a variable-incidence meter” is filing on a phase already named here.

---

## 8. Figures (described without drawings)

No drawings are included in this publication. None should be invented until real CAD or photographs exist. The following figure *descriptions* are the figures: a skilled person can sketch them from the text. When CAD or photos later exist, they illustrate these same figures.

**Figure 1 — Tribometer pose (overall).** Two pre-tensioned printed struts meet at a hinge. The mast stands off-vertical by angle \(\theta\). Distal foot with cassette rests on the walking surface. Turnbuckle with TPU wheel spans the hinge. T-Motor and NEMA 17 / 310 mm screw lie along the mast. 65 W PD pack is a detachable brick on a 200 cm cable. Caption: \(SI=\tan\theta\).

**Figure 2 — Penetrometer pose (overall).** The same machine, mast more vertical, lead screw driving a tip or the foot into the ground. Same PD pack. Caption: StallGuard/current vs depth, minus zero-load baseline.

**Figure 3 — Main hinge, bearings, encoder.** Cross-section: smooth M8 bolt; 608ZZ; spacer; printed ear; spacer; 608ZZ; nut. Plastic contacts inner race only. AS5600 on one ear; diametric magnet on the rotating side, coaxial. Callouts: “angle truth,” “not the T-Motor MT6816.”

**Figure 4 — Turnbuckle wheel.** Eye/jaw turnbuckle between clevis brackets; partially threaded bolts + Nyloc; no bearings on those joints. Rigid hub on the turnbuckle body; TPU tire stretched over the hub.

**Figure 5 — Distal foot and cassette.** Foot at the far end of the mast. M8 Heim (or TPU flexure) for pitch and roll. Horizontal micro-spools, thumbwheel ratchet, textured cam-lock lever clamping rubber to platen. Die spring or TPU block behind platen. Ballast cavities. Motors/spools/metal drawn as distal mass.

**Figure 6 — Lead-screw mast.** NEMA 17 with 310 mm Tr8x8, mounted to T-Motor, along the mast. Shows travel collapse (retracted ~17.3 in) vs extended stroke for penetrometer.

**Figure 7 — Power.** 65 W USB-C PD laptop bank; 200 cm PD trigger cable; 12 V on 5.5×2.1 mm; T-Motor JST V+. Pack shown **detached** (screening) and **attached** (use).

**Figure 8 — Pre-tensioned strut.** Printed tube, M8 rod inside, nuts on both ends, arrows: rod in tension, print in compression. Note: PETG/ABS/ASA, not PLA.

**Figure 9 — Travel envelope.** Bounding box ~17.3 in long × ~7 in wide. Power-tool-like silhouette. Personal-item context. No dimension beyond those two envelopes is claimed as a limit; they are the worked example.

**Figure 10 — Solderless electronics block.** T-Motor; TMC2209; unused-as-truth MT6816; I2C bus to AS5600 (JST SH) and optional OLED; stepper connector to NEMA 17; V+ from PD. Caption: 100% solderless field stack.

**Figure 11 — Zero-load subtract (plot, not a photo).** Two traces vs stroke position: unloaded StallGuard/current, loaded, and the difference. This *is* M2.

**Figure 12 — Family variants (schematic).** Side-by-side: Heim vs TPU flexure; die spring vs TPU block; travel vs stay-in-place stand; slip-only vs dual-purpose. Same hinge and encoder in every frame.

Do not commission artistic renderings that mimic a commercial meter’s trade dress. If a photo is added in a later phase, photograph the OpenSlip machine.

---

## 9. License, authorship, independence (restated)

**Author:** Michael Vredenburgh / OpenSlip (Vantage Forensics)  
**Published:** 2026-08-27  
**Status:** Public enabling disclosure.

This written disclosure is **CC BY-SA 4.0**.

Firmware and existing documentation remain **AGPL-3.0** (already public at https://github.com/MVredenburgh/OpenSlip).

Hardware CAD, **when it exists**, is **CERN-OHL-S**. Until CAD exists, this enabling text is the geometry disclosure.

**NOTICE (independence).** OpenSlip is an independent open-hardware and open-firmware project for walkway traction measurement (and, in this Phase 1, penetration resistance). It is not affiliated with, endorsed by, or derived from any commercial tribometer brand. Names of commercial tribometers, test-foot materials, and standards bodies are used only to situate the science. No affiliation or endorsement is claimed. Hardware referenced (LilyGO T-Motor, TMC2209, MT6816, AS5600, SSD1306, NEMA 17, 608ZZ, etc.) remains the property of their respective manufacturers; pin maps and part facts are documented for interoperability.

**Disclaimer.** Not a certified instrument. Not legal or safety advice. Not by itself a sufficient basis for a legal opinion. Experimental, provided AS IS. CSV logs are raw operator-tagged events.

**Default is publish.** No closed-source carve-out. Commercial use is allowed on copyleft terms (AGPL for firmware/docs; CERN-OHL-S for CAD; CC BY-SA for this text).

---

## 10. File / license table

| Artifact | Location | License | Publish status |
| --- | --- | --- | --- |
| Firmware `OpenSlip.ino` + `webpage.h` v0.2.0 | GitHub `firmware/OpenSlip/` | AGPL-3.0 | Public (2026-08-22; relicense commit 2026-08-24) |
| README, docs, CONTRIBUTING, DISCLAIMER | GitHub | AGPL-3.0 (repo-wide) | Public |
| NOTICE | GitHub `NOTICE` | (notice file) | Public |
| Electronics BOM | GitHub `hardware/bom.md` | with repo | Public; electronics only |
| Measurement protocol (working method) | GitHub `docs/measurement-protocol.md` | with repo | Public |
| This architecture / methods disclosure | `docs/defensive-publication.md` (and dated markdown + PDF) | CC BY-SA 4.0 | **Published 2026-08-27** |
| CAD (STEP/STL/source) | does not exist | CERN-OHL-S when it exists | Not started; P1 text *is* this phase |
| Manuals beyond current docs | not yet written | CC BY-SA 4.0 | Future phase |
| Mechanical BOM, wet protocol, test-foot prep, StallGuard calibration write-up, CSV schema | not yet written | CC BY-SA 4.0 (docs) / AGPL if in-repo | Future phases of the same object |

---

## 11. Next-phase artifacts still missing

List only. **Do not invent drawings, measurements, or part numbers** beyond the worked example already given.

1. CAD of hinge, struts, foot, cassette, wheel, PD sled (CERN-OHL-S).
2. Mechanical BOM (fasteners, bearings, turnbuckle, magnet, harnesses).
3. Wet-surface protocol with residence time.
4. Test-foot preparation method (open, with photographs of a real prep).
5. StallGuard / zero-load calibration method written as a repeatable lab sheet.
6. Versioned CSV schema.
7. Firmware change: AS5600 as \(\theta\) truth.
8. Confirmation photos: OLED ACK; MT6816 with magnet on a spinning shaft; first printed hinge.
9. Two independent builds and a reference-surface comparison that does **not** claim brand equivalence.

These are P2–P12 in §7. Completing them is publication of later phases of the **same** object.

---

## 12. Gaps (honest)

- No CAD, no photos of a complete Phase 1 machine in this pack.
- Public firmware 0.2.0 still treats MT6816 as the encoder in code; Phase 1 hinge truth is AS5600 — firmware has not caught up. Firmware 0.2.0 is still electronics-first.
- OLED not confirmed on the first public unit.
- MT6816 not yet confirmed with a magnet on a spinning shaft.
- No mechanical BOM, no wet protocol, no test-foot prep sheet, no StallGuard force table, no frozen CSV schema.
- No second build, no inter-lab data.
- Exact expired-patent numbers for the English XL family are **not recited here** (do not invent patent numbers). Physics is adapted; trade dress is avoided; manuals are not copied.

New art belongs in a dated enabling disclosure of this kind — not in a GitHub issue, a PR comment, a chat thread, or a review bubble. Do not commission look-alike styling of any commercial tribometer.

---

## 13. Channels

This enabling disclosure is published as markdown and print PDF dated **2026-08-27**.

### First wave

1. **Zenodo** — DOI; deposit **PDF + markdown** of this enabling disclosure. Primary archival timestamp.
2. **Technical Disclosure Commons** — defensive-publication venue.
3. **Hackaday.io** — project log pointing at the Zenodo DOI and the existing GitHub.
4. **GitHub** — already a live channel for firmware/docs (Phase 0) at https://github.com/MVredenburgh/OpenSlip. This disclosure is intended to be added to that public repo as a dated file (for example `docs/defensive-publication.md`).

### Not first wave

- **Research Disclosure** — not first wave.
- **FreeCAD forum** — not first wave (relevant only once CAD exists).

### Timestamp stack

1. Zenodo DOI (PDF + md).
2. Technical Disclosure Commons entry.
3. GitHub commit hash and date on the already-public repo (and on the disclosure file if/when it is added).

Do not invent additional first-wave venues. A chat screenshot or a private PDF is not a timestamp.

---

**End of enabling disclosure.**
