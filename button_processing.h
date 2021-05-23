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

const PROGMEM int BUTTON_LEFT = 5;
const PROGMEM int BUTTON_SELECT = 7;
const PROGMEM int BUTTON_RIGHT = 8;

void button_processsing(int *const button);

#endif
