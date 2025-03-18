#ifndef UTIL_H
#define UTIL_H

#include "common.h"
#include "types.h"

int collision(entity_t *source, entity_t *target);
void calc_slope(entity_t *player, entity_t *enemy, entity_t *bullet);

#endif // UTIL_H