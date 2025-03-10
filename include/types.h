#ifndef TYPES_H
#define TYPES_H

#include "common.h"

typedef struct
{
    struct
    {
        int x, y;
    } pos;
    struct
    {
        int x, y;
    } delta;
    int w, h;
    int health;
    int speed;
    int fire;
    SDL_Texture *texture;
} entity_t;

#endif  // TYPES_H
