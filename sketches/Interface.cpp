/*
 * Implementation of Interface module
 *
 * Author: Lagutin Daniil
 * Group: IU7-23B
 */

#include <string.h>
#include <limits.h>
#include <EEPROM.h>
#include "Interface.h"
#include "screen.h"
#include "button_processing.h"

int8_t on_select(Interface *const interface);

int8_t on_navigate(Interface *const interface, const int button);

int8_t on_select_level(Interface *const interface, const int8_t type);

void init_interface(Interface *const interface)
{
    interface->brightness = EEPROM.read(BRIGHTNESS_BYTE);
    interface->volume = EEPROM.read(VOLUME_BYTE);
    interface->mute = EEPROM.read(MUTE_BYTE);
    interface->invert = EEPROM.read(INVERT_BYTE);
    interface->state = PAUSE;
    interface->fade = UNFADED;
    interface->last_call = mills();

    strcpy(interface->track, (char *) pgm_read_word(&TRACK_PLACEHOLDER));
    interface->cursor_pos = 0;

    interface->event = NULL;
    interface->active_block = BLOCK_BUTTON;
    interface->block_item = BUTTON_PLAY;

    interface->level_type = NULL;
    interface->level_mode = NULL;

    interface->error = NULL;
}

void check_timer(Interface *const interface)
{
    unsigned long c_time = mills();
    unsigned long diff = c_time - interface->last_call;
    
    // Fix mills ulong limit
    if (diff < 0)
        if (c_time <= SLEEP_TIME)
            diff = ULONG_MAX - interface->last_call + c_time;
        else
            interface->last_call = 0;
    
    if (LEVEL_ADJUST == interface->level_mode && diff > ADJUST_TIME)
        interface->level_mode = LEVEL_SELECT;

    if (UNFADED == interface->fade && diff > SLEEP_TIME)
    {
        interface->fade = FADED;
        set_screen_brightness(interface->brightness / FADED_BRIGHTNESS_SCALE);
    }
    else if (FADED == interface->fade && diff <= SLEEP_TIME)
    {
        interface->fade = UNFADED;
        set_screen_brightness(interface->brightness);
    }
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
    set_screen_invert(interface->invert);
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
    strncpy(interface->track, track, MAX_STRING);
    interface->cursor_pos = 0;
}

int8_t on_select(Interface *const interface)
{
    switch (interface->block_item)
    {
        case (BUTTON_PLAY):
            if (PLAY == interface->state)
                interface->state = PAUSE;
            else
                interface->state = PLAY;
            
            return PLAY_BUTTON_PRESSED;
        case (BUTTON_PREVIOUS):
            return PREVIOUS_BUTTON_PRESSED;
        case (BUTTON_FORWARD):
            return FORWARD_BUTTON_PRESSED;
        case (LEVEL_DECREASE):
            return on_select_level(interface, DECREASE);
        case (LEVEL_INCREASE):
            return on_select_level(interface, INCREASE);
        case (LEVEL_BUTTON):
            if (LEVEL_SELECT == interface->level_mode) 
            {
                interface->level_mode = LEVEL_ADJUST;

                return LEVEL_MODE_CHANGED;
            }

            if (LEVEL_VOLUME == interface->level_type)
            {
                toggle_mute(interface);

                return MUTE_TOGGLED;
            }

            if (LEVEL_BRIGHTNESS == interface->type)
            {
                toggle_invert(interface);

                return INVERT_TOGGLED;
            }

            break;
    }

    return NULL;
}

int8_t on_navigate(Interface *const interface, const int button)
{
    if (BLOCK_ERROR == interface->active_block)
        return NULL;

    uint8_t step = (INDEX_BUTTON_LEFT == button) ? 1 : -1;

    if (-1 == step && START_INDEX == interface->block_item || 1 == step 
        && (pgm_read_byte(&MAX_BLOCK_ELEMENTS[interface->active_block])
            == interface->block_item))
    {
        if (BLOCK_LEVEL == interface->active_block 
            && LEVEL_ADJUST == interface->level_mode || -1 == step 
            && START_INDEX == interface->active_block || 1 == step
            && PLAIN_BLOCK_AMOUNT == interface->active_block - 1)
            return NULL;
        
        interface->active_block += step;
        
        if (-1 == step)
            interface->block_item = START_INDEX;
        else
            (interface->block_item = 
             pgm_read_byte(&MAX_BLOCK_ELEMENTS[interface->active_block]) - 1);

        return BLOCK_CHANGED;
    }

    interface->block_item += step;

    return ITEM_CHANGED;
}

int8_t on_select_level(Interface *const interface, const int8_t type)
{
    if (LEVEL_ADJUST == interface->level_mode)
    {
        if (LEVEL_VOLUME == interface->level_type)
        {
            step_volume(interface, type);
            return VOLUME_CHANGED;
        }
        else if (LEVEL_BRIGHTNESS == interface->level_type)
        {
            step_brightness(interface, type);
            return BRIGHTNESS_CHANGED;
        }
    }
    else if (LEVEL_SELECT == interface->level_mode)
    {
         if (INCREASE == type && (interface->level_type)++ >= LEVEL_AMOUNT - 1)
            interface->level_type = START_INDEX;

         else if (DECREASE == type && (interface->level_type)-- <= START_INDEX)
            interface->level_type = LEVEL_AMOUNT - 1;

         return LEVEL_CHANGED; 
    } 

    return NULL;
}

int8_t get_event(Interface *const interface, const int *const buttons)
{
    int8_t rc = NULL;

    switch (BUTTON_PRESSED)
    {
        case (button[INDEX_BUTTON_SELECT]):
            rc = on_select(interface);
            break;
        case (button[INDEX_BUTTON_LEFT]):
            rc = on_navigate(interface, INDEX_BUTTON_LEFT);
            break;
        case (button[INDEX_BUTTON_RIGHT]):
            rc = on_navigate(interface, INDEX_BUTTON_RIGHT);
            break;
    }

    interface->event = rc;
    interface->last_call = mills();
    check_timer(interface);

    return rc;
}

int8_t get_state(const Interface *const interface)
{
    return interface->state;
}

uint8_t get_volume(const Interface *const interface)
{
    return interface->volume;
}

