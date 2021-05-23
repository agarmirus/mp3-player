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

#include "button_processing.h"

void button_processsing(int *const button)
{
    pinMode(BUTTON_0, INPUT_PULLDOWN);
    pinMode(BUTTON_1, INPUT_PULLDOWN);
    pinMode(BUTTON_2, INPUT_PULLDOWN);
    pinMode(BUTTON_3, INPUT_PULLDOWN);

    button[0] = digitalRead(BUTTON_0) == LOW ? BUTTON_PRESSED : BUTTON_NOT_PRESSED;
    button[1] = digitalRead(BUTTON_1) == LOW ? BUTTON_PRESSED : BUTTON_NOT_PRESSED;
    button[2] = digitalRead(BUTTON_2) == LOW ? BUTTON_PRESSED : BUTTON_NOT_PRESSED;
    button[3] = digitalRead(BUTTON_3) == LOW ? BUTTON_PRESSED : BUTTON_NOT_PRESSED;
}