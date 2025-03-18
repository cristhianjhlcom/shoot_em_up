#ifndef TEXTS_H
#define TEXTS_H

#define GLYPH_HEIGHT 28
#define GLYPH_WIDTH  18

#include "common.h"
#include "graphics.h"

void init_fonts(void);
void draw_text(int x, int y, int r, int g, int b, const char *format, ...);

#endif // TEXTS_H