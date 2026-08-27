**Published:** 2026-08-27  
**Author:** Michael Vredenburgh / OpenSlip (Vantage Forensics)  
**Licenses:** Firmware and in-repo documentation AGPL-3.0. Written architecture / methods disclosure CC BY-SA 4.0. Hardware CAD, when it exists, CERN-OHL-S.

Enabling disclosure: [defensive-publication.md](defensive-publication.md)  
Public firmware: https://github.com/MVredenburgh/OpenSlip

# Measurement protocol

This is a **working method** for a dual-purpose inclined-strut tribometer and StallGuard penetrometer. It is not a copy of any commercial manual and it is not a published standard. It is **not ASTM/ANSI certified** and **not a legal-opinion instrument**. Change it in the open when data say to.

Numbered methods in this documentation:

| ID | Method |
| --- | --- |
| **M1** | Slip protocol (vertical to slip, N/E/S/W, SI to 0.01) |
| **M2** | Penetrometer: StallGuard + zero-load subtract |
| **M3** | Reel-to-reel cassette + cam-lock |
| **M4** | Travel / TSA detachable PD pack |
| **M5** | Hinge / encoder calibration |

(The enabling disclosure pack also names related methods for the pre-tensioned strut, inner-race hinge, and dual-purpose mode switch. Those are the same object.)

## Physics

On a **level** walking surface, the strut (mast) makes an angle \(\theta\) with the vertical (the surface normal).

\[
SI = \tan\theta
\]

OpenSlip calls \(SI\) the **slip index**. It is reported to **0.01**.

| SI | \(\theta\) from vertical |
| --- | --- |
| 0.00 | 0° (vertical) |
| 0.30 | 16.70° |
| 0.50 | 26.57° |
| 1.00 | 45° |

On a **ramp**, “vertical” is no longer the surface normal. Either level the chassis to the surface (measure in the surface frame) or record chassis pitch and correct. Do not mix the two.

**Encoder, not step counting, is metrology.** Phase 1 angle truth is the **AS5600 on the hinge**. Firmware 0.2.0 still reads the onboard MT6816; that chip is **not** the mast sensor in this design. Firmware 0.2.0 is still electronics-first.

This method does **not** claim equivalence to any commercial tribometer. English XL principles (variable incidence, distal weight, heel-strike) are adapted as physics; trade dress is avoided.

---

## M1 — Slip / traction protocol

1. Prepare the test elastomer with a **written** prep (grit, strokes, cleaning). Publish the prep with the data when data are published.
2. Place the instrument on the walking surface. On a **level** floor, set the mast to the surface normal (**vertical**). **Zero** the hinge AS5600 there. \(SI=\tan\theta\) with \(\theta=0\) at that zero. Confirm with method M5.
3. Start **more vertical** (lower SI) than the expected slip.
4. Deliver a heel-strike: distal mass + spring (die spring or TPU block) drives the **cam-locked** cassette rubber onto the surface (method M3). Actuation may be manual (operator lets the foot fall or snaps it), spring-released, or later automated. Residence time on a wet film is a first-order variable; document it.
5. If the foot **holds**, increase incidence by about 0.01 SI (turnbuckle wheel and/or firmware jog) and repeat. Always go from lower SI to higher SI — **vertical toward slip**.
6. On **first slip**, record SI to **0.01** and tag Slip. Tag the previous hold as No slip if useful.
7. If the surface may be directional, repeat facing **north, east, south, and west**.
8. Export CSV (firmware version, SI, encoder identity, tags). Do not treat a phone-UI average as a complete uncertainty budget.

On a ramp, either level the chassis into the surface frame or record chassis pitch and correct.

---

## M2 — Penetrometer with StallGuard and zero-load subtract

1. Reconfigure or reorient the same machine so the NEMA 17 **Tr8x8** drives a probe, tip, or the foot **into or against** the material under test.
2. **Zero-load calibration (dynamic, per session or per stroke family):** with the probe in air (or on a known-free slide), run a full or representative stroke at the intended speed and current. Log TMC2209 **StallGuard** (and/or RMS current, and/or `SG_RESULT`) against lead-screw position. Store this as the **friction baseline**. It includes lead-screw efficiency, nut stiction, gravity of the moving stack, and seal drag.
3. **Loaded stroke:** repeat in the material. Log the same signals vs position.
4. **Subtract:** reported resistance at \(z\) = loaded(\(z\)) − baseline(\(z\)) (interpolated to the same position). Do not report raw StallGuard as “ground strength.”
5. Optional stops: StallGuard threshold as a digital “hit hard stop / hit a stone” event; current cap as a thermal safety.
6. Report: firmware version, RMS current setting, microstep, screw lead (example: Tr8x8), speed, baseline ID, raw and subtracted traces.

