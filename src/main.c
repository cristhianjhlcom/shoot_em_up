#include "common.h"
#include "core.h"
#include "game_state.h"
#include "input.h"
#include "stage.h"

// #define SDL_MAIN_HANDLED

int main(int argc, char *argv[])
{
    memset(&app, 0, sizeof(app_t));
    memset(&game_state, 0, sizeof(game_state_t));

    app.is_running = init();

    atexit(cleanup);

    init_stage();

    while (app.is_running)
    {
        prepare_scene();
        inputs();
        game_state.delegate.logic();
        game_state.delegate.draw();
        present_scene();
        SDL_Delay(16);
    }

    return EXIT_SUCCESS;
}
