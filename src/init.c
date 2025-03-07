typedef struct
{
    SDL_Renderer *renderer;
    SDL_Window *window;
    bool is_running;
    SDL_Event event;
} app_t;

app_t app;

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
    }

    return true;
}

void cleanup(void)
{
    SDL_DestroyRenderer(app.renderer);
    SDL_DestroyWindow(app.window);
    app.renderer = NULL;
    app.window = NULL;
    SDL_Quit();
}
