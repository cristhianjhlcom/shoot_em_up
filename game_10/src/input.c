#include "../include/common.h"

void do_key_down(SDL_KeyboardEvent *event);
void do_key_up(SDL_KeyboardEvent *event);

extern app_t app;

void do_input(void) {
    SDL_Event event;

    while(SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                SDL_Quit();
                exit(0);
                break;
            case SDL_KEYDOWN:
                do_key_down(&event.key);
                break;
            case SDL_KEYUP:
                do_key_up(&event.key);
            default:
                break;
        }
    }
}

void do_key_down(SDL_KeyboardEvent *event) {
    if (event->repeat == 0 && event->keysym.scancode < MAX_KEYBOARD_KEYS) {
        app.keyboard[event->keysym.scancode] = 1;
    }
}

void do_key_up(SDL_KeyboardEvent *event) {
    if (event->repeat == 0 && event->keysym.scancode < MAX_KEYBOARD_KEYS) {
        app.keyboard[event->keysym.scancode] = 0;
    }
}