A later published calibration curve (settings → approximate force) is a later phase of this **same** method. An external load cell may replace or audit StallGuard; the zero-load subtract still applies.

---

## M3 — Reel-to-reel cassette + cam-lock

1. Mount two micro-spools with **horizontal** axes on the distal foot.
2. Thread elastomer from supply spool across the platen to take-up spool.
3. Advance with a **thumbwheel ratchet** until unused material covers the platen.
4. Close a **textured cam-lock lever** to clamp the strip to the platen so it cannot creep during the strike.
5. Perform M1 (or a documented dry/wet wipe).
6. Release the cam-lock, ratchet fresh material, re-clamp. Used material winds onto take-up; do not reverse contaminated rubber onto the contact patch.

In-family variants: drop-in cassette cartridge; vertical spools; clips; one-shot coupons.

---

## M4 — Travel / TSA detachable PD pack

1. Retract the **310 mm** lead screw (or the then-current screw) until overall length is about **17.3 in** or less.
2. Confirm max width about **7 in** (hinge ears, foot, wheel).
3. Cam-lock the cassette so the strip cannot unroll in a bag.
4. **Detach the 65 W PD pack** from the instrument. Carry the pack as an ordinary laptop power bank. The machine body then has no large lithium pack inside it.
5. Carry the body as airline **personal item**. Intended visual language: professional power tool, not a laboratory jig.
6. Reattach PD + 200 cm trigger cable at the site; then M5, then M1 or M2.

Exact carrier rules vary; this method is the **mechanical** pack-down, not legal advice about what any airline or screening authority will accept.

## M5 — Hinge / encoder calibration

**Angle / SI**

1. Place on a known-level surface. Set hinge to surface normal. Store AS5600 reading as zero. \(SI=\tan\theta\).
2. Move to a known angle (independent digital inclinometer on the mast, or a known SI fixture). Store the mapping (counts per degree). AS5600 is 12-bit (4096 counts/rev) in the worked example; other I2C encoders differ.
3. Direct-on-hinge AS5600 ⇒ gear ratio ≈ 1. Learn a ratio only if a reduction exists between encoder and mast.
4. Repeat after travel, after bearing re-pack, and whenever the magnet air gap is disturbed.
5. Independent inclinometer vs AS5600 vs (optional) MT6816, logged together, is the audit. Firmware version goes in the CSV header.

**Penetrometer baseline**

6. Run M2 step 2 at the same speed/current as the working stroke. Invalidate the baseline if temperature, orientation, or nut wear changed.

**StallGuard / current**

7. Note TMC2209 `SGTHRS`, RMS current, and microstep with every subtracted trace. StallGuard is driver-specific and speed-specific; it is comparable only under a documented setting.

---

## Wet vs dry

Dry, clean, hard floors often behave like a static coefficient of friction at the instant of slip. Wet, oily, or polished-wet surfaces do not. Until a written wet protocol is published (already named as a later phase of this same object), treat wet numbers as **condition-specific**. Document contaminant, film, application, and **residence time**. Do not dwell the test foot on a wet surface before the impulse if you are trying to avoid squeeze-film “sticktion.”

## What to publish with a number

- Firmware version (0.2.0 or successor)
- Encoder identity (hinge AS5600 vs any audit sensor) and zero method
- Test-foot material, cassette state, and prep
- Surface, facing (N/E/S/W), contaminant, residence time
- Raw CSV, not only the average
- Whether actuation was manual, spring, solenoid, pneumatic, or other
- For M2: StallGuard settings, screw lead, baseline ID, raw and subtracted traces

## Inter-lab (later phase, already disclosed)

A public reference-surface round robin belongs here once two machines exist. Until then, do not claim agreement with any named commercial meter.
