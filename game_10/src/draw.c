#include "../include/common.h"

extern app_t app;

void prepare_scene(void) {
    SDL_SetRenderDrawColor(app.renderer, 32, 32, 32, 255);
    SDL_RenderClear(app.renderer);
}

SDL_Texture *load_texture(const char *filename) {
    SDL_Texture *texture = IMG_LoadTexture(app.renderer, filename);
    if (texture == NULL) {
        printf("Texture load failed (%s) %s.\n", filename, SDL_GetError());
        exit(1);
    }
    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Loading %s", filename);
    return texture;
}

void blit(SDL_Texture *texture, int x, int y) {
    SDL_Rect dest;
    dest.x = x;
    dest.y = y;
    SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);
    SDL_RenderCopy(app.renderer, texture, NULL, &dest);
}

void blit_rect(SDL_Texture *texture, SDL_Rect *src, int x, int y) {
    SDL_Rect dest;
    dest.x = x;
    dest.y = y;
    dest.w = src->w;
    dest.h = src->h;

    SDL_RenderCopy(app.renderer, texture, src, &dest);
}

void present_scene(void) {
    SDL_RenderPresent(app.renderer);
}
