#include "common.h"
#include "core.h"
#include "game_state.h"
#include "input.h"
#include "stage.h"

// #define SDL_MAIN_HANDLED

int main(int argc, char *argv[])
{
    long then;
    float remainder;
    memset(&app, 0, sizeof(app_t));
    memset(&game_state, 0, sizeof(game_state_t));
    app.is_running = init();
    atexit(cleanup);
    init_stage();
    then = (long) SDL_GetTicks();
    remainder = 0;
    while (app.is_running)
    {
        prepare_scene();
        inputs();
        game_state.delegate.logic();
        game_state.delegate.draw();
        present_scene();
        cap_frame_rate(&then, &remainder);
    }
    return EXIT_SUCCESS;
}
