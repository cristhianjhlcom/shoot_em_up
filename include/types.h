#ifndef TYPES_H
#define TYPES_H

#include "common.h"

typedef struct
{
    struct
    {
        int x, y;
    } pos;
    SDL_Texture *texture;
} entity_t;

#endif  // TYPES_H
