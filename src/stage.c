#include "stage.h"

static SDL_Texture *bullet_texture;

static void fire_bullet(void)
{
	entity_t *bullet;
	bullet = calloc(1, sizeof(entity_t));
	if (bullet == NULL)
	{
		SDL_Log("Player Memory Allocation Failed.\n");
		exit(1);
	}
	/*
	NOTE: Es lo mismo que calloc, limpia los valores basuras.
	memset(bullet, 0, sizeof(entity_t));
	*/
	game_state.stage.bullet_tail->next = bullet;
	game_state.stage.bullet_tail = bullet;
	/*
	*bullet = (entity_t) {
		.pos.x = (float) game_state.player.pos.x + (float) ((game_state.player.w + 50) / 2),
		.pos.y = (float) game_state.player.pos.y + (float) ((game_state.player.h - 10) / 2),
		.delta.x = PLAYER_BULLET_SPEED,
		.health = 1,
		.texture = bullet_texture,
	};
	bullet->delta.x += PLAYER_BULLET_SPEED;
	*/
	bullet->pos.x = (float) game_state.player.pos.x + (float) ((game_state.player.w + 50) / 2);
	bullet->pos.y = (float) game_state.player.pos.y + (float) ((game_state.player.h - 10) / 2);
	bullet->delta.x = PLAYER_BULLET_SPEED;
	bullet->health = 1;
	bullet->texture = bullet_texture;
	bullet->delta.x += PLAYER_BULLET_SPEED;
	SDL_QueryTexture(bullet->texture, NULL, NULL, &bullet->w, &bullet->h);
	game_state.player.reload = 8;
}

static void do_bullets(void)
{
	entity_t *b, *prev;
	prev = &game_state.stage.bullet_head;
	for (b = game_state.stage.bullet_head.next; b != NULL; b = b->next)
	{
		b->pos.x += b->delta.x;
		b->pos.y += b->delta.y;

		if (b->pos.x > SCREEN_WIDTH)
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

static void do_player(void)
{
	game_state.player.delta.x = 0;
	game_state.player.delta.y = 0;
	if (game_state.player.reload > 0)
	{
		game_state.player.reload--;
	}
	if (game_state.keyboard[SDL_SCANCODE_UP])
	{
		game_state.player.delta.y = -PLAYER_SPEED;
	}
	if (game_state.keyboard[SDL_SCANCODE_DOWN])
	{
		game_state.player.delta.y = PLAYER_SPEED;
	}
	if (game_state.keyboard[SDL_SCANCODE_LEFT])
	{
		game_state.player.delta.x = -PLAYER_SPEED;
	}
	if (game_state.keyboard[SDL_SCANCODE_RIGHT])
	{
		game_state.player.delta.x = PLAYER_SPEED;
	}
	if (game_state.keyboard[SDL_SCANCODE_LCTRL] && game_state.player.reload == 0)
	{
		fire_bullet();
	}
	game_state.player.pos.x += game_state.player.delta.x;
	game_state.player.pos.y += game_state.player.delta.y;
}

static void draw_player(void)
{
	blit(&game_state.player);
}

static void draw_bullets(void)
{
	entity_t *b;
	for (b = game_state.stage.bullet_head.next; b != NULL; b = b->next)
	{
		if (b->health > 0)
		{
			blit(b);
		}
	}
}

static void draw(void)
{
	draw_player();
	draw_bullets();
}

static void logic(void)
{
	do_player();
	do_bullets();
}

static void init_player(void)
{
	game_state.stage.fighter_tail->next = &game_state.player;
	game_state.stage.fighter_tail = &game_state.player;
	game_state.player.pos.x = 200;
    game_state.player.pos.y = 200;
    game_state.player.texture = load_texture("assets/graphics/player.png");
    game_state.player.speed = PLAYER_SPEED;
    if (SDL_QueryTexture(game_state.player.texture, NULL, NULL, &game_state.player.w, &game_state.player.h) < 0)
    {
        SDL_Log("[init_player]: %s\n", SDL_GetError());
        return;
    }
}

void init_stage(void)
{
	game_state.delegate.logic = logic;
	game_state.delegate.draw = draw;
	game_state.stage.fighter_tail = &game_state.stage.fighter_head;
	game_state.stage.bullet_tail = &game_state.stage.bullet_head;
	init_player();
    bullet_texture = load_texture("assets/graphics/bullet.png");
    // game_state.bullet.speed = PLAYER_BULLET_SPEED;
}