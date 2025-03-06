void inputs(void)
{
    while (SDL_PollEvent(&app.event))
    {
        switch (app.event.type)
        {
            case SDL_QUIT:
                app.is_running = false;
                break;
            default:
                break;
        }
    }
}
