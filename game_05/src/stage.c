#include "common.h"

#include "stage.h"
#include "draw.h"

extern app_t app;
extern stage_t stage;

static void init_player(void);
static void logic(void);
static void draw(void);
static void do_player(void);
static void do_bullets(void);
static void fire_bullet(void);
static void draw_player(void);
static void draw_bullet(void);

static entity_t *player;
static SDL_Texture *bullet_texture;

void init_stage(void) {
    app.delegate.logic = logic;
    app.delegate.draw = draw;

    memset(&stage, 0, sizeof(stage_t));

    stage.fighter_tail = &stage.fighter_head;
    stage.bullet_tail = &stage.bullet_head;

    init_player();

    bullet_texture = load_texture("src/graphics/fire_bullets.png");
}

static void init_player(void)  {
    player = malloc(sizeof(entity_t));
    if (player == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }
    memset(player, 0, sizeof(entity_t));
    stage.fighter_tail->next = player;
    stage.fighter_tail = player;
    player->x = 100;
    player->y = 100;
    player->texture = load_texture("src/graphics/rocket.png");
    SDL_QueryTexture(player->texture, NULL, NULL, &player->w, &player->h);
}

static void logic(void) {
    do_player();
    do_bullets();
}

static void do_player(void) {
    player->dx = player->dy = 0;

    if (player->reload > 0) {
        player->reload--;
    }

    if (app.keyboard[SDL_SCANCODE_UP]) {
        player->dy = -PLAYER_SPEED;
    }

    if (app.keyboard[SDL_SCANCODE_DOWN]) {
        player->dy = PLAYER_SPEED;
    }

    if (app.keyboard[SDL_SCANCODE_LEFT]) {
        player->dx = -PLAYER_SPEED;
    }

    if (app.keyboard[SDL_SCANCODE_RIGHT]) {
        player->dx = PLAYER_SPEED;
    }

    if (app.keyboard[SDL_SCANCODE_LCTRL] && player->reload == 0) {
        fire_bullet();
    }

    player->x += player->dx;
    player->y += player->dy;
}

static void fire_bullet(void) {
    entity_t *bullet;
    bullet = malloc(sizeof(entity_t));
    if (bullet == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }
    memset(bullet, 0, sizeof(entity_t));
    stage.bullet_tail->next = bullet;
    stage.bullet_tail = bullet;
    bullet->x = player->x;
    bullet->y = player->y;
    bullet->dx = PLAYER_BULLET_SPEED;
    bullet->health = 1;
    bullet->texture = bullet_texture;
    SDL_QueryTexture(bullet->texture, NULL, NULL, &bullet->w, &bullet->h);
    bullet->y += (player->h / 2) - (bullet->h / 2);
    player->reload = 8;
}

static void do_bullets(void) {
    entity_t *b;
    entity_t *prev;
    prev = &stage.bullet_head;

    for (b = stage.bullet_head.next; b != NULL; b = b->next) {
        b->x += b->dx;
        b->y += b->dy;

        if (b->x > SCREEN_WIDTH) {
            if (b == stage.bullet_tail) {
                stage.bullet_tail = prev;
            }

            prev->next = b->next;
            free(b);
            b = prev;
        }

        prev = b;
    }
}


static void draw(void) {
    draw_player();
    draw_bullet();
}


static void draw_player(void) {
    blit(player->texture, player->x, player->y);
}

static void draw_bullet(void) {
    entity_t *b;

    for (b = stage.bullet_head.next; b != NULL; b = b->next) {
        blit(b->texture, b->x, b->y);
    }
}
