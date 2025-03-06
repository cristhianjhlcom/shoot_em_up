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

void blit(SDL_Texture *texture, int x, int y)
{
    SDL_Rect dest = (SDL_Rect){
        .x = x,
        .y = y,
    };
    if (SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h) < 0)
    {
        SDL_Log("Error getting texture sizes %s\n", SDL_GetError());
        return;
    }
    SDL_RenderCopy(app.renderer, texture, NULL, &dest);
}
