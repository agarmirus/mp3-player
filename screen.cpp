/*
 * Implementation of screen module
 *
 * Author: Lagtin Daniil
 * Group: IU7-23B
 */

#include <string.h>
#include "SPI.h"
#include "HCuOLED.h"
#include "screen.h"

void turn_on_animation(const Interface *const interface);

void shutdown_animation(const Interface *const interface);

void draw_track(const Interface *const interface);

void draw_buttons(const Interface *const interface);

void draw_levels(const Interface *const interface);

HCuOLED screen(SSD1306, CS, DS, PST);

Interface init_screen(void)
{
    screen.Reset();

    Interface interface;
    init_interface(&interface);
    
    screen.Brightness(interface->brightness);
    turn_on_animation();

    return interface;
}

void set_screen_brightness(const unsigned int8_t brightness)
{
    screen.Brightness(brightness);
}

