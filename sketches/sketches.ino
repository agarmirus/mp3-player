#include "button_processing.h"
#include "file_handler.h"
#include "Interface.h"
#include "screen.h"

// #define _INIT_

Interface interface;
int8_t event;

int buttons[BUTTONS_COUNT] = { BUTTON_NOT_PRESSED };
int current_track_number = 0;

void setup(void)
{
#ifdef _INIT_
    init_screen_eeprom();
#endif

    pinMode(pgm_read_word(&PIN_BUTTON_LEFT), INPUT_PULLUP);
    pinMode(pgm_read_word(&PIN_BUTTON_SELECT), INPUT_PULLUP);
    pinMode(pgm_read_word(&PIN_BUTTON_RIGHT), INPUT_PULLUP);

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

    if (event == PLAY_BUTTON_PRESSED)
    {
        if (interface.state == PLAY)
        {
            play(current_track_number);
        }
        else if (interface.state == PAUSE)
        {
            stop();
        }
    }
    else if (event == PREVIOUS_BUTTON_PRESSED || event == FORWARD_BUTTON_PRESSED)
    {
        stop();
        current_track_number += event == FORWARD_BUTTON_PRESSED ? 1 : -1;

        if (current_track_number < 0)
        {
            current_track_number = 0;
        }
        else
            play(current_track_number);
    }

    draw_screen_frame(&interface);
    delay(100);
}
