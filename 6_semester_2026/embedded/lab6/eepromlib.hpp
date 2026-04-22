#ifndef RW_EEPROM_LIB
#define RW_EEPROM_LIB
// https://forum.arduino.cc/t/how-to-save-an-integer-in-eeprom/52254/3

int ewrite_int(int ee, const int value) {
    const byte* p = (const byte*)(const void*)&value;
    int i;
    for (i = 0; i < sizeof(value); i++)
	  EEPROM.write(ee++, *p++);
    return i;
}

int ewrite_str(int ee, const char* str) {
    int i = 0;
    while (*str) {
        EEPROM.write(ee++, *str++);
        i++;
    }
    EEPROM.write(ee, '\0');
    return i + 1;
}

// template <class T> int EEPROM_readAnything(int ee, T& value)
// {
//     byte* p = (byte*)(void*)&value;
//     int i;
//     for (i = 0; i < sizeof(value); i++)
// 	  *p++ = EEPROM.read(ee++);
//     return i;
// }

#endif 