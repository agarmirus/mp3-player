#include "button_processing.h"
#include "screen.h"


void setup()
{
    pinMode(pgm_read_word(&BUTTON_LEFT), INPUT_PULLUP);
    pinMode(pgm_read_word(&BUTTON_SELECT), INPUT_PULLUP);
    pinMode(pgm_read_word(&BUTTON_RIGTH), INPUT_PULLUP);
}

void loop();
