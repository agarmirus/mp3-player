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

void draw_track(Interface *const interface);

void draw_triangle(const uint8_t *const pos, const uint8_t radius, 
                   const bool fill, const int8_t color, const float scale, 
                   const int8_t side);

void draw_button(const uint8_t *const pos, const uint8_t radius, 
                 const int8_t state, const int8_t type, const int8_t play);

void draw_buttons(const Interface *const interface);

void draw_levels(const Interface *const interface); 

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
    screen.drawFastVLine(SCREEN_WIDTH - 2, 1, SCREEN_HEIGHT - 2, SSD1306_WHITE);
    screen.drawFastHLine(1, 1, SCREEN_WIDTH - 2, SSD1306_WHITE);
    screen.drawFastHLine(1, SCREEN_HEIGHT - 2, SCREEN_WIDTH - 2, 
                         SSD1306_WHITE);

    draw_buttons(interface);
    draw_levels(interface);

    screen.display();
}

void draw_track(Interface *const interface)
{
    screen.setTextSize(DEFAULT_TEXT_SCALE);
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

void draw_triangle(const uint8_t *const pos, const uint8_t radius, 
                   const bool fill, const int8_t color, const float scale,
                   const int8_t side)
{
    uint8_t pos_modified[] = {pgm_read_byte(&pos[0]) + side * scale * radius,
                              pgm_read_byte(&pos[1]),
                              pgm_read_byte(&pos[0]) - side * scale * radius
                              * COS60,
                              pgm_read_byte(&pos[1]) + scale * radius * SIN60,
                              pgm_read_byte(&pos[0]) - side * scale * radius  
                              * COS60,
                              pgm_read_byte(&pos[1]) - scale * radius * SIN60
                              };

    if (fill)
        screen.fillTriangle(pos_modified[0], pos_modified[1], pos_modified[2], 
                            pos_modified[3], pos_modified[4], pos_modified[5], 
                            color);
    else
        screen.drawTriangle(pos_modified[0], pos_modified[1], pos_modified[2], 
                            pos_modified[3], pos_modified[4], pos_modified[5], 
                            color);
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
                draw_triangle(pos, radius, true, accent, ICON_RATIO, TLEFT);
            else if (PLAY == play)
            {
                uint8_t width = PAUSE_BAR_RATIO * radius;
                uint8_t height = 2 * radius * ICON_RATIO;

                screen.fillRect(pgm_read_byte(&pos[0]) - ICON_RATIO * DIAG 
                                * radius + width,
                                pgm_read_byte(&pos[1]) - height / 2,
                                width, height, accent);
                screen.fillRect(pgm_read_byte(&pos[0]) + ICON_RATIO * DIAG 
                                * radius - width,
                                pgm_read_byte(&pos[1]) - height / 2,
                                width, height, accent);
            }
        }
        else if (BUTTON_FORWARD == type)
            draw_triangle(pos, radius, false, accent, ICON_RATIO, TLEFT);
        else if (BUTTON_PREVIOUS == type)
            draw_triangle(pos, radius, false, accent, ICON_RATIO, TRIGHT);
    }
}

void draw_buttons(const Interface *const interface)
{
    int8_t state;

    if (PLAY_BUTTON_PRESSED == interface->event)
        state = PRESSED;
    else if (BLOCK_BUTTON == interface->active_block 
             && BUTTON_PLAY == interface->block_item)
        state = ACTIVE;
    else
        state = INACTIVE;

    draw_button(POS_PLAY_BUTTON, RADIUS_PLAY_BUTTON, state, BUTTON_PLAY, 
                interface->state);

    if (FORWARD_BUTTON_PRESSED == interface->event)
        state = PRESSED;
    else if (BLOCK_BUTTON == interface->active_block 
             && BUTTON_FORWARD == interface->block_item)
        state = ACTIVE;
    else
        state = INACTIVE;

    draw_button(POS_FORWARD_BUTTON, RADIUS_FP_BUTTON, state, BUTTON_FORWARD, 
                NULL);

    if (PREVIOUS_BUTTON_PRESSED == interface->event)
        state = PRESSED;
    else if (BLOCK_BUTTON == interface->active_block 
             && BUTTON_PREVIOUS == interface->block_item)
        state = ACTIVE;
    else
        state = INACTIVE;

    draw_button(POS_PREVIOUS_BUTTON, RADIUS_FP_BUTTON, state, BUTTON_PREVIOUS, 
                NULL);
}

