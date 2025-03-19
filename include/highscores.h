#ifndef HIGHSCORES_H
#define HIGHSCORES_H

#include "common.h"
#include "types.h"
#include "game_state.h"
#include "stage.h"
#include "background.h"
#include "texts.h"

void init_highscore_table(void);
void init_highscores(void);
void add_highscore(int score);

#endif // HIGHSCORES_H
