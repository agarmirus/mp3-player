/
#include "button_processing.h"
#include "file_handler.h"
#include "Interface.h"
#include "screen.h"

#define BUTTON_NOT_PRESSED 0
#define BUTTONS_COUNT 3

#define DEFAULT_VOLUME 10
#define MUTE 0

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

    setVolume(DEFAULT_VOLUME);
}

void loop(void)
{
    // Get information about buttons

    button_processing(buttons);
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
            pause();
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
    else if (event == VOLUME_CHANGED)
    {
        setVolume(interface.volume);
    }
    else if (event == MUTE_TOGGLED)
    {
        if (interface.mute)
        {
            setVolume(MUTE);
        }
        else
            setVolume(interface.volume);
    }

    draw_screen_frame(&interface);
    delay(100);
}
