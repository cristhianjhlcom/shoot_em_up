#ifndef TYPES_H
#define TYPES_H

#include "common.h"

typedef struct entity_t entity_t;

struct entity_t
{
    struct
    {
        float x, y;
    } pos;
    struct
    {
        float x, y;
    } delta;
    int w, h;
    int health;
    int reload;
    int speed;
    int fire;
    SDL_Texture *texture;
    entity_t *next;
};

#endif  // TYPES_H
