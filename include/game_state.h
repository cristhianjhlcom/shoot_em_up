#ifndef GAME_STATE_H
#define GAME_STATE_H

#include "common.h"
#include "types.h"

typedef struct
{
    void (*logic)(void);
    void (*draw)(void);
} delegate_t;

typedef struct
{
    SDL_Renderer *renderer;
    SDL_Window *window;
    bool is_running;
} app_t;

typedef struct
{
    entity_t player;
    SDL_Event event;
    delegate_t delegate;
    int keyboard[MAX_KEYBOARD_KEYS];
    struct {
        entity_t fighter_head, *fighter_tail;
        entity_t bullet_head, *bullet_tail;
    } stage;
} game_state_t;

extern app_t app;
extern game_state_t game_state;

#endif  // GAME_STATE_H
