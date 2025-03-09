#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "common.h"
#include "game_state.h"

void prepare_scene(void);
SDL_Texture *load_texture(const char *filename);
void blit(entity_t *entity);
void present_scene(void);

#endif  // GRAPHICS_H
