/*
 * Module, which handles button clicks
 *
 * Call example:
 * int button[3];
 * button_processing(button);
 *
 * Author: Sapozhkov Andrey
 * Group: IU7-23B
 */

#ifndef BUTTON_PROCESSING_H
#define BUTTON_PROCESSING_H

#include <Arduino.h>

#define BUTTON_PRESSED 1
#define BUTTON_NOT_PRESSED 0

#define BUTTONS_COUNT 3
#define INDEX_BUTTON_LEFT 0
#define INDEX_BUTTON_SELECT 1
#define INDEX_BUTTON_RIGHT 2

const PROGMEM int PIN_BUTTON_LEFT = 4;
const PROGMEM int PIN_BUTTON_SELECT = 5;
const PROGMEM int PIN_BUTTON_RIGHT = 8;

void button_processing(int *const button);

#endif

