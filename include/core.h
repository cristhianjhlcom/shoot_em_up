#ifndef CORE_H
#define CORE_H

#include "common.h"
#include "game_state.h"

bool init(void);
void cleanup(void);
void cap_frame_rate(long *then, float *remainder);

#endif  // CORE_H
