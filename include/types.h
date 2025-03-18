#ifndef TYPES_H
#define TYPES_H

#include "common.h"

typedef struct entity_t entity_t;
typedef struct debris_t debris_t;
typedef struct explosion_t explosion_t;
// typedef struct star_t star_t;

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
    int side;
    SDL_Texture *texture;
    entity_t *next;
};

struct explosion_t {
    struct {
        float x, y;
    } pos;
    struct {
        float x, y;
    } delta;
    struct {
        int r, g, b, a;
    } color;
    explosion_t *next;
};

struct debris_t {
    struct {
        float x, y;
    } pos;
    struct {
        float x, y;
    } delta;
    SDL_Rect rect;
    SDL_Texture *texture;
    int life;
    debris_t *next;
};

typedef struct
{
    struct {
        int x, y;
    } pos;
    int speed;
} star_t;

#endif  // TYPES_H
