/*
 * Module, that allow to render GUI of a MP3-Player 
 *
 * Author: Lagutin Daniil
 * Group: IU7-23B
 */

#ifndef SCREEN_H
#define SCREEN_H

#include <stdint.h>
#include <avr/pgmspace.h>
#include "Interface.h"

// Pins
const PROGMEM int8_t SCREEN_SCL = 5; 
const PROGMEM int8_t SCREEN_SDA = 4; 

// Sizes
const PROGMEM uint8_t SCREEN_WIDTH = 128;
const PROGMEM uint8_t SCREEN_HEIGHT = 64; 

// Return codes
const PROGMEM uint8_t OK_SCREEN = 0;
const PROGMEM uint8_t ERROR_SCREEN_INIT = 1;

uint8_t init_screen(Interface *const interface);

void screen_shutdown(Interface *const interface);

void draw_screen_frame(Interface *const interface);

void set_screen_brightness(const uint8_t brightness);

#endif 

