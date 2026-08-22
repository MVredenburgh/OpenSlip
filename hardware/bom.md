# Bill of materials (controller stage)

Quantities for one prototype electronics stack. Mechanics/test foot are TBD.

| Item | Example | Notes |
| --- | --- | --- |
| Motion controller | LilyGO T-Motor | ESP32 + TMC2209 + MT6816 |
| USB-TTL 3.3 V | CH340 / CP2102 / FTDI | First flash only |
| Jumper wires | Dupont | First flash only |
| DC supply | 5–12 V, ≥2 A | Match motor current; 12 V typical |
| Stepper | NEMA17 bipolar | Size to mast inertia, not “as big as possible” |
| Magnet | Diametric, for MT6816 | Air gap per MT6816 datasheet |
| OLED (optional) | 0.49" SSD1306 64×32 | 4-pin I2C: VDD, GND, SDA, SCL |
| Heat sink | Included with many T-Motor kits | On the TMC2209 |

## Later (not required to run firmware)

- Mast / chassis (CAD wanted)
- Test-foot blank + elastomer
- Ankle spring or equivalent
- Actuator (pneumatic cylinder, solenoid, or other) — **not implemented**
- Limit switches (GPIO 21/22 are I2C on this board — do not steal them for limits without moving OLED)

## Consumables when you start measuring

- Prepared test foot and a written prep method
- Water bottle / contaminant protocol
- Level or known-flat plate for zeroing
- Independent inclinometer for first calibration
