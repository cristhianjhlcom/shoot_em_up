# Process register

## Process

### 06/01/2025

- **09:06:46**. Add fire bullets.
    - Declare a new bullet entity `entity_t bullet;` and set default values with `memset(&bullet, 0, sizeof(entity_t));`.
    - Inside the game loop with handle the next interaction:
        - If the player trying to fire and the bullet is out of screen.
            ```c
            if (app.fire && bullet.health == 0) {
                bullet.x = player.x + 130;
                bullet.y = player.y + 45;
                bullet.dx = 16;
                bullet.dy = 0;
                bullet.health = 1;
            }
            ```
        - Set the bullet `speed` increased by x and y delta value.
            ```c
            bullet.x += bullet.dx;
            bullet.y += bullet.dy;
            ```
        - If the bullet go out the screen, kill the bullet by setting the health to 0 `bullet.health = 0;`.
        - If the health of bullet is greater than 0 would mean that the bullet is running throuth the screen so it have to be rendered with `blit()` function.
- **08:49:57**. Update `input` events.
    - Add `LCTRL` key event to handle the fire.
    - `event->keysym.scancode == SDL_SCANCODE_LCTRL` add the scancode to check the key.
        - keydown update `app.fire = 1;` value.
        - keyup update `app.fire = 0;` value.
- **08:45:45**. Add new properties on `entity_t` struct.
    - `dx`, `dy` and `health`.
    - These three properties will handle the delta `x` and `y` of the entity.
    - The health property checks is the entity is alive if the health of zero would mean the entity is dead and could be deleted.
- **08:42:55**. Add `fire` property on `app_t` struct.
    - This track when the fire key is pressing.
    - The main idea is only let the player shoot when the bullet is out of screen or touch the edge.

### 05/01/2025

- **22:49:20**. Update the player movement speed to `5`.
- **22:46:21**. Add collision with edge of screen.
    - Prevent the player graphic go off the screen.
        - If `player.x` and `player.y` are on `(0, 0)` coords on screen, set player x and y equal to 0.
        - If `player.x` and `player.y` are greatter than screen width or screen height minus the size of player, set the player x and y properties equal to size of screen minus size of player graphics.
            - Size of screen is `1260x720`.
            - Size of player is `151x101`.
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
