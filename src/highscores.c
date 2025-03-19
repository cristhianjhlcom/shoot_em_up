#include "highscores.h"

static highscores_t highscores;

static int highscore_comparator(const void *a, const void *b);
static void logic(void);
static void draw(void);
static void draw_highscores(void);

void init_highscore_table(void)
{
    memset(&highscores, 0, sizeof(highscores_t));
    for (int idx = 0; idx < NUM_HIGHSCORE; idx++)
    {
        highscores.highscore[idx].score = NUM_HIGHSCORE - idx;
    }
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
    for (int idx = 0; idx < NUM_HIGHSCORE; idx++)
    {
        new_highscores[idx] = highscores.highscore[idx];
        new_highscores[idx].recent = 0;
    }
    new_highscores[NUM_HIGHSCORE].score = score;
    new_highscores[NUM_HIGHSCORE].recent = 1;
    qsort(new_highscores, NUM_HIGHSCORE + 1, sizeof(highscore_t), highscore_comparator);
    for (int idx = 0; idx < NUM_HIGHSCORE; idx++)
    {
        highscores.highscore[idx] = new_highscores[idx];
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
    int i, y;
    y = 150;
    draw_text(425, 70, 255, 255, 255, "HIGHSCORES");
    for (i = 0 ; i < NUM_HIGHSCORE ; i++)
    {
        if (highscores.highscore[i].recent)
        {
            draw_text(425, y, 255, 255, 0, "#%d ............. %03d", (i + 1), highscores.highscore[i].score);
        }
        else
        {
            draw_text(425, y, 255, 255, 255, "#%d ............. %03d", (i + 1), highscores.highscore[i].score);
        }
        y += 50;
    }
    draw_text(425, 600, 255, 255, 255, "PRESS FIRE TO PLAY!");
}

static void logic(void)
{
    do_background();
    do_star_field();
    if (game_state.keyboard[SDL_SCANCODE_LCTRL])
    {
        init_stage();
    }
}

static void draw(void)
{
    draw_background();
    draw_star_field();
    draw_highscores();
}
