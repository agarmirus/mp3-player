/*
 * Module, that allow to render GUI of a MP3-Player 
 *
 * Author: Lagutin Daniil
 * Group: IU7-23B
 */

#include <stdlib.h>
#include "Interface.h"

// Pins
//TODO
const PROGMEM int8_t CS = 0; // Chip select pin
const PROGMEM int8_t DS = 0; // Data/command pin
const PROGMEM int8_t RST = 0; // Reset pin
//

Interface init_screen(void);

void draw_screen_frame(Interface *const interface);

void set_screen_brightness(const unsigned int8_t brightness);

