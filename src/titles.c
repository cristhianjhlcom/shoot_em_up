#include "titles.h"

static SDL_Texture *sdl2_texture;
static SDL_Texture *shooter_texture;
static int timeout;
static int reveal;

static void logic(void);
static void draw(void);
static void draw_logo(void);

void init_title(void)
{
    game_state.delegate.logic = logic;
    game_state.delegate.draw = draw;
    memset(game_state.keyboard, 0, sizeof(int) * MAX_KEYBOARD_KEYS);
    sdl2_texture = load_texture("assets/graphics/sdl2.png");
    shooter_texture = load_texture("assets/graphics/shooter.png");
    timeout = FPS * 5;
}

static void logic(void)
{
    do_background();
    do_star_field();
    if (reveal < SCREEN_HEIGHT)
    {
        reveal++;
    }
    if (--timeout <= 0)
    {
        init_highscores();
    }
    if (game_state.keyboard[SDL_SCANCODE_LCTRL])
    {
        init_stage();
    }
}

static void draw(void)
{
    draw_background();
    draw_star_field();
    draw_logo();
    if (timeout % 40 < 20)
    {
        draw_text(SCREEN_WIDTH / 2, 600, 255, 255, 255, TEXT_CENTER, "PRESS FIRE TO PLAY!");
    }
}

static void draw_logo(void)
{
    SDL_Rect r;
    r.x = 0;
    r.y = 0;
    if (SDL_QueryTexture(sdl2_texture, NULL, NULL, &r.w, &r.h) < 0)
    {
        printf("Cannot set sdl2 textures sizes values\n");
        exit(1);
    }
    r.h = MIN(reveal, r.h);
    blit_rect(sdl2_texture, (SCREEN_WIDTH / 2) - (r.w / 2), 100, &r);
    if (SDL_QueryTexture(shooter_texture, NULL, NULL, &r.w, &r.h) < 0)
    {
        printf("Cannot set shooter texture sizes values\n");
        exit(1);
    }
    r.h = MIN(reveal, r.h);
    blit_rect(shooter_texture, (SCREEN_WIDTH / 2) - (r.w / 2), 250, &r);
}
