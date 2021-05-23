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
#define SCREEN_SCL 5 
#define SCREEN_SDA 4 

// Sizes
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64 

// Return codes
#define OK_SCREEN         0
#define ERROR_SCREEN_INIT 1

uint8_t init_screen(Interface *const interface);

void screen_shutdown(const Interface *const interface);

void draw_screen_frame(const Interface *const interface); // TODO

void check_for_timeout(); // TODO

void set_screen_brightness(const uint8_t brightness);

void set_screen_invert(const uint8_t type);

#endif 

