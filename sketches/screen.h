/*
 * Module, that allow to render GUI of a MP3-Player 
 *
 * Author: Lagutin Daniil
 * Group: IU7-23B
 */

#ifndef _SCREEN_H_
#define _SCREEN_H_

#include <stdint.h>
#include <avr/pgmspace.h>
#include "Interface.h"

// Pins
#define SCREEN_SCL 5 
#define SCREEN_SDA 4 

// Sizes
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64 

// Text
#define DEFAULT_TEXT_SCALE   2
#define DEFAULT_TEXT_WIDTH  12
#define DEFAULT_TEXT_HEIGHT 14
#define TEXT_LIM            10
#define DEFAULE_TEXT_OFFSET  4
#define TEXT_Y               8

// Buttons
#define PRESSED     2
#define ACTIVE      1
#define INACTIVE    0
#define RADIUS_PLAY_BUTTON 13
#define RADIUS_FP_BUTTON    8
const PROGMEM uint8_t POS_PLAY_BUTTON[] = {80, 41};
const PROGMEM uint8_t POS_PREVIOUS_BUTTON[] = {54, 41};
const PROGMEM uint8_t POS_FORWARD_BUTTON[] = {106, 41};

#define ICON_RATIO      0.7
#define PAUSE_BAR_RATIO 0.2
#define SIN60           0.8660254
#define COS60           0.5
#define DIAG            0.707106

// Return codes
#define OK_SCREEN         0
#define ERROR_SCREEN_INIT 1

uint8_t init_screen(Interface *const interface);

void screen_shutdown(const Interface *const interface); // TODO

void draw_screen_frame(Interface *const interface); // TODO

void set_screen_brightness(const uint8_t brightness);

void set_screen_invert(const uint8_t type);

#endif 

