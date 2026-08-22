# Roadmap

Rough order. Rearrange when someone actually builds the next piece.

## Now (electronics + firmware)

- [x] ESP32 AP, phone UI, OTA partition
- [x] TMC2209 scan, arm/disarm, jog
- [x] MT6816 read, SI = tan(θ), CSV
- [x] OLED diagnostic (I2C scan, white blink)
- [ ] OLED confirmed on a soldered 0.49" panel
- [ ] Encoder confirmed with magnet on a spinning shaft
- [ ] Soft limits in degrees, not only SI 1.15 cap

## Mechanics

- [ ] Mast + chassis CAD (inclined strut, known geometry)
- [ ] Test-foot mount / ankle
- [ ] How the T-Motor couples to the mast (direct, belt, screw)
- [ ] Stiffness and backlash budget so 0.01 SI is real

## Actuation

- [ ] Document a first actuator (pneumatic, solenoid, or spring)
- [ ] Optional GPIO / MOSFET fire pulse **without** stealing I2C pins
- [ ] Timestamp actuation vs encoder in the CSV

## Method

- [ ] Written test-foot prep (open, with photos)
- [ ] Wet-film protocol with residence time
- [ ] Reference-surface list and a shared CSV schema
- [ ] Uncertainty: encoder, gear ratio, chassis pitch, foot wear

## Project

- [ ] Two independent builds
- [ ] Comparison data (not claimed “equivalent to” a brand)
- [ ] Optional second controller target if T-Motor stock dries up
- [ ] Mechanical license note (CERN-OHL-W or CC-BY-SA) when CAD lands
