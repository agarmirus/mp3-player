/*
 * Implementation of screen module
 *
 * Author: Lagtin Daniil
 * Group: IU7-23B
 */

#include <string.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <SPI.h>
#include <Wire.h>
#include "screen.h"

void turn_on_animation(const Interface *const interface);

void shutdown_animation(const Interface *const interface);

void draw_track(const Interface *const interface);

void draw_buttons(const Interface *const interface);

void draw_levels(const Interface *const interface);

Adafruit_SSD1306 screen(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_MOSI, SCREEN_CLK, 
SCREEN_DS, SCREEN_RES, SCREEN_CS);

uint8_t init_screen(Interface *const interface)
{
    if (!(screen.begin(SSD1306_SWITCHCAPVCC)))
        return ERROR_SCREEN_INIT;

    screen.clearDisplay();

    init_interface(interface);
    
    screen.invertDisplay(interface->invert);
    set_screen_brightness(interface->brightness);

    turn_on_animation(interface);

    return OK_SCREEN;
}

void set_screen_brightness(const uint8_t brightness)
{
    screen.ssd1306_command(SSD1306_SETCONTRAST);
    screen.ssd1306_command(brightness);
}

