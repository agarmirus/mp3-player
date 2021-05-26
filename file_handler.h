//
//  file_handler.h
//  practice
//
//  Created by Волков Даниил Вячеславович on 26.05.2021.
//  Copyright © 2021 Волков Даниил Вячеславович. All rights reserved.
//

#include "DFMiniMp3.h"
#include <stdint.h>

void setup();

void waitMilliseconds(const uint16_t msWait);

void play(const int num);

void stop();

void play_needed_track(int file, int track);
