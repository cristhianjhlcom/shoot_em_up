#include "texts.h"

static SDL_Texture *font_texture;
static char draw_text_buffer[MAX_LINE_LENGTH];

void init_fonts(void)
{
	font_texture = load_texture("assets/fonts/font.png");
}

void draw_text(int x, int y, int r, int g, int b, int align, const char *format, ...)
{
	int idx, len, c;
	SDL_Rect rect;
	va_list args;
	memset(&draw_text_buffer, '\0', sizeof(draw_text_buffer));
	va_start(args, format);
	vsprintf(draw_text_buffer, format, args);
	va_end(args);
	len = (int) strlen(draw_text_buffer);
	switch (align)
	{
		case TEXT_RIGHT:
			x -= (len * GLYPH_WIDTH);
			break;
		case TEXT_CENTER:
			x -= (len * GLYPH_WIDTH / 2);
			break;
	}
	rect.w = GLYPH_WIDTH;
	rect.h = GLYPH_HEIGHT;
	rect.y = 0;
	SDL_SetTextureColorMod(font_texture, (Uint8) r, (Uint8) g, (Uint8) b);
	for (idx = 0; idx < len; idx++)
	{
		c = draw_text_buffer[idx];
		if (c >= ' ' && c <= 'Z')
		{
			rect.x  = (c - ' ') * GLYPH_WIDTH;
			blit_rect(font_texture, x, y, &rect);
			x += GLYPH_WIDTH;
		}
	}
}
