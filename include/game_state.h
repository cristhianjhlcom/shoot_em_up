#ifndef GAME_STATE_H
#define GAME_STATE_H

#include "common.h"
#include "types.h"

typedef struct
{
    SDL_Renderer *renderer;
    SDL_Window *window;
    bool is_running;
    SDL_Event event;
} app_t;

typedef struct
{
    entity_t player;
    entity_t bullet;
    int up, down, left, right;
} game_state_t;

extern app_t app;
extern game_state_t game_state;

#endif  // GAME_STATE_H
