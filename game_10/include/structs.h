#pragma once

#include "common.h"

typedef struct Delegate delegate_t;
typedef struct App app_t;
typedef struct Entity entity_t;
typedef struct Stage stage_t;
typedef struct Explosion explosion_t;
typedef struct Debris debris_t;
typedef struct Star star_t;

typedef struct Explosion {
  float x, y;
  float dx, dy;
  int r, g, b, a;
  explosion_t *next;
} explosion_t;

typedef struct Debris {
  float x, y;
  float dx, dy;
  SDL_Rect rect;
  SDL_Texture *texture;
  int life;
  debris_t *next;
} debris_t;

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
  float x, y;
  int w, h;
  float dx, dy;
  int health, reload, side;
  SDL_Texture *texture;
  entity_t *next;
} entity_t;

typedef struct Stage {
  entity_t fighter_head, *fighter_tail;
  entity_t bullet_head, *bullet_tail;
  explosion_t explosion_head, *explosion_tail;
  debris_t debris_head, *debris_tail;
} stage_t;

typedef struct Star {
  int x, y;
  int speed;
} star_t;
