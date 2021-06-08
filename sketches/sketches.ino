#include "button_processing.h"
#include "file_handler.h"
#include "Interface.h"
#include "screen.h"

// #define _INIT_

int buttons[BUTTONS_COUNT] = { BUTTON_NOT_PRESSED };

Interface interface;
int8_t event;

void setup(void)
{
#ifdef _INIT_
    init_screen_eeprom();
#endif

    pinMode(pgm_read_word(&BUTTON_LEFT), INPUT_PULLUP);
    pinMode(pgm_read_word(&BUTTON_SELECT), INPUT_PULLUP);
    pinMode(pgm_read_word(&BUTTON_RIGTH), INPUT_PULLUP);

    setupDFM();  // Initializing DFMPlayer
    init_interface(&interface);
    init_screen(&interface);
}

void loop(void)
{
    // Get information about buttons

    event = get_event(&interface, buttons);
    check_timer(&interface);

    // Get/set variables 
    // Do stuff ...

    

    draw_screen_frame(&interface);
    delay(100);
}
