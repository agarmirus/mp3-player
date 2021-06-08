//
//  file_handler.h
//  practice
//
//  Created by Волков Даниил Вячеславович on 26.05.2021.
//  Copyright © 2021 Волков Даниил Вячеславович. All rights reserved.
//

#ifndef FILE_HANDLER_H
#define FILE_HANDLER_H


#include "DFMiniMp3.h"
#include <stdint.h>

void setupDFM();

void waitMilliseconds(const uint16_t msWait);

void play(const int num);

void stop();

void pause();

void play_needed_track(int file, int track);

#endif
