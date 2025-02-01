#pragma once

#include "common.h"

void prepare_scene(void);
void present_scene(void);
SDL_Texture *load_texture(char *filename);
void blit(SDL_Texture *texture, int x, int y);

