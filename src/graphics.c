#include "graphics.h"

static SDL_Texture *get_texture(const char *name);
static void add_texture_to_cache(const char *name, SDL_Texture *sdl_texture);

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
    SDL_Texture *texture;
    texture = get_texture(filename);
    /*
    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Loading %s", filename);
    texture = IMG_LoadTexture(app.renderer, filename);
    */
    if (texture == NULL)
    {
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Loading %s", filename);
        texture = IMG_LoadTexture(app.renderer, filename);
        add_texture_to_cache(filename, texture);
        // SDL_Log("Load texture failed %s\n", SDL_GetError());
    }
    return texture;
}

static SDL_Texture *get_texture(const char *name)
{
    texture_t *t;
    for (t = game_state.stage.texture_head.next; t != NULL; t = t->next)
    {
        if (strcmp(t->name, name) == 0)
        {
            return t->texture;
        }
    }
    return NULL;
}

static void add_texture_to_cache(const char *name, SDL_Texture *sdl_texture)
{
    texture_t *texture;
    texture = malloc(sizeof(texture_t));
    if (texture == NULL)
    {
        printf("Memory Allocation Failed.\n");
        exit(1);
    }
    memset(texture, 0, sizeof(texture_t));
    game_state.stage.texture_tail->next = texture;
    game_state.stage.texture_tail = texture;
    STRNCPY(texture->name, name, MAX_NAME_LENGTH);
    texture->texture = sdl_texture;
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
