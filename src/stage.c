#include "stage.h"

static SDL_Texture *bullet_texture;
static SDL_Texture *enemy_texture;
static SDL_Texture *alien_bullet_texture;
static SDL_Texture *player_texture;
static SDL_Texture *explosion_texture;
static SDL_Texture *points_texture;
static int enemy_spawn_timer;
static int stage_reset_timer;
static int high_score;

static void logic(void);
static void draw(void);
static void reset_stage(void);
static void init_player(void);
static void clip_player(void);
static void add_explosions(float x, float y, int num);
static void add_debris(entity_t *e);
static void add_points_pods(int x, int y);
static void do_player(void);
static void do_fighters(void);
static void do_enemies(void);
static void do_bullets(void);
static void do_explosions(void);
static void do_debris(void);
static void do_points_pods(void);
static void draw_bullets(void);
static void draw_points_pods(void);
static void draw_fighters(void);
static void draw_debris(void);
static void draw_explosions(void);
static void draw_hub(void);

void init_stage(void)
{
    game_state.stage.fighter_tail = &game_state.stage.fighter_head;
    game_state.stage.bullet_tail = &game_state.stage.bullet_head;
    game_state.stage.points_tail = &game_state.stage.points_head;
    game_state.stage.explosion_tail = &game_state.stage.explosion_head;
    game_state.stage.debris_tail = &game_state.stage.debris_head;
    game_state.stage.texture_tail = &game_state.stage.texture_head;
    bullet_texture = load_texture("assets/graphics/bullet.png");
    enemy_texture = load_texture("assets/graphics/enemy.png");
    alien_bullet_texture = load_texture("assets/graphics/bullet.png");
    player_texture = load_texture("assets/graphics/player.png");
    explosion_texture = load_texture("assets/graphics/explosion.png");
    points_texture = load_texture("assets/graphics/points.png");
    reset_stage();
}

static void reset_stage(void)
{
    entity_t *e;
    explosion_t *ex;
    debris_t *d;
    while (game_state.stage.fighter_head.next)
    {
        e = game_state.stage.fighter_head.next;
        game_state.stage.fighter_head.next = e->next;
        free(e);
    }
    while (game_state.stage.bullet_head.next)
    {
        e = game_state.stage.bullet_head.next;
        game_state.stage.bullet_head.next = e->next;
        free(e);
    }
    while (game_state.stage.points_head.next)
    {
        e = game_state.stage.points_head.next;
        game_state.stage.points_head.next = e->next;
        free(e);
    }
    while (game_state.stage.explosion_head.next)
    {
        ex = game_state.stage.explosion_head.next;
        game_state.stage.explosion_head.next = ex->next;
        free(ex);
    }
    while (game_state.stage.debris_head.next)
    {
        d = game_state.stage.debris_head.next;
        game_state.stage.debris_head.next = d->next;
        free(d);
    }
    memset(&game_state, 0, sizeof(game_state_t));
    game_state.stage.fighter_tail = &game_state.stage.fighter_head;
    game_state.stage.bullet_tail = &game_state.stage.bullet_head;
    game_state.stage.explosion_tail = &game_state.stage.explosion_head;
    game_state.stage.debris_tail = &game_state.stage.debris_head;
    game_state.stage.points_tail = &game_state.stage.points_head;
    init_player();
    init_star_field();
    enemy_spawn_timer = 0;
    stage_reset_timer = FPS * 3;
    game_state.stage.score = 0;
    game_state.delegate.logic = logic;
    game_state.delegate.draw = draw;
}

static void init_player(void)
{
    game_state.player = malloc(sizeof(entity_t));
    if (game_state.player == NULL)
    {
        printf("Memory Allocation Failed.\n");
        exit(1);
    }
    memset(game_state.player, 0, sizeof(entity_t));
    game_state.stage.fighter_tail->next = game_state.player;
    game_state.stage.fighter_tail = game_state.player;

    game_state.player->health = 1;
    game_state.player->pos.x = 100;
    game_state.player->pos.y = SCREEN_HEIGHT / 2;
    game_state.player->texture = player_texture;
    game_state.player->speed = PLAYER_SPEED;
    if (SDL_QueryTexture(game_state.player->texture, NULL, NULL, &game_state.player->w, &game_state.player->h) < 0)
    {
        SDL_Log("init_player:138 %s\n", SDL_GetError());
        return;
    }
    game_state.player->side = SIDE_PLAYER;
}

