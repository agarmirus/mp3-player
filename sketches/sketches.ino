#include "button_processing.h"
#include "file_handler.h"
#include "Interface.h"
#include "screen.h"


#define BUTTONS_COUNT 3

#define INDEX_BUTTON_LEFT 0
#define INDEX_BUTTON_SELECT 1
#define INDEX_BUTTON_RIGHT 2

int buttons[BUTTONS_COUNT] = {0};

// #define _INIT_

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
