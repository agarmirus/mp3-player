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

void draw_button(const uint8_t *const pos, const uint8_t radius, 
                 const int8_t state, const int8_t type, const int8_t play);

void draw_buttons(const Interface *const interface); // todo

void draw_levels(const Interface *const interface); // todo

// Init screen class
Adafruit_SSD1306 screen(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire);

uint8_t init_screen(Interface *const interface)
{
    if (!(screen.begin(SSD1306_SWITCHCAPVCC)))
        return ERROR_SCREEN_INIT;

    screen.clearDisplay();

    screen.invertDisplay(interface->invert);
    set_screen_brightness(interface->brightness);
   
    screen.setTextColor(SSD1306_WHITE); 
    screen.setTextSize(DEFAULT_TEXT_SCALE);
    screen.setTextWrap(false);

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
                             SCREEN_HEIGHT - 2 * (j + 2), 
                             SSD1306_WHITE);

        screen.drawFastHLine(i + 2, j + 2, 
                             SCREEN_WIDTH - 2 * (i + 2),
                             SSD1306_WHITE);
        screen.drawFastHLine(i + 2, SCREEN_HEIGHT - j - 2, 
                             SCREEN_WIDTH - 2 * (i + 2), 
                             SSD1306_WHITE);
        
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

        screen.drawFastHLine(i, SCREEN_HEIGHT / 2 - 1, 
                             SCREEN_WIDTH - 2 * i,
                             SSD1306_WHITE);
        screen.drawFastHLine(i, SCREEN_HEIGHT / 2, 
                             SCREEN_WIDTH - 2 * i,
                             SSD1306_WHITE);
        
        screen.display();
    }

    screen.clearDisplay();
    screen.display();
}

void screen_shutdown(const Interface *const interface)
{
    shutdown_animation();

    /*
     * TODO Look for correct shutdown
     */
}

void draw_screen_frame(Interface *const interface)
{
    screen.clearDisplay();
    
    draw_track(interface);

    // Drawing lines
    screen.drawFastVLine(1, 1, SCREEN_HEIGHT - 2, SSD1306_WHITE);
    screen.drawFastVLine(SCREEN_WIDTH - 1, 1, SCREEN_HEIGHT - 2, SSD1306_WHITE);
    screen.drawFastHLine(1, 1, SCREEN_WIDTH - 2, SSD1306_WHITE);
    screen.drawFastVLine(1, SCREEN_HEIGHT - 1, SCREEN_WIDTH - 2, 
                         SSD1306_WHITE);

    draw_buttons(interface);
    draw_levels(interface);

    screen.display();
}

void draw_track(Interface *const interface)
{
    screen.setCursor(interface->cursor_pos, TEXT_Y);
    screen.print(interface->track);

    if (TEXT_LIM < interface->track_size)
    {
        if (-(interface->track_size * DEFAULT_TEXT_WIDTH) + DEFAULE_TEXT_OFFSET 
            >= interface->cursor_pos)
            interface->cursor_pos = SCREEN_WIDTH - DEFAULE_TEXT_OFFSET + 1;

        interface->cursor_pos--;
    }

    screen.fillRect(0, 0, DEFAULE_TEXT_OFFSET, SCREEN_HEIGHT, SSD1306_BLACK);
    screen.fillRect(SCREEN_WIDTH - DEFAULE_TEXT_OFFSET, 0, 
                    DEFAULE_TEXT_OFFSET, SCREEN_HEIGHT, SSD1306_BLACK);
}