static void fire_alien_bullet(entity_t *e)
{
    entity_t *bullet;
    bullet = malloc(sizeof(entity_t));
    if (bullet == NULL)
    {
        printf("Memory Allocation Failed.\n");
        exit(1);
    }
    memset(bullet, 0, sizeof(entity_t));
    game_state.stage.bullet_tail->next = bullet;
    game_state.stage.bullet_tail = bullet;
    bullet->pos.x = e->pos.x;
    bullet->pos.y = e->pos.y;
    bullet->health = 1;
    bullet->texture = alien_bullet_texture;
    bullet->side = SIDE_ALIEN;
    if (SDL_QueryTexture(bullet->texture, NULL, NULL, &bullet->w, &bullet->h) < 0)
    {
        SDL_Log("fire_alient_bullet:28 %s\n", SDL_GetError());
        return;
    }
    bullet->pos.x += (float)((e->w / 2) - (bullet->w / 2));
    bullet->pos.y += (float)((e->h / 2) - (bullet->h / 2));
    calc_slope(game_state.player, e, bullet);
    bullet->delta.x *= ALIEN_BULLET_SPEED;
    bullet->delta.y *= ALIEN_BULLET_SPEED;
    e->reload = (rand() % FPS * 2);
}

static void fire_bullet(void)
{
    entity_t *bullet;
    bullet = malloc(sizeof(entity_t));
    if (bullet == NULL)
    {
        SDL_Log("Player Memory Allocation Failed.\n");
        exit(1);
    }
    memset(bullet, 0, sizeof(entity_t));
    bullet->pos.x = (float)game_state.player->pos.x + (float)((game_state.player->w + 50) / 2);
    bullet->pos.y = (float)game_state.player->pos.y + (float)((game_state.player->h - 10) / 2);
    bullet->delta.x = PLAYER_BULLET_SPEED;
    bullet->health = 1;
    bullet->texture = bullet_texture;
    bullet->delta.x += PLAYER_BULLET_SPEED;
    bullet->side = SIDE_PLAYER;
    if (SDL_QueryTexture(bullet->texture, NULL, NULL, &bullet->w, &bullet->h) < 0)
    {
        SDL_Log("fire_bullet:36 %s\n", SDL_GetError());
        return;
    }
    game_state.stage.bullet_tail->next = bullet;
    game_state.stage.bullet_tail = bullet;
    game_state.player->reload = 20;
}

static int bullet_hit_fighter(entity_t *b)
{
    entity_t *e;
    for (e = game_state.stage.fighter_head.next; e != NULL; e = e->next)
    {
        if (e->side != b->side && collision(b, e))
        {
            if (e == game_state.player)
            {
                play_sound(SND_PLAYER_DIE, CH_PLAYER);
            }
            else
            {
                add_points_pods((int)e->pos.x + e->w / 2, (int)e->pos.y + e->h / 2);
                /*
                play_sound(SND_ALIEN_DIE, CH_ANY);
                game_state.stage.score++;
                high_score = MAX(game_state.stage.score, high_score);
                */
            }
            b->health = 0;
            e->health = 0;
            add_explosions(e->pos.x, e->pos.y, 32);
            add_debris(e);
            return 1;
        }
    }
    return 0;
}

static void clip_player(void)
{
    if (game_state.player != NULL)
    {
        if (game_state.player->pos.x < 0)
        {
            game_state.player->pos.x = 0;
        }
        if (game_state.player->pos.y < 0)
        {
            game_state.player->pos.y = 0;
        }
        if (game_state.player->pos.x > SCREEN_WIDTH / 2)
        {
            game_state.player->pos.x = SCREEN_WIDTH / 2;
        }
        if (game_state.player->pos.y > SCREEN_HEIGHT - game_state.player->h)
        {
            game_state.player->pos.y = (float)(SCREEN_HEIGHT - game_state.player->h);
        }
    }
}

