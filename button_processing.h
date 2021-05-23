/*
 * Module, which handles button clicks
 *
 * Call example:
 * int button[4];
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

const int BUTTON_0 = 5;
const int BUTTON_1 = 7;
const int BUTTON_2 = 8;
const int BUTTON_3 = 11;

void button_processsing(int *const button);

#endif
