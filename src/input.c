#include "input.h"

static void do_key_down(SDL_KeyboardEvent *event)
{
    if (event->repeat == 0)
    {
        if (event->keysym.scancode == SDL_SCANCODE_UP)
        {
            game_state.up = 1;
        }

        if (event->keysym.scancode == SDL_SCANCODE_DOWN)
        {
            game_state.down = 1;
        }

        if (event->keysym.scancode == SDL_SCANCODE_LEFT)
        {
            game_state.left = 1;
        }

        if (event->keysym.scancode == SDL_SCANCODE_RIGHT)
        {
            game_state.right = 1;
        }
    }
}

static void do_key_up(SDL_KeyboardEvent *event)
{
    if (event->repeat == 0)
    {
        if (event->keysym.scancode == SDL_SCANCODE_UP)
        {
            game_state.up = 0;
        }

        if (event->keysym.scancode == SDL_SCANCODE_DOWN)
        {
            game_state.down = 0;
        }

        if (event->keysym.scancode == SDL_SCANCODE_LEFT)
        {
            game_state.left = 0;
        }

        if (event->keysym.scancode == SDL_SCANCODE_RIGHT)
        {
            game_state.right = 0;
        }
    }
}

void inputs(void)
{
    while (SDL_PollEvent(&app.event))
    {
        switch (app.event.type)
        {
            case SDL_QUIT:
                app.is_running = false;
                break;
            case SDL_KEYDOWN:
                do_key_down(&app.event.key);
                break;
            case SDL_KEYUP:
                do_key_up(&app.event.key);
                break;
            default:
                break;
        }
    }
}
