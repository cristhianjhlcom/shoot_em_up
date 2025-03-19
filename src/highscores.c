#include "highscores.h"

static highscores_t highscores;
static highscore_t *new_highscore;
static int cursor_blink;

static int highscore_comparator(const void *a, const void *b);
static void logic(void);
static void draw(void);
static void draw_highscores(void);
static void draw_name_input(void);
static void do_name_input(void);

void init_highscore_table(void)
{
    memset(&highscores, 0, sizeof(highscores_t));
    for (int idx = 0; idx < NUM_HIGHSCORE; idx++)
    {
        highscores.highscore[idx].score = NUM_HIGHSCORE - idx;
        STRNCPY(highscores.highscore[idx].name, "ANONYMOUS", MAX_SCORE_NAME_LENGTH);
    }
    new_highscore = NULL;
    cursor_blink = 0;
}

void init_highscores(void)
{
    game_state.delegate.logic = logic;
    game_state.delegate.draw = draw;
    memset(game_state.keyboard, 0, sizeof(int) * MAX_KEYBOARD_KEYS);
}

void add_highscore(int score)
{
    highscore_t new_highscores[NUM_HIGHSCORE + 1];
    memset(new_highscores, 0, sizeof(highscore_t) * (NUM_HIGHSCORE + 1));
    for (int idx = 0; idx < NUM_HIGHSCORE; idx++)
    {
        new_highscores[idx] = highscores.highscore[idx];
        new_highscores[idx].recent = 0;
    }
    new_highscores[NUM_HIGHSCORE].score = score;
    new_highscores[NUM_HIGHSCORE].recent = 1;
    qsort(new_highscores, NUM_HIGHSCORE + 1, sizeof(highscore_t), highscore_comparator);
    new_highscore = NULL;
    for (int idx = 0; idx < NUM_HIGHSCORE; idx++)
    {
        highscores.highscore[idx] = new_highscores[idx];
        if (new_highscores[idx].recent)
        {
            new_highscore = &highscores.highscore[idx];
        }
    }
}

static int highscore_comparator(const void *a, const void *b)
{
    highscore_t *h1 = ((highscore_t*)a);
    highscore_t *h2 = ((highscore_t*)b);

    return h2->score - h1->score;
}

static void draw_highscores(void)
{
    int i, y, r, g, b;
    y = 150;
    const char *highscore_text = "HIGHSCORES";
    draw_text(425, 70, 255, 255, 255, TEXT_CENTER, highscore_text);
    for (i = 0 ; i < NUM_HIGHSCORE ; i++)
    {
        r = 255;
        g = 255;
        b = 255;
        if (highscores.highscore[i].recent)
        {
            b = 0;
            // draw_text(425, y, 255, 255, 0, "#%d ............. %03d", (i + 1), highscores.highscore[i].score);
        }
        draw_text(
            SCREEN_WIDTH / 2,
            y,
            r,
            g,
            b,
            TEXT_CENTER,
            "#%d . %-15s ...... %03d",
            (i + 1),
            highscores.highscore[i].name,
            highscores.highscore[i].score
        );
        /*
        else
        {
            draw_text(425, y, 255, 255, 255, "#%d ............. %03d", (i + 1), highscores.highscore[i].score);
        }
        */
        y += 50;
    }
    draw_text(425, 600, 255, 255, 255, TEXT_CENTER, "PRESS FIRE TO PLAY!");
}

static void draw_name_input(void)
{
    SDL_Rect r;

    draw_text(SCREEN_WIDTH / 2, 70, 255, 255, 255, TEXT_CENTER, "CONGRATULATIONS, YOU'VE GAINED A HIGHSCORE!");
    draw_text(SCREEN_WIDTH / 2, 120, 255, 255, 255, TEXT_CENTER, "ENTER YOUR NAME BELOW:");
    draw_text(SCREEN_WIDTH / 2, 250, 128, 255, 128, TEXT_CENTER, new_highscore->name);
    if (cursor_blink < FPS / 2)
    {
        r.x = (int) ((SCREEN_WIDTH / 2) + (strlen(new_highscore->name) * GLYPH_WIDTH) / 2) + 5;
        r.y = 250;
        r.w = GLYPH_WIDTH;
        r.h = GLYPH_HEIGHT;

        SDL_SetRenderDrawColor(app.renderer, 0, 255, 0, 255);
        SDL_RenderFillRect(app.renderer, &r);
    }
    draw_text(SCREEN_WIDTH / 2, 625, 255, 255, 255, TEXT_CENTER, "PRESS RETURN WHEN FINISHED");
}

static void do_name_input(void)
{
    int n;
    char c;
    n = (int) strlen(new_highscore->name);
    for (int idx = 0; idx < (int) strlen(game_state.input_text); idx++)
    {
        c = (char) toupper(game_state.input_text[idx]);
        if (n < MAX_SCORE_NAME_LENGTH - 1 && c >= ' ' && c <= 'Z')
        {
            new_highscore->name[n++] = c;
        }
    }
    if (n > 0 && game_state.keyboard[SDL_SCANCODE_BACKSPACE])
    {
        new_highscore->name[--n] = '\0';
        game_state.keyboard[SDL_SCANCODE_BACKSPACE] = 0;
    }
    if (game_state.keyboard[SDL_SCANCODE_RETURN])
    {
        if (strlen(new_highscore->name) == 0)
        {
            STRNCPY(new_highscore->name, "ANONYMOUS", MAX_SCORE_NAME_LENGTH);
        }
        new_highscore = NULL;
    }
}

static void logic(void)
{
    do_background();
    do_star_field();
    /*
    if (game_state.keyboard[SDL_SCANCODE_LCTRL])
    {
        init_stage();
    }
    */
    if (new_highscore != NULL)
    {
        do_name_input();
    }
    else
    {
        if (game_state.keyboard[SDL_SCANCODE_LCTRL])
        {
            init_stage();
        }
    }
    if (++cursor_blink >= FPS)
    {
        cursor_blink = 0;
    }
}

static void draw(void)
{
    draw_background();
    draw_star_field();
    if (new_highscore != NULL)
    {
        draw_name_input();
    }
    else
    {
        draw_highscores();
    }
}
