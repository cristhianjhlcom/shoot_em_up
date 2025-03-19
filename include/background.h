#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "common.h"
#include "graphics.h"
#include "types.h"
#include "game_state.h"

void init_background(void);
void init_star_field(void);
void do_background(void);
void do_star_field(void);
void draw_background(void);
void draw_star_field(void);

#endif // BACKGROUND_H
