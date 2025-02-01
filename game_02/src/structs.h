#pragma  once

#include "common.h"

typedef struct App app_t;
typedef struct Entity entity_t;

typedef struct App {
    SDL_Renderer *renderer;
    SDL_Window *window;
} app_t;

typedef struct Entity {
    int x;
    int y;
    SDL_Texture *texture;
} entity_t;
