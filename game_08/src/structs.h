#pragma  once

#include "common.h"

typedef struct Delegate delegate_t;
typedef struct App app_t;
typedef struct Entity entity_t;
typedef struct Stage stage_t;

typedef struct Delegate {
    void (*logic)(void);
    void (*draw)(void);
} delegate_t;

typedef struct App {
    SDL_Renderer *renderer;
    SDL_Window *window;
    delegate_t delegate;
    int keyboard[MAX_KEYBOARD_KEYS];
} app_t;

typedef struct Entity {
    float x;
    float y;
    int w;
    int h;
    float dy;
    float dx;
    int health;
    int reload;
    int side;
    SDL_Texture *texture;
    entity_t *next;
} entity_t;

typedef struct Stage {
    entity_t fighter_head;
    entity_t *fighter_tail;
    entity_t bullet_head;
    entity_t *bullet_tail;
} stage_t;
