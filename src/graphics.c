#include "graphics.h"

void prepare_scene(void)
{
    SDL_SetRenderDrawColor(app.renderer, 96, 128, 255, 255);
    SDL_RenderClear(app.renderer);
}

void present_scene(void)
{
    SDL_RenderPresent(app.renderer);
}

SDL_Texture *load_texture(const char *filename)
{
    SDL_Texture *texture = NULL;
    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Loading %s", filename);
    texture = IMG_LoadTexture(app.renderer, filename);
    if (texture == NULL)
    {
        SDL_Log("Load texture failed %s\n", SDL_GetError());
        return NULL;
    }
    return texture;
}

void blit_rect(SDL_Texture *texture, int x, int y, SDL_Rect *src)
{
    SDL_Rect dest;
    dest.x = x;
    dest.y = y;
    dest.w = src->w,
    dest.h = src->h;
    SDL_RenderCopy(app.renderer, texture, src, &dest);
}

void blit(SDL_Texture *texture, int x, int y)
{
    int w, h;
    if (SDL_QueryTexture(texture, NULL, NULL, &w, &h) < 0)
    {
        SDL_Log("[blit] %s\n", SDL_GetError());
        return;
    }
    SDL_Rect dest;
    dest.x = x;
    dest.y = y;
    dest.w = w;
    dest.h = h;
    SDL_RenderCopy(app.renderer, texture, NULL, &dest);
}
