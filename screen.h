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
const PROGMEM int8_t SCREEN_CS = 10; // Chip select pin
const PROGMEM int8_t SCREEN_DS = 9; // Data/command pin
const PROGMEM int8_t SCREEN_RES = 8; // Reset pin
const PROGMEM int8_t SCREEN_CLK = 13; // CLK Clock pin
const PROGMEM int8_t SCREEN_MOSI = 11; // MOSI pin

// Sizes
const PROGMEM uint8_t SCREEN_WIDTH = 128;
const PROGMEM uint8_t SCREEN_HEIGHT = 64; 

// Return codes
const PROGMEM uint8_t OK_SCREEN = 0;
const PROGMEM uint8_t ERROR_SCREEN_INIT = 1;

uint8_t init_screen(Interface *const interface);

void draw_screen_frame(Interface *const interface);

void set_screen_brightness(const uint8_t brightness);

#endif 

