#include "background.h"

static SDL_Texture *background;
static int background_x;
static star_t stars[MAX_STARS];

void init_background(void)
{
    background = load_texture("assets/graphics/background.png");
    background_x = 0;
}

void init_star_field(void)
{
    for (int idx = 0; idx < MAX_STARS; idx++)
    {
        stars[idx].pos.x = rand() % SCREEN_WIDTH;
        stars[idx].pos.y = rand() % SCREEN_HEIGHT;
        stars[idx].speed = 1 + rand() % 8;
    }
}

void do_background(void)
{
    if (--background_x < -SCREEN_WIDTH)
    {
        background_x = 0;
    }
}

void do_star_field(void)
{
    for (int idx = 0; idx < MAX_STARS; idx++)
    {
        stars[idx].pos.x -= stars[idx].speed;
        if (stars[idx].pos.x < 0)
        {
            stars[idx].pos.x = SCREEN_WIDTH + stars[idx].pos.x;
        }
    }
}


void draw_background(void)
{
    SDL_Rect dest;
    for (int x = background_x; x < SCREEN_WIDTH; x += SCREEN_WIDTH)
    {
        dest.x = x;
        dest.y = 0;
        dest.w = SCREEN_WIDTH;
        dest.h = SCREEN_HEIGHT;
        SDL_RenderCopy(app.renderer, background, NULL, &dest);
    }
}

void draw_star_field(void)
{
    int i, c;
    for (i = 0; i < MAX_STARS; i++)
    {
        c = 32 * stars[i].speed;
        SDL_SetRenderDrawColor(app.renderer, (Uint8)c, (Uint8)c, (Uint8)c, 255);
        SDL_RenderDrawLine(
            app.renderer,
            (Uint8)stars[i].pos.x,
            (Uint8)stars[i].pos.y,
            (Uint8)stars[i].pos.x + 3,
            (Uint8)stars[i].pos.y);
    }
}