void draw_button(const uint8_t *const pos, const uint8_t radius, 
                 const int8_t state, const int8_t type, const int8_t play)
{
    int accent;

    if (ACTIVE == state || PRESSED == state)
    {
        screen.fillCircle(pgm_read_byte(&pos[0]), pgm_read_byte(&pos[1]), 
                          radius, SSD1306_WHITE);
        accent = SSD1306_BLACK;
    }
    else
    {
        screen.drawCircle(pgm_read_byte(&pos[0]), pgm_read_byte(&pos[1]), 
                          radius, SSD1306_WHITE);
        accent = SSD1306_WHITE;
    }

    if (PRESSED != state)
    {
        if (BUTTON_PLAY == type)
        {
            if (PAUSE == play)
                screen.fillTriangle(pgm_read_byte(&pos[0]) + ICON_RATIO 
                                    * radius,
                                    pgm_read_byte(&pos[1]),
                                    pgm_read_byte(&pos[0]) - ICON_RATIO * radius
                                    * COS60,
                                    pgm_read_byte(&pos[1]) + ICON_RATIO * radius
                                    * SIN60,
                                    pgm_read_byte(&pos[0]) - ICON_RATIO * radius
                                    * COS60,
                                    pgm_read_byte(&pos[1]) - ICON_RATIO * radius
                                    * SIN60,
                                    accent);
            else if (PLAY == play)
            {
                screen.fillRect(pgm_read_byte(&pos[0]) - DIAG * radius,
                                pgm_read_byte(&pos[1]) - DIAG * radius,
                                PAUSE_BAR_RATIO * radius,
                                2 * DIAG * radius, accent);
                screen.fillRect(pgm_read_byte(&pos[0]) + DIAG * radius 
                                - PAUSE_BAR_RATIO * radius,
                                pgm_read_byte(&pos[1]) - DIAG * radius,
                                PAUSE_BAR_RATIO * radius,
                                2 * DIAG * radius, accent);
            }
        }
        else if (BUTTON_FORWARD == type)
            screen.drawTriangle(pgm_read_byte(&pos[0]) + ICON_RATIO * radius,
                                pgm_read_byte(&pos[1]),
                                pgm_read_byte(&pos[0]) - ICON_RATIO * radius
                                * COS60,
                                pgm_read_byte(&pos[1]) + ICON_RATIO * radius
                                * SIN60,
                                pgm_read_byte(&pos[0]) - ICON_RATIO * radius
                                * COS60,
                                pgm_read_byte(&pos[1]) - ICON_RATIO * radius
                                * SIN60,
                                accent);
        else if (BUTTON_PREVIOUS == type)
            screen.drawTriangle(pgm_read_byte(&pos[0]) - ICON_RATIO * radius,
                                pgm_read_byte(&pos[1]),
                                pgm_read_byte(&pos[0]) + ICON_RATIO * radius
                                * COS60,
                                pgm_read_byte(&pos[1]) + ICON_RATIO * radius
                                * SIN60,
                                pgm_read_byte(&pos[0]) + ICON_RATIO * radius
                                * COS60,
                                pgm_read_byte(&pos[1]) - ICON_RATIO * radius
                                * SIN60,
                                accent);
    }
}

void draw_buttons(const Interface *const interface)
{
    int8_t state;

    if (PLAY_BUTTON_PRESSED == interface->event)
        state = PRESSED;
    else if (BUTTON_PLAY == interface->block_item)
        state = ACTIVE;
    else
        state = INACTIVE;

    draw_button(POS_PLAY_BUTTON, RADIUS_PLAY_BUTTON, state, BUTTON_PLAY, 
                interface->state);

    if (FORWARD_BUTTON_PRESSED == interface->event)
        state = PRESSED;
    else if (BUTTON_FORWARD == interface->block_item)
        state = ACTIVE;
    else
        state = INACTIVE;

    draw_button(POS_FORWARD_BUTTON, RADIUS_FP_BUTTON, state, BUTTON_FORWARD, 
                NULL);

    if (PREVIOUS_BUTTON_PRESSED == interface->event)
        state = PRESSED;
    else if (BUTTON_PREVIOUS == interface->block_item)
        state = ACTIVE;
    else
        state = INACTIVE;

    draw_button(POS_PREVIOUS_BUTTON, RADIUS_FP_BUTTON, state, BUTTON_PREVIOUS, 
                NULL);
}

void draw_levels(const Interface *const interface)
{

}

void set_screen_brightness(const uint8_t brightness)
{
    screen.ssd1306_command(SSD1306_SETCONTRAST);
    screen.ssd1306_command(brightness);
}

void set_screen_invert(const uint8_t type)
{
    screen.invertDisplay(type);
}

