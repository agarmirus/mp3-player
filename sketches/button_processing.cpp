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

void button_processing(int *const button)
{
    button[INDEX_BUTTON_LEFT] = (digitalRead(pgm_read_word(&BUTTON_LEFT)) == LOW) ? BUTTON_PRESSED : BUTTON_NOT_PRESSED;
    button[INDEX_BUTTON_SELECT] = (digitalRead(pgm_read_word(&BUTTON_SELECT)) == LOW) ? BUTTON_PRESSED : BUTTON_NOT_PRESSED;
    button[INDEX_BUTTON_RIGHT] = (digitalRead(pgm_read_word(&BUTTON_RIGHT)) == LOW) ? BUTTON_PRESSED : BUTTON_NOT_PRESSED;
}
