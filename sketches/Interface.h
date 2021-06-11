/*
 * Module, that allow to interact with GUI of a MP3-Player
 *
 * Author: Lagutin Daniil
 * Group: IU7-23B
 */

#ifndef _INTERFACE_H_
#define _INTERFACE_H_

#include <stdint.h>
#include <avr/pgmspace.h>

// Interface elements
// BLOCKS
#define BLOCK_LEVEL  0
#define BLOCK_BUTTON 1
#define BLOCK_ERROR  2

#define START_INDEX        0
#define PLAIN_BLOCK_AMOUNT 2
const PROGMEM int8_t MAX_BLOCK_ELEMENTS[] = {2, 2};

// BUTTON ITEMS
#define BUTTON_PREVIOUS 0
#define BUTTON_PLAY     1
#define BUTTON_FORWARD  2

// LEVEL TYPES
#define LEVEL_AMOUNT     2
#define LEVEL_VOLUME     0
#define LEVEL_BRIGHTNESS 1

// LEVEL MODES
#define LEVEL_SELECT 0
#define LEVEL_ADJUST 1

// LEVEL ITEMS
#define LEVEL_DECREASE 0
#define LEVEL_BUTTON   1
#define LEVEL_INCREASE 2

// ERROR ITEMS
#define ERROR_OK 1

// Values
#define MAX_STRING             255
#define MAX_LEVEL_VOLUME        30
#define MAX_LEVEL_BRIGHTNESS   410
#define BRIGHTNESS_OVERFLOW    156
#define PRECHARGE_LOW           16
#define PRECHARGE_HIGH           0
#define BRIGHTNESS_STEP         82
#define VOLUME_STEP              3
#define VOLUME_AMOUNT           10
#define BRIGHTNESS_AMOUNT        5
#define INCREASE                 1
#define DECREASE                 2
#define FADED_BRIGHTNESS_SCALE   4 // To be tested
#define FADED                    1
#define UNFADED                  0
#define ADJUST_TIME           4000 // To be tested
#define SLEEP_TIME           10000 // To be tested

const PROGMEM char TRACK_PLACEHOLDER[] = "Nothing is playing";
#define TRACK_NUM_FORMAT "Track #%d"

// EEPROM
#define MUTE_BYTE             100
#define INVERT_BYTE           101
#define VOLUME_BYTE           102
#define BRIGHTNESS_BYTE_START 103

#define DEF_VOLUME      15
#define DEF_BRIGHTNESS 246
#define DEF_MUTE         0
#define DEF_INVERT       0

// States
#define PLAY  1
#define PAUSE 2

// Events
#define NULL_EVENT               0
#define PLAY_BUTTON_PRESSED      1
#define FORWARD_BUTTON_PRESSED   2
#define PREVIOUS_BUTTON_PRESSED  3
#define VOLUME_CHANGED           4
#define MUTE_TOGGLED             5
#define BRIGHTNESS_CHANGED       6
#define INVERT_TOGGLED           7
#define BLOCK_CHANGED            8
#define ITEM_CHANGED             9
#define LEVEL_CHANGED           10
#define LEVEL_MODE_CHANGED      11
#define OK_BUTTON_ERROR_PRESSED 12

// Main interface item 
typedef struct 
{
    // settings
    uint16_t brightness;
    uint8_t volume; 
    int8_t mute;
    int8_t invert;
    uint8_t state;
    uint8_t fade;
    unsigned long last_call; 
    
    // track preferences
    char track[MAX_STRING + 1];
    uint8_t track_size;
    int16_t cursor_pos;

    // interface
    int8_t event;
    int8_t active_block;
    int8_t block_item;

    int8_t level_type;
    int8_t level_mode;

    // errors
    int8_t error;
} Interface;

void init_interface(Interface *const interface);

void init_screen_eeprom(void);

void update_screen_eeprom(const Interface *const interface);

void check_timer(Interface *const interface);

void shudown_interface(const Interface *const interface);

void step_brightness(Interface *const interface, const int8_t type);

void toggle_invert(Interface *const interface);

void step_volume(Interface *const interface, const int8_t type);

void toggle_mute(Interface *const interface);

void set_track(Interface *const interface, const char *const track);

void set_track(Interface *const interface, const int32_t num);

void set_error(Interface *const interface, const int8_t  error);

void set_cursor(Interface *const interface, const int16_t pos);

int8_t get_event(Interface *const interface, const int *const buttons);

int8_t get_state(const Interface *const interface);

uint8_t get_volume(const Interface *const interface);

#endif 
