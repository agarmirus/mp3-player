/*
 * Implementation of screen module
 *
 * Author: Lagtin Daniil
 * Group: IU7-23B
 */

#include <string.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <EEPROM.h>
#include <SPI.h>
#include <Wire.h>
#include "screen.h"

void turn_on_animation(void);

void shutdown_animation(void);

void draw_track(const Interface *const interface);

void draw_buttons(const Interface *const interface);

void draw_levels(const Interface *const interface);

// Init screen class
Adafruit_SSD1306 screen(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire);

uint8_t init_screen(Interface *const interface)
{
    if (!(screen.begin(SSD1306_SWITCHCAPVCC)))
        return ERROR_SCREEN_INIT;

    screen.clearDisplay();

    init_interface(interface);
    
    screen.invertDisplay(interface->invert);
    set_screen_brightness(interface->brightness);

    turn_on_animation();

    return OK_SCREEN;
}

void turn_on_animation(void)
{
    screen.clearDisplay();
    screen.display();

    for (float i = SCREEN_WIDTH / 2, j = SCREEN_HEIGHT / 2;
        i >= 0;
        i--, j = i / SCREEN_WIDTH * SCREEN_HEIGHT)
    {
        screen.fillRect(i, j, SCREEN_WIDTH - 2 * i, SCREEN_HEIGHT - 2 * j, 
        SSD1306_WHITE);
        screen.display();
    }

    screen.clearDisplay();

    for (float i = SCREEN_WIDTH / 2, j = SCREEN_HEIGHT / 2;
        i >= 0;
        i--, j = i / SCREEN_WIDTH * SCREEN_HEIGHT)
    {
        screen.fillRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, SSD1306_WHITE);
        screen.fillRect(i, j, SCREEN_WIDTH - 2 * i, SCREEN_HEIGHT - 2 * j, 
        SSD1306_BLACK);

        screen.drawFastVLine(i + 2, j + 2, SCREEN_HEIGHT - 2 * (j + 2), 
        SSD1306_WHITE);
        screen.drawFastVLine(SCREEN_WIDTH - i - 2, j + 2, 
        SCREEN_HEIGHT - 2 * (j + 2), SSD1306_WHITE);

        screen.drawFastHLine(i + 2, j + 2, SCREEN_WIDTH - 2 * (i + 2),
        SSD1306_WHITE);
        screen.drawFastHLine(i + 2, SCREEN_HEIGHT - j - 2, 
        SCREEN_WIDTH - 2 * (i + 2), SSD1306_WHITE);
        
        screen.display();
        screen.clearDisplay();
    }
}

void shutdown_animation(void)
{
    for (int i = 0; i <= SCREEN_HEIGHT / 2; i++)
    {
        screen.drawFastHLine(0, i, SCREEN_WIDTH, SSD1306_WHITE);
        screen.drawFastHLine(0, SCREEN_HEIGHT - i, SCREEN_WIDTH, SSD1306_WHITE);
        screen.display();
    }   

    for (int i = 0; i <= SCREEN_HEIGHT / 2 - 1; i++)
    {
        screen.drawFastHLine(0, i, SCREEN_WIDTH, SSD1306_BLACK);
        screen.drawFastHLine(0, SCREEN_HEIGHT - i, SCREEN_WIDTH, SSD1306_BLACK);
        screen.display();
    }
    
    screen.clearDisplay();

    for (int i = 0; i < SCREEN_WIDTH / 2; i++)
    {
        screen.clearDisplay();
        screen.drawFastHLine(i, SCREEN_HEIGHT / 2 - 1, SCREEN_WIDTH - 2 * i,
        SSD1306_WHITE);
        screen.drawFastHLine(i, SCREEN_HEIGHT / 2, SCREEN_WIDTH - 2 * i,
        SSD1306_WHITE);
        screen.display();
    }

    screen.clearDisplay();
    screen.display();
}

void screen_shutdown(Interface *const interface)
{
    EEPROM.update(BRIGHTNESS_BYTE, interface->brightness);
    EEPROM.update(VOLUME_BYTE, interface->volume);
    EEPROM.update(INVERT_BYTE, interface->invert);
    EEPROM.update(MUTE_BYTE, interface->mute);

    shutdown_animation();

    /*
     * TODO Look for correct shutdown
     */
}

void set_screen_brightness(const uint8_t brightness)
{
    screen.ssd1306_command(SSD1306_SETCONTRAST);
    screen.ssd1306_command(brightness);
}

