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

void blit(entity_t *entity)
{
    if (SDL_QueryTexture(entity->texture, NULL, NULL, &entity->w, &entity->h) < 0)
    {
        SDL_Log("[blit] %s\n", SDL_GetError());
        return;
    }
    SDL_Rect dest;
    dest.x = (int) entity->pos.x;
    dest.y = (int) entity->pos.y;
    dest.w = entity->w;
    dest.h = entity->h;
    SDL_RenderCopy(app.renderer, entity->texture, NULL, &dest);
}
