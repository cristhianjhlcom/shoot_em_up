#include "common.h"

#include "setup.h"

extern app_t app;

void init(void) {
    const int renderer_flags = SDL_RENDERER_ACCELERATED;
    const int window_flags = 0;

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL2 is not installed %s\n", SDL_GetError());
        exit(1);
    }

    app.window = SDL_CreateWindow(
        "Shooter 01",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        SCREEN_WIDTH,
        SCREEN_HEIGHT,
        window_flags
    );
    if (app.window == NULL) {
        printf(
            "Failed to open %d x %d window %s\n",
            SCREEN_WIDTH,
            SCREEN_HEIGHT,
            SDL_GetError()
        );
        exit(1);
    }

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");

    app.renderer = SDL_CreateRenderer(
        app.window,
        -1,
        renderer_flags
    );
    if (app.renderer == NULL) {
        printf("Failed to create renderer %s\n", SDL_GetError());
        exit(1);
    }

    IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);
}

void cleanup() {
    SDL_DestroyRenderer(app.renderer);
    SDL_DestroyWindow(app.window);
    SDL_Quit();
}

