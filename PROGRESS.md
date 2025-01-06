# Process register

## Process

### 05/01/2025

- **22:01:44**. Dealing with player movement.
    - Simple adds interation with and of app movement properties change from 0 to 1.
        - `app.up` updates `player.y -= 4`.
        - `app.down` updates `player.y += 4`.
        - `app.left` updates `player.x -= 4`.
        - `app.right` updates `player.x += 4`.
- **21:53:10**. Add press keys events.
    - Add to function to handle when user press and release an arrow key.
        - `do_key_down` when the user press the key arrow.
            - Checks with ifs statement when any of four arrow keys is pressing.
        - `do_key_up` when the user released the key arrow.
            - Checks with ifs statement when any of four arrow keys is released.
    - Pass the keyboad event that triggers those events.
    - Ignore the repeated keyboard events with `event->repeat == 0`.
        - Deal only with events where the key has been pushed down for the first time.
    - Its almost the same on both functions.
- **21:45:37**. Add `app_t` struct properties.
    - `int up`.
    - `int down`.
    - `int left`.
    - `int right`.
    - This properties will track out movement request when we press any arrow keys.
- **16:14:03**. Update windows size constant to 1260 width and 760 height.
- **16:12:56**. Update graphic image to `src/graphics/rocket.png`.
- **16:11:03**. Add `-lSDL2_image` linked on compile script.
- **16:06:44**. Update main entry point.
    - Declare `player` variable of `entity_t` type.
    - Set player default with `memset()`.
    - Set `player` x and y properties as `100` and `texture` as `load_texture("graphics/rocket.png")`.
    - Inside game loop call blit function with `player` properties.
- **16:02:32**. Add new `entity_t` struct. This struct represents the player.
    - x and y coordinates.
    - textures that will use.
- **15:46:32**. Add blit function.
    - This function simple draws the specified texture on screen at the specified x and y coordinates.
- **15:11:43**. Add load texture function.
    - Define the `load_texture` function signature.
    - Create a pointer of `texture` that is type `SDL_Texture`.
    - Log a message with specificy category and priority.
    - Save the texture on variable using `IMG_LoadTexture` function.
    - return the `texture` pointer.
    - This function is simple it calls the `LoadTexture` function to load an imagen and return as a texture.
- **15:05:58**. Add `SDL_Image`.
    - This line initialice image library with `IMG_Init` function, and we pass as arguments:
        - `IMG_INIT_PNG`.
        - `IMG_INIT_JPG`.
    - Now I can use it to load texture.
- **14:55:19**. In the previous lesson we create a simple windows. In this steps I gonna load and draw graphics.

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
