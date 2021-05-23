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

#include "button_processing.h"

void button_processsing(int *const button)
{
    button[0] = digitalRead(BUTTON_LEFT) == LOW ? BUTTON_PRESSED : BUTTON_NOT_PRESSED;
    button[1] = digitalRead(BUTTON_SELECT) == LOW ? BUTTON_PRESSED : BUTTON_NOT_PRESSED;
    button[2] = digitalRead(BUTTON_RIGHT) == LOW ? BUTTON_PRESSED : BUTTON_NOT_PRESSED;
}