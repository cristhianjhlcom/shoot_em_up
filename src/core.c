#include "core.h"

bool init(void)
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        SDL_Log("SDL initialization failed %s\n", SDL_GetError());
        return false;
    }

    app.window = SDL_CreateWindow("Shoot Em Up", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    if (app.window == NULL)
    {
        SDL_Log("SDL Window creation failed %s\n", SDL_GetError());
        return false;
    }

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");

    app.renderer = SDL_CreateRenderer(app.window, -1, SDL_RENDERER_ACCELERATED);
    if (app.renderer == NULL)
    {
        SDL_Log("SDL Renderer creation failed %s\n", SDL_GetError());
        SDL_DestroyWindow(app.window);
        return false;
    }

    int image_flags = IMG_INIT_PNG | IMG_INIT_JPG;
    if (!(IMG_Init(image_flags) & image_flags))
    {
        SDL_Log("SDL image initialization failed %s\n", IMG_GetError());
        return false;
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) == -1)
    {
        SDL_Log("SDL mixer initialization failed %s\n", Mix_GetError());
        return false;
    }
    Mix_AllocateChannels(MAX_SND_CHANNELS);

    SDL_ShowCursor(0);

    return true;
}

void init_game(void)
{
    init_background();
    init_star_field();
    init_sounds();
    init_fonts();
    init_highscore_table();
    load_music("assets/musics/Mercury.ogg");
    play_music(1);
}

void cleanup(void)
{
    Mix_Quit();
    IMG_Quit();
    SDL_DestroyRenderer(app.renderer);
    SDL_DestroyWindow(app.window);
    app.renderer = NULL;
    app.window = NULL;
    SDL_Quit();
}

void cap_frame_rate(long *then, float *remainder)
{
   long wait, frame_time; 
   wait = (long) (16 + *remainder);
   *remainder -= (int) *remainder;
   frame_time = (long) SDL_GetTicks() - *then;
   wait -= frame_time;
   if (wait < 1)
   {
        wait = 1;
   }
   // SDL_Log("FPS: %ld", wait);
   SDL_Delay((Uint32) wait);
   *remainder += (float) 0.667;
   *then = (long) SDL_GetTicks();
}
