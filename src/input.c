#include "input.h"

static void do_key_down(SDL_KeyboardEvent *event)
{
    if (event->repeat == 0 && event->keysym.scancode < MAX_KEYBOARD_KEYS)
    {
        game_state.keyboard[event->keysym.scancode] = 1;
    }
}

static void do_key_up(SDL_KeyboardEvent *event)
{
    if (event->repeat == 0 && event->keysym.scancode < MAX_KEYBOARD_KEYS)
    {
        game_state.keyboard[event->keysym.scancode] = 0;
    }
}

void inputs(void)
{
    memset(game_state.input_text, '\0', MAX_LINE_LENGTH);
    while (SDL_PollEvent(&game_state.event))
    {
        switch (game_state.event.type)
        {
            case SDL_QUIT:
                app.is_running = false;
                break;
            case SDL_KEYDOWN:
                do_key_down(&game_state.event.key);
                break;
            case SDL_KEYUP:
                do_key_up(&game_state.event.key);
                break;
            case SDL_TEXTINPUT:
                STRNCPY(game_state.input_text, game_state.event.text.text, MAX_LINE_LENGTH);
                break;
            default:
                break;
        }
    }
}
