#include "button_processing.h"
#include "screen.h"
#include "file_handler.h"
#include "button_processing.h"
#include "Interface.h"

#define BUTTONS_COUNT 3

#define INDEX_BUTTON_LEFT 0
#define INDEX_BUTTON_SELECT 1
#define INDEX_BUTTON_RIGHT 2


void setup()
{
    // Initializing buttons ports
    
    pinMode(pgm_read_word(&BUTTON_LEFT), INPUT_PULLUP);
    pinMode(pgm_read_word(&BUTTON_SELECT), INPUT_PULLUP);
    pinMode(pgm_read_word(&BUTTON_RIGTH), INPUT_PULLUP);

    init_screen();  // Initializing screen
    setupDFM();  // Initializing DFMPlayer
    init_interface(Interface);  // Initializing interface
}

void loop()
{
    int buttons_flags[BUTTONS_COUNT] = {0};

    button_processing(buttons_flags);

    get_event(Interface, buttons_flags);
}
