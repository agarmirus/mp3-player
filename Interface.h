/*
 * Module, that allow to interact with GUI of a MP3-Player
 *
 * Author: Lagutin Daniil
 * Group: IU7-23B
 */

#ifndef INTERFACE_H
#define INTERFACE_H

#include <stdint.h>
#include <avr/pgmspace.h>

// Interface elements
// BLOCKS
const PROGMEM int8_t BLOCK_BUTTON = 1;
const PROGMEM int8_t BLOCK_LEVEL = 2;
const PROGMEM int8_t BLOCK_ERROR = 3;

// BUTTON ITEMS
const PROGMEM int8_t BUTTON_PLAY = 1;
const PROGMEM int8_t BUTTON_PREVIOUS = 2;
const PROGMEM int8_t BUTTON_FORWARD = 3;

// LEVEL ITEMS
const PROGMEM int8_t LEVEL_VOLUME = 1;
const PROGMEM int8_t LEVEL_BRIGHTNESS = 2;

// ERROR ITEMS
const PROGMEM int8_t ERROR_OK = 1;

// Values
#define MAX_STRING 255
const PROGMEM int8_t MAX_LEVEL_VOLUME = //?;
const PROGMEM int8_t MAX_LEVEL_BRIGHTNESS = 255;
const PROGMEM int8_t BRIGHTNESS_STEP = 51;
const PROGMEM int8_t VOLUME_STEP = //?;
const PROGMEM int8_t INCREASE = 1;
const PROGMEM int8_t DECREASE = 2;

const PROGMEM char TRACK_PLACEHOLDER[] = "Ничего не воспроизводится";

// States
const PROGMEM int8_t PLAY = 1;
const PROGMEM int8_t PAUSE = 2;

// Events
const PROGMEM int8_t PLAY_BUTTON_PRESSED = 1;
const PROGMEM int8_t FORWARD_BUTTON_PRESSED = 2;
const PROGMEM int8_t BACKWARD_BUTTON_PRESSED = 3;
const PROGMEM int8_t VOLUME_INCREASED = 4;
const PROGMEM int8_t VOLUME_DECREASED = 5;
const PROGMEM int8_t MUTE_TOGGLED = 6;
const PROGMEM int8_t BRIGHTNESS_INCREASED = 7;
const PROGMEM int8_t BRIGHTNESS_DECREASED = 8;
const PROGMEM int8_t INVERT_TOGGLED = 9;
const PROGMEM int8_t BLOCK_CHANGED = 10;
const PROGMEM int8_t ITEM_CHANGED = 11;

// Main interface item 
typedef struct 
{
    // settings
    uint8_t brightness;
    /* ? */ volume; 
    int8_t mute;
    int8_t invert;
    uint8_t state;
    
    // track preferences
    char track[MAX_STRING + 1];
    uint8_t cursor_pos;

    // interface
    int8_t event;
    int8_t active_block;
    int8_t block_item;

    // errors
    int8_t error;
} Interface;

void init_interface(Interface *const interface);

void step_brightness(Interface *const interface, const int8_t type);

void toggle_invert(Interface *const interface);

void step_volume(Interface *const interface, const int8_t type);

void toggle_mute(Interface *const interface);

void set_track(Interface *const interface, const char *const track);

void set_error(Interface *const interface, const /* ? */ error);

int8_t get_event(Interface *const interface, const /* ? */ action);

int8_t get_state(const Interface *const interface);

/* ? */ get_volume(const Interface *const interface);

#endif 