static void do_bullets(void)
{
    entity_t *b, *prev;
    prev = &game_state.stage.bullet_head;
    for (b = game_state.stage.bullet_head.next; b != NULL; b = b->next)
    {
        b->pos.x += b->delta.x;
        b->pos.y += b->delta.y;

        if (bullet_hit_fighter(b) || b->pos.x > SCREEN_WIDTH)
        {
            if (b == game_state.stage.bullet_tail)
            {
                game_state.stage.bullet_tail = prev;
            }
            prev->next = b->next;
            free(b);
            b = prev;
        }
        prev = b;
    }
}

static void do_explosions(void)
{
    explosion_t *e, *prev;
    prev = &game_state.stage.explosion_head;
    for (e = game_state.stage.explosion_head.next; e != NULL; e = e->next)
    {
        e->pos.x += e->delta.x;
        e->pos.y += e->delta.y;
        if (--e->color.a <= 0)
        {
            if (e == game_state.stage.explosion_tail)
            {
                game_state.stage.explosion_tail = prev;
            }
            prev->next = e->next;
            free(e);
            e = prev;
        }
        prev = e;
    }
}

static void do_player(void)
{
    if (game_state.player != NULL)
    {
        game_state.player->delta.x = 0;
        game_state.player->delta.y = 0;
        if (game_state.player->reload > 0)
        {
            game_state.player->reload--;
        }
        if (game_state.keyboard[SDL_SCANCODE_UP])
        {
            game_state.player->delta.y = -PLAYER_SPEED;
        }
        if (game_state.keyboard[SDL_SCANCODE_DOWN])
        {
            game_state.player->delta.y = PLAYER_SPEED;
        }
        if (game_state.keyboard[SDL_SCANCODE_LEFT])
        {
            game_state.player->delta.x = -PLAYER_SPEED;
        }
        if (game_state.keyboard[SDL_SCANCODE_RIGHT])
        {
            game_state.player->delta.x = PLAYER_SPEED;
        }
        if (game_state.keyboard[SDL_SCANCODE_LCTRL] && game_state.player->reload == 0)
        {
            fire_bullet();
            play_sound(SND_PLAYER_FIRE, CH_PLAYER);
        }
    }
}

static void do_fighters(void)
{
    entity_t *e, *prev;
    prev = &game_state.stage.fighter_head;
    for (e = game_state.stage.fighter_head.next; e != NULL; e = e->next)
    {
        e->pos.x += e->delta.x;
        e->pos.y += e->delta.y;
        if (e != game_state.player && e->pos.x < -e->w)
        {
            e->health = 0;
        }
        if (e->health == 0)
        {
            if (e == game_state.player)
            {
                game_state.player = NULL;
            }
            if (e == game_state.stage.fighter_tail)
            {
                game_state.stage.fighter_tail = prev;
            }
            prev->next = e->next;
            free(e);
            e = prev;
        }
        prev = e;
    }
}

static void do_points_pods(void)
{
    entity_t *e, *prev;
    prev = &game_state.stage.points_head;
    for (e = game_state.stage.points_head.next; e != NULL; e = e->next)
    {
        // Pod bounce on x axis.
        if (e->pos.x < 0)
        {
            e->pos.x = 0;
            e->delta.x = -e->delta.x;
        }
        if ((int)e->pos.x + e->w > SCREEN_WIDTH)
        {
            e->pos.x = (float)(SCREEN_WIDTH - e->w);
            e->delta.x = -e->delta.x;
        }
        // Pod bounce on y axis.
        if (e->pos.y < 0)
        {
            e->pos.y = 0;
            e->delta.y = -e->delta.y;
        }
        if ((int)e->pos.y + e->h > SCREEN_HEIGHT)
        {
            e->pos.y = (float)(SCREEN_HEIGHT - e->h);
            e->delta.y = -e->delta.y;
        }
        e->pos.x += e->delta.x;
        e->pos.y += e->delta.y;
        if (game_state.player != NULL && collision(e, game_state.player))
        {
            e->health = 0;
            game_state.stage.score++;
            high_score = MAX(game_state.stage.score, high_score);
            play_sound(SND_POINTS, CH_POINTS);
        }
        if (--e->health <= 0)
        {
            if (e == game_state.stage.points_tail)
            {
                game_state.stage.points_tail = prev;
            }
            prev->next = e->next;
            free(e);
            e = prev;
        }
        prev = e;
    }
}

