# OpenSlip measurement protocol (draft)

This is a **working method** for an inclined-strut meter. It is not a copy of any commercial manual and it is not a published standard. Change it in the open when data say to.

## Physics

On a **level** walking surface, the strut (mast) makes an angle \(\theta\) with the vertical (the surface normal).

The ratio of the horizontal component of the thrust to the vertical component is:

\[
SI = \tan\theta
\]

OpenSlip calls \(SI\) the **slip index**. It is reported to 0.01.

| SI | \(\theta\) from vertical |
| --- | --- |
| 0.00 | 0° (vertical) |
| 0.30 | 16.70° |
| 0.50 | 26.57° |
| 1.00 | 45° |

On a **ramp**, “vertical” is no longer the surface normal. Either level the chassis to the surface (measure in the surface frame) or record chassis pitch and correct. Do not mix the two.

Firmware uses the encoder (after zero and gear-ratio calibration) as the source of \(\theta\), not step counting.

## Operator sequence

1. Prepare the test foot with a **written** method (grit, strokes, cleaning). Publish that method with the data.
2. Zero the mast at the surface normal (vertical on a level floor). Use **Set vertical zero**.
3. Confirm calibration against an inclinometer at least once per session until the machine is trusted.
4. Start at a **more vertical** (lower SI) setting than you expect to slip.
5. Actuate the test foot (your mechanism — not yet part of OpenSlip firmware).
6. If it holds, increase SI (default 0.01) and repeat. Always go from lower SI to higher SI.
7. When it slips, record SI to 0.01 and tag **Slip**. The previous hold is also useful — tag **No slip**.
8. Rotate the facing 90° (N, E, S, W) and repeat if the surface may be directional.
9. Export CSV.

Do not dwell the test foot on a wet surface before applying the impulse if you are trying to avoid squeeze-film “sticktion.” Residence time is a first-order variable. Document it.

## Wet vs dry

Dry, clean, hard floors often behave like a static coefficient of friction at the instant of slip. Wet, oily, or polished-wet surfaces do not. An open method has to say:

- contaminant and film
- how the film was applied
- time from application to actuation
- test-foot material

until those are standardized in this project, treat wet numbers as **condition-specific**, not interchangeable with dry SI.

## What to publish with a number

- Firmware version
- Gear ratio and zero method
- Test-foot material and prep
- Surface, facing, contaminant
- Raw CSV, not only the average
- Whether actuation was manual, pneumatic, or other

## Inter-lab (future)

A public reference-surface round robin belongs in this repo once two machines exist. Until then, do not claim agreement with any named commercial meter.
