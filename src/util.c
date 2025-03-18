#include "util.h"

int collision(entity_t *source, entity_t *target)
{
	return (
		MAX((int) source->pos.x, (int) target->pos.x) < MIN((int) source->pos.x + source->w, (int) target->pos.x + target->w)
		&& MAX((int) source->pos.y, (int) target->pos.y) < MIN((int) source->pos.y + source->h, (int) target->pos.y + target->h)
	);
}

void calc_slope(entity_t *player, entity_t *enemy, entity_t *bullet)
{
	int steps = MAX(
		abs((int) (player->pos.x - enemy->pos.x)),
		abs((int) (player->pos.y - enemy->pos.y))
	);
	if (steps == 0)
	{
		bullet->delta.x = 0;
		bullet->delta.y = 0;
		return;
	}
	bullet->delta.x = (float) (player->pos.x - enemy->pos.x);
	bullet->delta.x /= (float) steps;
	bullet->delta.y = (float) (player->pos.y - enemy->pos.y);
	bullet->delta.y /= (float) steps;
}