static void do_debris(void)
{
    debris_t *d, *prev;
    prev = &game_state.stage.debris_head;
    for (d = game_state.stage.debris_head.next; d != NULL; d = d->next)
    {
        d->pos.x += d->delta.x;
        d->pos.y += d->delta.y;
        d->delta.y += (float)0.5;
        if (--d->life <= 0)
        {
            if (d == game_state.stage.debris_tail)
            {
                game_state.stage.debris_tail = prev;
            }
            prev->next = d->next;
            free(d);
            d = prev;
        }
        prev = d;
    }
}

static void do_enemies(void)
{
    entity_t *e;
    for (e = game_state.stage.fighter_head.next; e != NULL; e = e->next)
    {
        if (e != game_state.player && game_state.player != NULL && --e->reload <= 0)
        {
            fire_alien_bullet(e);
            play_sound(SND_ALIEN_FIRE, CH_ALIEN_FIRE);
        }
    }
}

static void add_explosions(float x, float y, int num)
{
    explosion_t *e;
    for (int idx = 0; idx < num; idx++)
    {
        e = malloc(sizeof(explosion_t));
        if (e == NULL)
        {
            printf("Memory Allocation Failed.\n");
            exit(1);
        }
        memset(e, 0, sizeof(explosion_t));
        game_state.stage.explosion_tail->next = e;
        game_state.stage.explosion_tail = e;
        e->pos.x = x + (float)(rand() % 32) - (float)(rand() % 32);
        e->pos.y = y + (float)(rand() % 32) - (float)(rand() % 32);
        e->delta.x = (float)(rand() % 10) - (float)(rand() % 10);
        e->delta.y = (float)(rand() % 10) - (float)(rand() % 10);
        e->delta.x /= 10;
        e->delta.y /= 10;
        switch (rand() % 4)
        {
            case 0:
                e->color.r = 255;
                break;
            case 1:
                e->color.r = 255;
                e->color.g = 128;
                break;
            case 2:
                e->color.r = 255;
                e->color.g = 255;
                break;
            default:
                e->color.r = 255;
                e->color.g = 255;
                e->color.b = 255;
                break;
        }
        e->color.a = rand() % FPS * 3;
    }
}

static void add_points_pods(int x, int y)
{
    entity_t *e;
    e = malloc(sizeof(entity_t));
    if (e == NULL)
    {
        printf("Memory Allocation Failed.\n");
        exit(1);
    }
    memset(e, 0, sizeof(entity_t));
    game_state.stage.points_tail->next = e;
    game_state.stage.points_tail = e;
    e->pos.x = (float)x;
    e->pos.y = (float)y;
    e->delta.x = (float)-(rand() % 5);
    e->delta.y = (float)(rand() % 5) - (float)(rand() % 5);
    e->health = FPS * 10;
    e->texture = points_texture;
    if (SDL_QueryTexture(e->texture, NULL, NULL, &e->w, &e->h) < 0)
    {
        printf("Could react texture size. %s\n", SDL_GetError());
        exit(1);
    }
    e->pos.x -= (float)e->w / 2;
    e->pos.y -= (float)e->h / 2;
}

static void add_debris(entity_t *e)
{
    debris_t *d;
    int x, y, w, h;
    w = e->w / 2;
    h = e->h / 2;
    for (y = 0; y <= h; y += h)
    {
        for (x = 0; x <= w; x += w)
        {
            d = malloc(sizeof(debris_t));
            if (d == NULL)
            {
                printf("Memory Allocation Failed.\n");
                exit(1);
            }
            memset(d, 0, sizeof(debris_t));
            game_state.stage.debris_tail->next = d;
            game_state.stage.debris_tail = d;
            d->pos.x = (float)e->pos.x + (float)e->w / 2;
            d->pos.y = (float)e->pos.y + (float)e->h / 2;
            d->delta.x = (float)(rand() % 5) - (float)(rand() % 5);
            d->delta.y = (float)-(5 + (rand() % 12));
            d->life = FPS * 2;
            d->texture = e->texture;
            d->rect.x = x;
            d->rect.y = y;
            d->rect.w = w;
            d->rect.h = h;
        }
    }
}

