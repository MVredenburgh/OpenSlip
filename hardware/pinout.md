# T-Motor pin map (OpenSlip)

Source: [LilyGO T-Motor README](https://github.com/Xinyuan-LilyGO/T-Motor). Confirm against your PCB silkscreen.

| Function | GPIO | Notes |
| --- | --- | --- |
| TMC2209 EN | 2 | Active low |
| TMC2209 DIR | 18 | |
| TMC2209 STEP | 23 | |
| TMC2209 CLK | 19 | Held low; use internal clock |
| TMC2209 SPREAD | 4 | |
| TMC2209 UART RX | 26 | ESP32 RX ← PDN_UART |
| TMC2209 UART TX | 27 | ESP32 TX → 1 kΩ → PDN_UART |
| MT6816 CS | 15 | SPI |
| MT6816 SCLK | 14 | |
| MT6816 MISO | 12 | |
| MT6816 MOSI | 13 | |
| I2C SCL | 21 | OLED |
| I2C SDA | 22 | OLED |
| Button B1 | 36 | Input only |
| Button B2 | 34 | Input only |
| Button B3 | 35 | Input only |
| External STEP monitor | 25 | Unused by OpenSlip |
| External DIR monitor | 32 | Unused |
| External EN monitor | 33 | Unused |

TMC2209 UART address follows MS1/MS2 dip switches. OpenSlip **scans 0b00–0b11**.

Programming UART is **UART0** (GPIO1/GPIO3), not GPIO26/27.
