#include "common.h"
#include "core.h"
#include "game_state.h"
#include "graphics.h"
#include "input.h"

// #define SDL_MAIN_HANDLED

int main(int argc, char *argv[])
{
    memset(&app, 0, sizeof(app_t));
    memset(&game_state, 0, sizeof(game_state_t));

    app.is_running = init();

    atexit(cleanup);

    game_state.player.pos.x = 200;
    game_state.player.pos.y = 200;
    game_state.player.texture = load_texture("assets/graphics/player.png");
    game_state.player.speed = 6;

    game_state.bullet.texture = load_texture("assets/graphics/bullet.png");
    game_state.bullet.speed = 26;

    while (app.is_running)
    {
        prepare_scene();
        inputs();
        game_state.player.pos.x += game_state.player.delta.x;
        game_state.player.pos.y += game_state.player.delta.y;
        if (game_state.up && game_state.player.pos.y > 0)
        {
            game_state.player.pos.y -= game_state.player.speed;
        }
        if (game_state.down && game_state.player.pos.y < (SCREEN_HEIGHT - game_state.player.h))
        {
            game_state.player.pos.y += game_state.player.speed;
        }
        if (game_state.left && game_state.player.pos.x > 0)
        {
            game_state.player.pos.x -= game_state.player.speed;
        }
        if (game_state.right && game_state.player.pos.x < (SCREEN_WIDTH - game_state.player.w))
        {
            game_state.player.pos.x += game_state.player.speed;
        }
        if (game_state.player.fire && game_state.bullet.health == 0)
        {
            game_state.bullet.pos.x = game_state.player.pos.x + ((game_state.player.w + 50) / 2);
            game_state.bullet.pos.y = game_state.player.pos.y + ((game_state.player.h - 10) / 2);
            game_state.bullet.delta.x = game_state.bullet.speed;
            game_state.bullet.delta.y = 0;
            game_state.bullet.health = 1;
        }
        game_state.bullet.pos.x += game_state.bullet.delta.x;
        game_state.bullet.pos.y += game_state.bullet.delta.y;
        if (game_state.bullet.pos.x > SCREEN_WIDTH)
        {
            game_state.bullet.health = 0;
        }
        blit(&game_state.player);
        if (game_state.bullet.health > 0)
        {
            blit(&game_state.bullet);
        }
        present_scene();
        SDL_Delay(16);
    }

    return EXIT_SUCCESS;
}
