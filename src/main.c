// Standars includes.
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// SDL2 includes.
#include "SDL.h"
#include "SDL_events.h"
#include "SDL_timer.h"
#include "SDL_image.h"

// Application includes.
#include "constants.c"
#include "init.c"
#include "draw.c"
#include "input.c"
#include "entity.c"

int main(int argv, char *argc[])
{
    memset(&app, 0, sizeof(app_t));
    memset(&player, 0, sizeof(entity_t));

    app.is_running = init();

    player = (entity_t){
        .pos.x = 200,
        .pos.y = 200,
        .texture = load_texture("assets/graphics/player.png"),
    };

    atexit(cleanup);

    while (app.is_running)
    {
        prepare_scene();
        inputs();
        blit(player.texture, player.pos.x, player.pos.y);
        present_scene();
        SDL_Delay(16);
    }

    return EXIT_SUCCESS;
}
