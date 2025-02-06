#include "common.h"

#define GLYPH_HEIGHT 28
#define GLYPH_WIDTH 18

static SDL_Texture *font_texture;
static char draw_text_buffer[MAX_LINE_LENGTH];

void init_fonts(void) {
    font_texture = load_texture("assets/graphics/font.png");
}

void draw_text(int x, int y, int r, int g, int b, char *format, ...) {
    int i, len, c;
    SDL_Rect rect;
    va_list args;

    memset(&draw_text_buffer, '\0', sizeof(draw_text_buffer));

    va_start(args, format);
    vsprintf(draw_text_buffer, format, args);
    va_end(args);

    len = strlen(draw_text_buffer);

    rect.w = GLYPH_WIDTH;
    rect.h = GLYPH_HEIGHT;
    rect.y = 0;

    SDL_SetTextureColorMod(font_texture, r, g, b);

    for (i = 0; i < len; i++) {
        c = draw_text_buffer[i];

        if (c >= ' ' && c <= 'Z') {
            rect.x = (c - ' ') * GLYPH_WIDTH;

            blit_rect(font_texture, &rect, x, y);

            x += GLYPH_WIDTH;
        }
    }
}
