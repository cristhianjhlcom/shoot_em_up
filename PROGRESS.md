# Process register

## Process

### 04/01/2025

- **10:55:33**. Implement main entry point.
    - Set default values of our `app_t` struct on 0, using `memset()`.
    - Call SDL initialization function.
    - Call `cleanup` function when the app is closed with `atexit()` function.
    - Inside the game loop call the next functions.
        - `prepare_scene`.
        - `do_input`.
        - `present_scene`.
        - `SDL_Delay(16)` to makes the game runs at 60 FPS.
- **10:53:35**. Implement inputs handlers logic.
    - Create a `SDL_Event` variable.
    - Use a while loop to watch all `SDL_PollEvent()`.
        - Check the `event.type` with a `switch` statement.
            - `SDL_QUIT` case, close the windows with `exit(1)`.
- **10:50:47**. Implement initialization functions.
    - Create variables for windows flags and renderer flags.
    - Create a window entity and save on `app.window` property.
        - Check if the entity was created successfully.
    - Create a renderer entity and save on `app.renderer` property.
        - Check if the entity was created successfully.
- **10:43:15**. Create new windows.
    - Define windows size constants.
        ```c
        #define SCREEN_WIDTH 800
        #define SCREEN_HEIGHT 600
        ```
    - Create initialization functions.
        - Check is SDL2 is already installed.
        - Create a cleanup function to execute on exit the program.
    - Create the draw logic to render the windows on screen.
        - Create `prepare_scene` that loads the color and render the windows.
        ```c
        SDL_SetRenderDrawColor(app.renderer, 61, 63, 77, 255);
        SDL_RenderClear(app.renderer);
        ```
        - Create `present_scene` that render the created windows on screent and update it.
        ```c
        void present_scene(void) {
            SDL_RenderPresent(app.renderer);
        }
        ```
    - Create `app_t` struct to handle renderer and window entities.
        ```c
        typedef struct App {
            SDL_Renderer *renderer;
            SDL_Window *window;
        } app_t;
        ```
