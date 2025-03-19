#ifndef SOUNDS_H
#define SOUNDS_H

#include "common.h"

void init_sounds(void);
void load_music(const char *filename);
void play_music(int loop);
void play_sound(int id, int channel);

#endif // SOUNDS_H
