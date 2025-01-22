#include "../include/common.h"

#include "../include/stage.h"
#include "../include/draw.h"
#include "../include/structs.h"
#include "../include/util.h"

extern app_t app;
extern stage_t stage;

static void init_player(void);
static void init_starfield(void);
static void logic(void);
static void draw(void);
static void do_player(void);
static void do_enemies(void);
static void do_fighters(void);
static void do_bullets(void);
static void do_brackground();
static void do_starfield();
static void do_explosions();
static void do_debris();
static void add_explosion(int x, int y, int num);
static void add_debris(entity_t *e);
static void fire_bullet(void);
static void fire_alien_bullet(entity_t *e);
static void draw_bullet(void);
static void draw_fighters(void);
static void draw_background();
static void draw_starfield();
static void draw_debris();
static void draw_explosion();
static void spawn_enemies(void);
static void reset_stage(void);
static void clip_player(void);
static int bullet_hit_fighter(entity_t *b);

static entity_t *player;
static SDL_Texture *bullet_texture;
static SDL_Texture *alien_bullet_texture;
static SDL_Texture *enemy_texture;
static SDL_Texture *player_texture;
static SDL_Texture *background;
static SDL_Texture *explosion_texture;
static int enemy_spawn_timer;
static int stage_reset_timer;
static int background_x;
static star_t stars[MAX_STARS];

void init_stage(void) {
    app.delegate.logic = logic;
    app.delegate.draw = draw;
    memset(&stage, 0, sizeof(stage_t));

    // En otro lado se esta llamando este codigo.
    stage.fighter_tail = &stage.fighter_head;
    stage.bullet_tail = &stage.bullet_head;
    stage.explosion_tail = &stage.explosion_head;
    stage.debris_tail = &stage.debris_head;

    bullet_texture = load_texture("src/graphics/player_bullet.png");
    alien_bullet_texture = load_texture("src/graphics/enemy_bullet.png");
    player_texture = load_texture("src/graphics/player.png");
    enemy_texture = load_texture("src/graphics/enemy.png");
    background = load_texture("src/graphics/background.png");
    explosion_texture = load_texture("src/graphics/explosion.png");

    reset_stage();
}

static void reset_stage(void) {
    entity_t *e;
    explosion_t *ex;
    debris_t *d;

    // Clean fighter linked list.
    while (stage.fighter_head.next) {
        e = stage.fighter_head.next;
        stage.fighter_head.next = e->next;
        free(e);
    }

    // Clean bullet linked list.
    while (stage.bullet_head.next) {
        e = stage.bullet_head.next;
        stage.bullet_head.next = e->next;
        free(e);
    }

    // Clean explosion linked list.
    while (stage.explosion_head.next) {
        ex = stage.explosion_head.next;
        stage.explosion_head.next = ex->next;
        free(e);
    }

    // Clean debris linked list.
    while (stage.debris_head.next) {
        d = stage.debris_head.next;
        stage.debris_head.next = d->next;
        free(d);
    }

    // Set default stage values.
    memset(&stage, 0, sizeof(stage_t));

    // Set circular linked list for fighter and bullet.
    stage.fighter_tail = &stage.fighter_head;
    stage.bullet_tail = &stage.bullet_head;
    stage.explosion_tail = &stage.explosion_head;
    stage.debris_tail = &stage.debris_head;

    // Init the player instance.
    init_player();
    init_starfield();

    // Set enemy and stage timer to default values.
    enemy_spawn_timer = 0;
    stage_reset_timer = FPS * 3;
}

static void init_starfield(void) {
    int idx;

    for (idx = 0; idx < MAX_STARS; idx++) {
        stars[idx].x = rand() % SCREEN_WIDTH;
        stars[idx].y = rand() % SCREEN_HEIGHT;
        stars[idx].speed = 1 + rand() % 8;
    }
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
    do_brackground();
    do_starfield();
    do_player();
    do_enemies();
    do_fighters();
    do_bullets();
    spawn_enemies();
    clip_player();
    do_explosions();
    do_debris();

    // Call reset stage function is there not
    // player and stage reset timer is less then 0.
    if (player == NULL && --stage_reset_timer <= 0) {
        reset_stage();
    }
}

static void clip_player(void) {
    if (player != NULL) {
        if (player->x < 0) {
            player->x = 0;
        }

        if (player->y < 0) {
            player->y = 0;
        }

        if (player->x > SCREEN_WIDTH / 2) {
            player->x = SCREEN_WIDTH / 2;
        }

        if (player->y > SCREEN_HEIGHT - player->h) {
            player->y = SCREEN_HEIGHT - player->h;
        }
    }
}