/*
static void draw_player(void)
{
    blit(game_state.player);
}
*/

static void draw_debris(void)
{
    debris_t *d;
    for (d = game_state.stage.debris_head.next; d != NULL; d = d->next)
    {
        blit_rect(d->texture, (int)d->pos.x, (int)d->pos.y, &d->rect);
    }
}

static void draw_points_pods(void)
{
    entity_t *e;
    for (e = game_state.stage.points_head.next; e != NULL; e = e->next)
    {
        blit(e->texture, (int)e->pos.x, (int)e->pos.y);
    }
}

static void draw_explosions(void)
{
    explosion_t *e;
    SDL_SetRenderDrawBlendMode(app.renderer, SDL_BLENDMODE_ADD);
    SDL_SetTextureBlendMode(explosion_texture, SDL_BLENDMODE_ADD);
    for (e = game_state.stage.explosion_head.next; e != NULL; e = e->next)
    {
        SDL_SetTextureColorMod(explosion_texture, (Uint8)e->color.r, (Uint8)e->color.g, (Uint8)e->color.b);
        SDL_SetTextureAlphaMod(explosion_texture, (Uint8)e->color.a);
        blit(explosion_texture, (int)e->pos.x, (int)e->pos.y);
    }
}

static void draw_bullets(void)
{
    entity_t *b;
    for (b = game_state.stage.bullet_head.next; b != NULL; b = b->next)
    {
        if (b->health > 0)
        {
            blit(b->texture, (int)b->pos.x, (int)b->pos.y);
        }
    }
}

static void draw_fighters(void)
{
    entity_t *e;
    for (e = game_state.stage.fighter_head.next; e != NULL; e = e->next)
    {
        blit(e->texture, (int)e->pos.x, (int)e->pos.y);
    }
}

static void draw_hub(void)
{
    draw_text(10, 10, 255, 255, 255, TEXT_LEFT, "SCORE: %03d", game_state.stage.score);
    if (game_state.stage.score > 0 && game_state.stage.score == high_score)
    {
        draw_text(SCREEN_WIDTH - 16 * 18, 10, 0, 255, 0, TEXT_RIGHT, "HIGH SCORE: %03d", high_score);
    }
    else
    {
        draw_text(SCREEN_WIDTH - 16 * 18, 10, 255, 255, 0, TEXT_RIGHT, "HIGH SCORE: %03d", high_score);
    }
}

static void spawn_enemies(void)
{
    entity_t *enemy;
    if (--enemy_spawn_timer <= 0)
    {
        enemy = malloc(sizeof(entity_t));
        if (enemy == NULL)
        {
            printf("Memory Allocation Failed.\n");
            exit(1);
        }
        memset(enemy, 0, sizeof(entity_t));
        enemy->pos.x = SCREEN_WIDTH;
        enemy->pos.y = (float)(rand() % SCREEN_HEIGHT);
        enemy->texture = enemy_texture;
        if (SDL_QueryTexture(enemy->texture, NULL, NULL, &enemy->w, &enemy->h) < 0)
        {
            printf("Cannont assign enemy w and h to entity\n.");
            exit(1);
        }
        enemy->delta.x = (float)-(2 + (rand() % 4));
        enemy->side = SIDE_ALIEN;
        enemy->health = 1;
        enemy_spawn_timer = 30 + (rand() & 60);
        game_state.stage.fighter_tail->next = enemy;
        game_state.stage.fighter_tail = enemy;
    }
}

static void logic(void)
{
    do_background();
    do_star_field();
    do_player();
    do_fighters();
    do_enemies();
    do_bullets();
    do_explosions();
    do_debris();
    do_points_pods();
    spawn_enemies();
    clip_player();
    if (game_state.player == NULL && --stage_reset_timer <= 0)
    {
        add_highscore(game_state.stage.score);
        init_highscores();
    }
}

static void draw(void)
{
    // draw_player();
    draw_background();
    // draw_star_field();
    draw_points_pods();
    draw_fighters();
    draw_debris();
    draw_explosions();
    draw_bullets();
    draw_hub();
}
