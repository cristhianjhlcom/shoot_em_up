// Standars includes.
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// SDL2 includes.
#include "SDL.h"
#include "SDL_events.h"
#include "SDL_timer.h"

// Application includes.
#include "constants.c"
#include "init.c"
#include "draw.c"
#include "input.c"

int main(int argv, char *argc[])
{
    memset(&app, 0, sizeof(app_t));

    app.is_running = init();

    atexit(cleanup);

    while (app.is_running)
    {
        prepare_scene();
        inputs();
        present_scene();

        SDL_Delay(16);
    }

    return EXIT_SUCCESS;
}
