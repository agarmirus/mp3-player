//  file_handler.h
//  practice
//
//  Created by Волков Даниил Вячеславович
//  Copyright © 2021 Волков Даниил Вячеславович. All rights reserved.
//

#ifndef FILE_HANDLER_H
#define FILE_HANDLER_H

void setupDFM(uint_8 volume);

void play(const int num);

void stop_play();

void pause();

void play_needed_track(int file, int track);

void set_volume(uint8_t volume);

#endif
