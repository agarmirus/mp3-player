
#include "Interface.h"
#include "screen.h"

// #define _INIT_

Interface interface;
int8_t event;

void setup(void)
{
#ifdef _INIT_
    init_screen_eeprom();
#endif

    init_interface(&interface);
    init_screen(&interface);
}

void loop(void)
{
    // Get information about buttons

    event = get_event(&interface, /* buttons */);
    check_timer(&interface);

    // Get/set variables 
    // Do stuff ...

    draw_screen_frame(&interface);
    delay(100);
}

