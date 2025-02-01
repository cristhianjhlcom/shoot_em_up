#include "common.h"

#include "setup.h"
#include "input.h"
#include "draw.h"
#include "stage.h"

app_t app;
stage_t stage;

static void cap_frame_rate(long *then, float *remainder);

int main(int argc, char *argv[]) {
    long then;
    float remainder;

    memset(&app, 0, sizeof(app_t));

    init();

    atexit(cleanup);

    init_stage();

    then = SDL_GetTicks();

    remainder = 0;

    while(1) {
        prepare_scene();

        do_input();

        app.delegate.logic();

        app.delegate.draw();

        present_scene();

        cap_frame_rate(&then, &remainder);
    }

    return EXIT_SUCCESS;
}

static void cap_frame_rate(long *then, float *remainder) {
    long wait;
    long frame_time;
    wait = 16 + *remainder;
    *remainder -= (int)*remainder;
    frame_time = SDL_GetTicks() - *then;
    wait -= frame_time;

    if (wait < 1) {
        wait = 1;
    }

    SDL_Delay(wait);

    *remainder += 0.667;
    *then = SDL_GetTicks();
}
