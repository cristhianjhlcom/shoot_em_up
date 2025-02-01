#include "common.h"

#include "setup.h"
#include "input.h"
#include "draw.h"

entity_t player;
app_t app;

int main(int argc, char *argv[]) {
    memset(&app, 0, sizeof(app_t));
    memset(&player, 0, sizeof(entity_t));

    init();

    player.x = 100;
    player.y = 100;
    player.texture = load_texture("src/graphics/rocket.png");

    atexit(cleanup);

    while(1) {
        prepare_scene();
        do_input();

        if (app.up) {
            player.y -= 5;
        }

        if (app.down) {
            player.y += 5;
        }

        if (app.left) {
            player.x -= 5;
        }

        if (app.right) {
            player.x += 5;
        }

        if (player.x < 0) player.x = 0;
        if (player.y < 0) player.y = 0;
        if (player.x > (SCREEN_WIDTH - PLAYER_WIDTH)) player.x = SCREEN_WIDTH - PLAYER_WIDTH;
        if (player.y > (SCREEN_HEIGHT - PLAYER_HEIGHT)) player.y = SCREEN_HEIGHT - PLAYER_HEIGHT;

        blit(player.texture, player.x, player.y);
        present_scene();
        SDL_Delay(16);
    }

    return EXIT_SUCCESS;
}
