#include <EEPROM.h>
#include "Interface.h"

void setup_(void)
{
    EEPROM.write(BRIGHTNESS_BYTE, DEF_BRIGHTNESS);
    EEPROM.write(VOLUME_BYTE, DEF_VOLUME);
    EEPROM.write(INVERT_BYTE, DEF_INVERT);
    EEPROM.write(MUTE_BYTE, DEF_MUTE);
}
