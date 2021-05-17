/*
 * Implementation of Interface module
 *
 * Author: Lagutin Daniil
 * Group: IU7-23B
 */

#include <string.h>
#include "Interface.h"
#include "screen.h"

void init_interface(Interface *const interface)
{
    interface->brightness = 125; // Look forward eeprom
    interface->volume = //?;     // same
    interface->mute = 1;         // same
    interface->invert = 1;       // same
    interface->state = PAUSE;

    strcpy(interface->track, TRACK_PLACEHOLDER);
    interface->cursor_pos = 0;

    interface->event = NULL;
    interface->active_block = BLOCK_BUTTON;
    interface->block_item = BUTTON_PLAY;

    interface->error = NULL;
}

void step_brightness(Interface *const interface, const int8_t type)
{
    switch (type)
    {
        case (INCREASE):
            if (MAX_LEVEL_BRIGHTNESS - BRIGHTNESS_STEP >= interface->brightness)
                interface->brightness += BRIGHTNESS_STEP;
            break;
        case (DECREASE):
            if (BRIGHTNESS_STEP < interface->brightness)
                interface->brightness -= BRIGHTNESS_STEP;
            break;
    }

    set_screen_brightness(interface->brightness);
}

void toggle_invert(Interface *const interface)
{
    interface->invert = !(interface->invert);
}

void step_volume(Interface *const interface, const int8_t type)
{
    switch (type)
    {
        case (INCREASE):
            if (MAX_LEVEL_VOLUME - VOLUME_STEP >= interface->volume)
                interface->volume += VOLUME_STEP;
            break;
        case (DECREASE):
            if (VOLUME_STEP < interface->volume)
                interface->volume -= VOLUME_STEP;
            break;
    }
}

void toggle_mute(Interface *const interface)
{
    interface->mute = !(interface->mute);
}

void set_track(Interface *const interface, const char *const track)
{
    strcpy(interface->track, track);
    interface->cursor_pos = 0;
}

int8_t get_state(const Interface *const interface)
{
    return interface->state;
}

/* ? */ get_volume(const Interface *const interface)
{
    return interface->volume;
}

