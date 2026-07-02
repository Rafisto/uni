## Pinout

```
DIGITAL

PIN 3  // SERVO
PIN 4  // HC-SR04 TRIGGER
PIN 5  // yellow - EN B - SPEED L - PIN 5
PIN 6  // white - EN A - SPEED R - PIN 6
PIN 7  // green - IN4 - PIN 7
PIN 8  // blue - IN3 - PIN 8
PIN 9  // RESERVED
PIN 10 // RESERVED
PIN 11 // gray - IN1 - PIN 11
PIN 12 // purple - IN2 - PIN 12

ANALOG

A0     // LEFT FRONT WHEEL
A1     // RIGHT FRONT WHEEL
A2     // HC-SR04 ECHO
A4     // LCD I2C SDA
A5     // LCD I2C SCL
```

## IRremote

PIN: 2137 = `0x46,0x45,0x47,0x7`

Codes:
- 1 : 0x45
- 2 : 0x46
- 3 : 0x47
- 4 : 0x44
- 5 : 0x40
- 6 : 0x43
- 7 : 0x7
- 8 : 0x15
- 9 : 0x9
- 0 : 0x19
- `#` : 0xD
- OK : 0x1C
- UP : 0x18
- DOWN : 0x52
- LEFT : 0x8
- RIGHT : 0x5A

- Library: https://github.com/Arduino-IRremote/Arduino-IRremote
- Arduino Library: IRremote

## LiqidCrystal I2C 

- Original Library: https://github.com/johnrickman/LiquidCrystal_I2C
- Arduino Library: https://github.com/markub3327/LiquidCrystal_I2C