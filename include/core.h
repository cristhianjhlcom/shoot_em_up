#ifndef CORE_H
#define CORE_H

#include "common.h"
#include "game_state.h"
#include "background.h"
#include "sounds.h"
#include "texts.h"
#include "highscores.h"

bool init(void);
void init_game(void);
void cleanup(void);
void cap_frame_rate(long *then, float *remainder);

#endif  // CORE_H