static void do_player(void) {
    // The player now can be NULL.
    // So we have to check it before run the logic.
    if (player != NULL) {
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
}

static void do_brackground() {
    if (--background_x < -SCREEN_WIDTH) {
        background_x = 0;
    }
}

static void do_starfield() {
    int idx;

    for (idx = 0; idx < MAX_STARS; idx++) {
        stars[idx].x -= stars[idx].speed;

        if (stars[idx].x < 0) {
            stars[idx].x = SCREEN_WIDTH + stars[idx].x;
        }
    }
}

static void do_explosions() {
    explosion_t *e, *prev;
    prev = &stage.explosion_head;

    for (e = stage.explosion_head.next; e != NULL; e = e->next) {
        e->x += e->dx;
        e->y += e->dy;

        if (--e->a <= 0) {
            if (e == stage.explosion_tail) {
                stage.explosion_tail = prev;
            }

            prev->next = e->next;
            free(e);
            e = prev;
        }

        prev = e;
    }
}

static void do_debris() {
    debris_t *d, *prev;
    prev = &stage.debris_head;

    for (d = stage.debris_head.next; d != NULL; d = d->next) {
        d->x += d->dx;
        d->y += d->dy;

        d->dy += 0.5;

        if (--d->life <= 0) {
            if (d == stage.debris_tail) {
                stage.debris_tail = prev;
            }

            prev->next = d->next;
            free(d);
            d = prev;
        }

        prev = d;
    }
}

static void do_enemies(void) {
    // Create an entity instance.
    entity_t *e;

    // Loop through fighter linked list of stage.
    for (e = stage.fighter_head.next; e != NULL; e = e->next) {
        // Check if entity is different to the player.
        // Check if the player is not NULL.
        // Decrease entity reload until is less than 0.
        // Then call fire_alien_bullet().
        if (e != player && player != NULL && --e->reload <= 0) {
            printf("Firing alien bullets...\n");
            fire_alien_bullet(e);
        }
    }
}

static void fire_bullet(void) {
    for (int idx = 0; idx < 1; idx++) {
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

static void add_explosion(int x, int y, int num) {
    explosion_t *e;
    int idx;

    for (idx = 0; idx < num; idx++) {
        e = malloc(sizeof(explosion_t));
        memset(e, 0, sizeof(explosion_t));
        stage.explosion_tail->next = e;
        stage.explosion_tail = e;

        e->x = x + (rand() % 32) - (rand() % 32);
        e->y = y + (rand() % 32) - (rand() % 32);
        e->dx = (rand() % 10) - (rand() % 10);
        e->dy = (rand() % 10) - (rand() % 10);

        e->dx /= 10;
        e->dy /= 10;

        switch (rand() % 4) {
            case 0:
                e->r = 255;
                break;
            case 1:
                e->r = 255;
                e->g = 128;
                break;
            case 2:
                e->r = 255;
                e->g = 255;
                break;
            default:
                e->r = 255;
                e->g = 255;
                e->b = 255;
                break;
        }

        e->a = rand() % FPS * 3;
    }
}

static void add_debris(entity_t *e) {
    debris_t *d;
    int x, y, w, h;

    w = e->w / 2;
    h = e->h / 2;

    for (y = 0; y <= h; y += h) {
        for (x = 0; x <= w; x += w) {
            d = malloc(sizeof(debris_t));
            memset(d, 0, sizeof(debris_t));
            stage.debris_tail->next = d;
            stage.debris_tail = d;

            d->x = e->x + e->w / 2;
            d->y = e->y + e->h / 2;
            d->dx = (rand() % 5) - (rand() % 5);
            d->dy = -(5 + (rand() % 12));
            d->life = FPS * 2;
            d->texture = e->texture;

            d->rect.x = x;
            d->rect.y = y;
            d->rect.w = w;
            d->rect.h = h;
        }
    }
}

static void fire_alien_bullet(entity_t *e) {
    // Create entity bullet instance.
    entity_t *bullet;

    // Allocated in memory a memory space for entity_t.
    // for the bullet variable.
    bullet = malloc(sizeof(entity_t));
    if (bullet == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }

    // Set default values of bullet instances.
    memset(bullet, 0, sizeof(entity_t));

    // Point the next node of tail bullet list to the current bullet node.
    stage.bullet_tail->next = bullet;
    // Update the tail of bullet list to point to current bullet node.
    // This make the current node the last node in the list.
    stage.bullet_tail = bullet;

    // Set bullet position coords the same as the entity who fired.
    bullet->x = e->x;
    bullet->y = e->y;

    // Set bullet properties health, texture and side (enemy or player)
    bullet->health = 1;
    bullet->texture = alien_bullet_texture;
    bullet->side = SIDE_ALIEN;
    // Render the texture on screen.
    SDL_QueryTexture(bullet->texture, NULL, NULL, &bullet->w, &bullet->h);

    // Position the bullet in the centre of the attacker.
    bullet->x += (e->w / 2) - (bullet->w / 2);
    bullet->y += (e->h / 2) - (bullet->h / 2);

    calc_slope(player->x + (player->w / 2), player->y + (player->h / 2), e->x, e->y, &bullet->dx, &bullet->dy);

    bullet->dx *= ALIEN_BULLET_SPEED;
    bullet->dy *= ALIEN_BULLET_SPEED;

    e->reload = (rand() % FPS * 2);
}

static void do_bullets(void) {
    entity_t *b;
    entity_t *prev;
    prev = &stage.bullet_head;

    for (b = stage.bullet_head.next; b != NULL; b = b->next) {
        b->x += b->dx;
        b->y += b->dy;

        if (
            bullet_hit_fighter(b) ||
            b->x < -b->w ||
            b->y < -b->h ||
            b->x > SCREEN_WIDTH ||
            b->y > SCREEN_HEIGHT
        ) {
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
    draw_background();
    draw_starfield();
    draw_fighters();
    draw_bullet();
    draw_debris();
    draw_explosion();
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

static void draw_background() {
    SDL_Rect dest;
    int x;

    for (x = background_x; x < SCREEN_WIDTH; x += SCREEN_WIDTH) {
        dest.x = x;
        dest.y = 0;
        dest.w = SCREEN_WIDTH;
        dest.y = SCREEN_HEIGHT;

        SDL_RenderCopy(app.renderer, background, NULL, &dest);
    }
}

static void draw_starfield() {
    int i, c;

    for (i = 0; i < MAX_STARS; i++) {
        c = 32 * stars[i].speed;

        SDL_SetRenderDrawColor(app.renderer, c, c, c, 255);
        SDL_RenderDrawLine(app.renderer, stars[i].x, stars[i].y, stars[i].x + 3, stars[i].y);
    }
}

static void draw_debris() {
    debris_t *d;

    for (d = stage.debris_head.next; d != NULL; d = d->next) {
        blit_rect(d->texture, &d->rect, d->x, d->y);
    }
}

static void draw_explosion() {
    explosion_t *e;

    SDL_SetRenderDrawBlendMode(app.renderer, SDL_BLENDMODE_ADD);
    SDL_SetTextureBlendMode(explosion_texture, SDL_BLENDMODE_ADD);

    for (e = stage.explosion_head.next; e != NULL; e = e->next) {
        SDL_SetTextureColorMod(explosion_texture, e->r, e->g, e->b);
        SDL_SetTextureAlphaMod(explosion_texture, e->a);

        blit(explosion_texture, e->x, e->y);
    }

    SDL_SetRenderDrawBlendMode(app.renderer, SDL_BLENDMODE_NONE);
}

static void do_fighters(void) {
    entity_t *e;
    entity_t *prev;

    prev = &stage.fighter_head;

    for (e = stage.fighter_head.next; e != NULL; e = e->next) {
        e->x += e->dx;
        e->y += e->dy;

        /*if (e->y <= 0) {*/
        /*    e->y = 0;*/
        /*    e->dy = -e->dy;*/
        /*}*/
        /**/
        /*if (e->y + e->h >= SCREEN_HEIGHT) {*/
        /*    e->y = SCREEN_HEIGHT - e->h;*/
        /*    e->dy = -e->dy;*/
        /*}*/
        /**/
        /*if (e->y <= 0 || e->y + e->h >= SCREEN_HEIGHT) {*/
        /*    e->dy = (rand() % 5) - 2;*/
        /*}*/

        if (e != player && e->x < -e->w) {
            e->health = 0;
        }

        if (e->health == 0) {
            if (e == player) {
                player = NULL;
            }

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
        enemy->health = 1;

        enemy->reload = FPS * (1 + (rand() % 3));

        enemy_spawn_timer = 30 + (rand() % FPS);
    }
}

static int bullet_hit_fighter(entity_t *b) {
    entity_t *e;

    for (e = stage.fighter_head.next; e != NULL; e = e->next) {
        if (e->side != b->side && collision(b->x, b->y, b->w, b->h, e->x, e->y, e->w, e->h)) {
            b->health = 0;
            e->health = 0;

            // Check the life of enemy.
            /*if (e->health > 0) {*/
            /*    e->health -= 1;*/
            /*} else {*/
            /*    e->health = 0;*/
            /*    add_explosion(e->x, e->y, 32);*/
            /*    add_debris(e);*/
            /*}*/
            add_explosion(e->x, e->y, 32);
            add_debris(e);

            return 1;
        }
    }

    return 0;
}
