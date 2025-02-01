#include <SDL2/SDL.h>
#include <SDL2/SDL_error.h>
#include <stdlib.h>
#include <stdio.h>

void init_SDL() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("SDL2 is not installed %s\n", SDL_GetError());
        exit(1);
    }
    printf("SDL2 installed successfully.\n");
}

void cleanup() {
    SDL_Quit();
}

