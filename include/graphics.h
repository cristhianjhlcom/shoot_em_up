#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "common.h"
#include "game_state.h"

void prepare_scene(void);
SDL_Texture *load_texture(const char *filename);
void blit_rect(SDL_Texture *texture, int x, int y, SDL_Rect *src);
void blit(SDL_Texture *texture, int x, int y);
void present_scene(void);

#endif  // GRAPHICS_H
