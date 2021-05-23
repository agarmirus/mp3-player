#include "button_processing.h"
#include "screen.h"
#include <stdint.h>


const PROGMEM int LEFT_BUTTON = 11;
const PROGMEM int SELECT_BUTTON = 12;
const PROGMEM int RIGHT_BUTTON = 13;
const PROGMEM int POWER_BUTTON = 14;


void setup()
{
    pinMode(LEFT_BUTTON, INPUT);
    pinMode(SELECT_BUTTON, INPUT);
    pinMode(RIGHT_BUTTON, INPUT);
    pinMode(POWER_BUTTON, INPUT);
}

void loop();
