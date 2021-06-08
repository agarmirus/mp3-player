#include "button_processing.h"
#include "file_handler.h"
#include "Interface.h"
#include "screen.h"

#define BUTTONS_COUNT 3

#define INDEX_BUTTON_LEFT 0
#define INDEX_BUTTON_SELECT 1
#define INDEX_BUTTON_RIGHT 2

// Events
#define PLAY_BUTTON_PRESSED 1
#define FORWARD_BUTTON_PRESSED 2
#define PREVIOUS_BUTTON_PRESSED 3
#define VOLUME_CHANGED 4
#define MUTE_TOGGLED 5
#define BRIGHTNESS_CHANGED 6
#define INVERT_TOGGLED 7
#define BLOCK_CHANGED 8
#define ITEM_CHANGED 9
#define LEVEL_CHANGED 10
#define LEVEL_MODE_CHANGED 11
#define OK_BUTTON_ERROR_PRESSED 12

// States
#define PLAY  1
#define PAUSE 2

// #define _INIT_

Interface interface;
int8_t event;

int buttons[BUTTONS_COUNT] = {0};
int current_track_number = 0;

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
