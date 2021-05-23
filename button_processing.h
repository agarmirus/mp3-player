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

#define BUTTON_0 D2
#define BUTTON_1 D4
#define BUTTON_2 D5
#define BUTTON_3 D8

void button_processsing(int *const button);

#endif
