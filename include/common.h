#ifndef COMMON_H
#define COMMON_H

#include "SDL2/SDL.h"
#include "SDL2/SDL_events.h"
#include "SDL2/SDL_timer.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_scancode.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#define MAX(a, b) (((a) > (b)) ? (a) : (b))
#define STRNCPY(dest, src, n) \
	strncpy(dest, src, n);    \
	dest[n - 1] = '\0'

#define FPS					60
#define SCREEN_WIDTH 		1280
#define SCREEN_HEIGHT 		720
#define PLAYER_SPEED 		4
#define PLAYER_BULLET_SPEED 16
#define MAX_KEYBOARD_KEYS 	350
#define SIDE_PLAYER			0
#define SIDE_ALIEN			1
#define ALIEN_BULLET_SPEED	8
#define MAX_STARS			500

#endif  // COMMON_H
