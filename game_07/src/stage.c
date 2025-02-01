#include "common.h"

#include "stage.h"
#include "draw.h"
#include "structs.h"
#include "util.h"

extern app_t app;
extern stage_t stage;

static void init_player(void);
static void logic(void);
static void draw(void);
static void do_player(void);
static void do_fighters(void);
static void do_bullets(void);
static void fire_bullet(void);
static void draw_player(void);
static void draw_bullet(void);
static void draw_fighters(void);
static void spawn_enemies(void);
static int bullet_hit_fighter(entity_t *b);

static entity_t *player;
static SDL_Texture *bullet_texture;
static SDL_Texture *enemy_texture;
static int enemy_spawn_timer;

void init_stage(void) {
    app.delegate.logic = logic;
    app.delegate.draw = draw;

    memset(&stage, 0, sizeof(stage_t));

    stage.fighter_tail = &stage.fighter_head;
    stage.bullet_tail = &stage.bullet_head;

    init_player();

    bullet_texture = load_texture("src/graphics/fire_bullet.png");
    enemy_texture = load_texture("src/graphics/enemy.png");

    enemy_spawn_timer = 0;
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
    player->texture = load_texture("src/graphics/player.png");
    SDL_QueryTexture(player->texture, NULL, NULL, &player->w, &player->h);
    player->health = 1;
	player->side = SIDE_PLAYER;
}

static void logic(void) {
    do_player();
    do_fighters();
    do_bullets();
    spawn_enemies();
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
}

static void fire_bullet(void) {
    for (int idx = 0; idx < 2; idx++) {
        entity_t *bullet;
        bullet = malloc(sizeof(entity_t));
        if (bullet == NULL) {
            printf("Memory allocation failed.\n");
            exit(1);
        }
        memset(bullet, 0, sizeof(entity_t));
        stage.bullet_tail->next = bullet;
        stage.bullet_tail = bullet;
        bullet->x = player->x + 50;
        bullet->y = player->y + (idx % 2 == 0 ? -5 : 5);
        bullet->dx = PLAYER_BULLET_SPEED;
        // Controls the spread of each bullets.
        //bullet->dy = (rand() % 5) - 2;
        bullet->dy = ((float)(rand() % 100) / 50.0f) - 1.0f;
        bullet->health = 1;
        bullet->texture = bullet_texture;
        bullet->side = SIDE_PLAYER;
        SDL_QueryTexture(bullet->texture, NULL, NULL, &bullet->w, &bullet->h);
        bullet->y += (player->h / 2) - (bullet->h / 2);
        // Controls how fast the player can fire.
        player->reload = 16;
    }
}

static void do_bullets(void) {
    entity_t *b;
    entity_t *prev;
    prev = &stage.bullet_head;

    for (b = stage.bullet_head.next; b != NULL; b = b->next) {
        b->x += b->dx;
        b->y += b->dy;

        if (bullet_hit_fighter(b) || b->x > SCREEN_WIDTH) {
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
    draw_fighters();
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

static void draw_fighters(void) {
    entity_t *e;

    for (e = stage.fighter_head.next; e != NULL; e = e->next) {
        blit(e->texture, e->x, e->y);
    }
}

static void do_fighters(void) {
    entity_t *e;
    entity_t *prev;

    prev = &stage.fighter_head;

    for (e = stage.fighter_head.next; e != NULL; e = e->next) {
        e->x += e->dx;
        e->y += e->dy;

        if (e->y <= 0) {
            e->y = 0;
            e->dy = -e->dy;
        }

        if (e->y + e->h >= SCREEN_HEIGHT) {
            e->y = SCREEN_HEIGHT - e->h;
            e->dy = -e->dy;
        }

        if (e->y <= 0 || e->y + e->h >= SCREEN_HEIGHT) {
            e->dy = (rand() % 5) - 2;
        }

        if (e != player && e->x < -e->w || e->health == 0) {
            if (e == stage.fighter_tail) {
                stage.fighter_tail = prev;
            }

            prev->next = e->next;
            free(e);
            e = prev;
        }

        prev = e;
    }
}

static void spawn_enemies(void) {
    entity_t *enemy;

    if (--enemy_spawn_timer <= 0) {
        enemy = malloc(sizeof(entity_t));
        memset(enemy, 0, sizeof(entity_t));
        stage.fighter_tail->next = enemy;
        stage.fighter_tail = enemy;

        enemy->x = SCREEN_WIDTH;
        enemy->y = rand() % SCREEN_HEIGHT;
        enemy->texture = enemy_texture;
        SDL_QueryTexture(enemy->texture, NULL, NULL, &enemy->w, &enemy->h);

        enemy->dy = (rand() % 5) - 2;
        enemy->dx = -(2 + (rand() % 4));
        enemy->side = SIDE_ALIEN;
        enemy->health = 3;

        enemy_spawn_timer = 10 + (rand() % 30);
    }
}

static int bullet_hit_fighter(entity_t *b) {
    entity_t *e;

    for (e = stage.fighter_head.next; e != NULL; e = e->next) {
        if (e->side != b->side && collision(b->x, b->y, b->w, b->h, e->x, e->y, e->w, e->h)) {
            b->health = 0;

            if (e->health > 0) {
                e->health -= 1;
            } else {
                e->health = 0;
            }

            return 1;
        }
    }

    return 0;
}
