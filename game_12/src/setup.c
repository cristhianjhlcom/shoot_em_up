#include "common.h"

extern app_t app;

void init(void) {
    const int renderer_flags = SDL_RENDERER_ACCELERATED;
    const int window_flags = 0;

    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        printf("SDL2 is not installed %s\n", SDL_GetError());
        exit(1);
    }

    app.window = SDL_CreateWindow(
        "Shoot'em Up",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        SCREEN_WIDTH,
        SCREEN_HEIGHT,
        window_flags);
    if (app.window == NULL) {
        printf(
            "Failed to open %d x %d window %s\n",
            SCREEN_WIDTH,
            SCREEN_HEIGHT,
            SDL_GetError());
        exit(1);
    }

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");

    app.renderer = SDL_CreateRenderer(
        app.window,
        -1,
        renderer_flags);
    if (app.renderer == NULL) {
        printf("Failed to create renderer %s\n", SDL_GetError());
        exit(1);
    }

    if (!IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG)) {
        printf("IMG_Init failed %s\n", IMG_GetError());
        exit(1);
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) == -1) {
        printf("Couldn't initialize SDL Mixer\n");
        exit(1);
    }

    Mix_AllocateChannels(MAX_SND_CHANNELS);

    SDL_ShowCursor(0);
}

void cleanup() {
    SDL_DestroyRenderer(app.renderer);
    SDL_DestroyWindow(app.window);
    SDL_Quit();
}