void draw_levels(const Interface *const interface)
{
    int8_t value, diff, amount, height;
    
    if ((LEVEL_VOLUME == interface->level_type && !interface->mute)
        || LEVEL_BRIGHTNESS == interface->level_type)
    {
        if (LEVEL_VOLUME == interface->level_type)
        {
            value = interface->volume / VOLUME_STEP;
            diff = VOLUME_DIFF;
            amount = VOLUME_AMOUNT;
        }
        else
        {
            value = interface->brightness / BRIGHTNESS_STEP;
            diff = BRIGHTNESS_DIFF;
            amount = BRIGHTNESS_AMOUNT;
        }
    
        for (float i = 0; i < value; i++)
        {
            height = (i + 1) / amount * LEVEL_HEIGHT; 
            screen.fillRect(pgm_read_byte(&POS_LINE[0]) + 1 + diff + 2 
                            * diff * i,
                            pgm_read_byte(&POS_LINE[1]) - 1 - height, diff,
                            height, SSD1306_WHITE);
        }
    }
    
    if (LEVEL_SELECT == interface->level_mode 
        || LEVEL_ADJUST == interface->level_mode && (millis() / MLS_TO_MS) % 2)
        for (int i = 0; i < LEVEL_LINE_WIDTH; i++)
            screen.drawFastHLine(pgm_read_byte(&POS_LINE[0]), 
                                 pgm_read_byte(&POS_LINE[1]) + i,
                                 LEVEL_LINE_LENGTH, SSD1306_WHITE);
  
    screen.setTextSize(LEVEL_TEXT_SCALE);
    screen.setCursor(pgm_read_byte(&POS_LEFT_ARROW[0]) + LEVEL_ARROW_SIZE,
                     pgm_read_byte(&POS_LEFT_ARROW[1]) - LEVEL_ARROW_SIZE);

    if (LEVEL_VOLUME == interface->level_type)  
        screen.print(TEXT_VOLUME);
    else
        screen.print(TEXT_BRIGHTNESS);
    
    bool state;
    
    if (BLOCK_LEVEL == interface->active_block 
        && LEVEL_DECREASE == interface->block_item)
        state = true;
    else
        state = false;
         
    draw_triangle(POS_LEFT_ARROW, LEVEL_ARROW_SIZE, state, SSD1306_WHITE, 
                  LEVEL_ARROW_SCALE, TRIGHT);
    
    if (BLOCK_LEVEL == interface->active_block 
        && LEVEL_INCREASE == interface->block_item)
        state = true;
    else
        state = false;
         
    draw_triangle(POS_RIGHT_ARROW, LEVEL_ARROW_SIZE, state, SSD1306_WHITE, 
                  LEVEL_ARROW_SCALE, TLEFT);

    if (BLOCK_LEVEL == interface->active_block 
        && LEVEL_BUTTON == interface->block_item)
        screen.drawFastHLine(pgm_read_byte(&POS_LEFT_ARROW[0]) 
                             + LEVEL_ARROW_SIZE,
                             pgm_read_byte(&POS_LEFT_ARROW[1]) 
                             + LEVEL_ARROW_SIZE,
                             LEVEL_CHARS * DEFAULT_TEXT_WIDTH 
                             / DEFAULT_TEXT_SCALE,
                             SSD1306_WHITE);

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

