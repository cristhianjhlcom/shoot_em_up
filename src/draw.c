void prepare_scene(void)
{
    SDL_SetRenderDrawColor(app.renderer, 96, 128, 255, 255);
    SDL_RenderClear(app.renderer);
}

void present_scene(void)
{
    SDL_RenderPresent(app.renderer);
}
