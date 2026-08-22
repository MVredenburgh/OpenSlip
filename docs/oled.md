# OLED troubleshooting

The kit OLED is a **0.49 inch SSD1306**, 64×32 pixels, I2C. It has **no backlight**. Working pixels emit a small white/blue rectangle (~12 mm × 6 mm). From a steep angle it can look “off” even when it is on.

## What firmware does (0.2.0+)

On boot it:

1. I2C-scans GPIO22/21 as SDA/SCL at 50 kHz
2. Scans the swapped pair (in case the header was wired backwards)
3. If 0x3C or 0x3D ACKs, initializes U8g2 `SSD1306_64X32_1F`, contrast 255
4. Blinks **solid white** for ~20 seconds

The phone UI shows an **OLED** line, for example:

- `I2C 0x3C normal (SDA22 SCL21)` — chip is talking
- `I2C 0x3C SWAPPED pins` — firmware compensated
- `No I2C device. Check OLED VDD/GND/SDA/SCL solder` — no ACK

**Flash OLED white 15s** repeats the blink on demand.

## If the UI says no I2C device

Software is not the first suspect. The ESP32 never heard the panel.

Check, in order:

1. **VDD and GND** continuity to the OLED module. A dead rail gives a dark glass and no ACK.
2. Solder bridges between adjacent header pins.
3. SDA vs SCL swapped (firmware already tries both; if *neither* bus ACKs, it is not just a swap).
4. Cracked module or unsoldered OLED flex.

Do not press on the module while jumper wires are hanging off the programming header.

## If I2C ACKs but you still see nothing

- Look straight at the glass during the white blink.
- Confirm it is SSD1306 64×32, not a different controller.
- Try the other I2C address (firmware already tries 0x3C and 0x3D).

## Pins

| OLED | T-Motor |
| --- | --- |
| VDD | 3.3 V |
| GND | GND |
| SDA | GPIO 22 |
| SCL | GPIO 21 |
