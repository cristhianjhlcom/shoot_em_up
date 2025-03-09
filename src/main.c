#include "common.h"
#include "core.h"
#include "game_state.h"
#include "graphics.h"
#include "input.h"

int main(int argc, char *argv[])
{
    memset(&app, 0, sizeof(app_t));
    memset(&game_state, 0, sizeof(game_state_t));

    app.is_running = init();

    atexit(cleanup);

    game_state.player.pos.x = 200;
    game_state.player.pos.y = 200;
    game_state.player.texture = load_texture("assets/graphics/player.png");

    while (app.is_running)
    {
        prepare_scene();
        inputs();
        blit(game_state.player.texture, game_state.player.pos.x, game_state.player.pos.y);
        present_scene();
        SDL_Delay(16);
    }

    return EXIT_SUCCESS;
}
