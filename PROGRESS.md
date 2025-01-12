# Process register

## Process

### 12/01/2025

- **17:15:15**. Implement `do_enemies` function.
    - Set `entity_t` instance.
    - Loop through fighter linked list of stage until `e` is NULL.- Check the next conditions:
        1. The entity if diferent to the player instance.
        2. The player is not `NULL`.
        3. Decrease entity reload until is less than 0.
        4. Call `fire_alien_bullet` function.
- **15:24:12**. Add validation on `do_player`.
    - Now that player can be NULL, the program prevents that the logic inside function is executed.
- **14:55:43**. Update `logic` function.
    - Call `reset_stage` function when there is not player instances and `stage_reset_timer` is less than 0.
        - The scenario when the player is NULL happens when any enemy bullet hit the player.
        - We decrement the `stage_reset_timer` and when the value is 0 we reset the stage. This prevents that the game reset instantly.
- **14:20:16**. Implement `reset_stage` function.
    1. Clean fighters and bullets linked list from memory.
        - Delete any existing fighters or bullets.
    2. Set default `stage_t` struct values with `memset`.
    3. Set circular linked list for fighter and bullets.
    4. Move `init_player` from `init_stage` inside this function.
    5. Move `enemy_spawn_timer` and `stage_reset_timer` inside this function.
        - Reset timer default values.
- **13:47:22**. Add new texture.
    - `alien_bullet_texture` from `enemy_bullet.png`
    - `player_texture` from `player.png`
    - Use a different bullet texture for the enemy bullets.
    - Now load the player texture and cached it on its own variable, so the app dont wasted time and resource loading the image every time.
- **13:08:25**. Implement `calc_slope`.
    - Takes six arguments the x and y of sources coords, and x and y of destinations coords.
    - Two floats delta coords memory references.
    - This function calculates the step from one point to another.
    - The `dx` and `dy` will be always `1` or `-1`.
    - This will be used to tell the alien's bullets which way they need to go to reach their target when they are fired.
- **13:00:20*. Add new constasts.
    - `FSP`for timing calculation.
    - `ALIEN_BULLET_SPEED`this controlles the speed of enemies bullets while the are moving.

### 10/01/2025

- **20:55:50**. Update `bullet` y position.
    - Check is the index of the bullet is even or odd.
        - If its event, set `y` position on `-5`.
        - If its odd,s et `y` position on `5`.
- **20:40:17**. Allow the enemies to be shot more than once before they are destroyed.
- **20:33:29**. Add `bullet_hit_fighter` function.
    - Loop through linked list of fighters.
        - Check is entity are on same `side`.
        - Check is `collision` is `true` or `1` (is the same)
        - If the condition es true return 1.
        - Otherwise, return 0.
- **19:41:30**. Update `do_fighters` function.
    - Add `e->health == 0` condition so we delete the enemy when its health is equal to 0.
    - Add `health` property as `1` to all entities.
        - `player` entity.
        - `enemy` entity.
        - `bullet` entity.
        - This prevent to remove any entity before render becuase of conditions.
- **19:37:57**. Add `side` property on:
    - `init_player` as `SIDE_PLAYER`.
    - `spawn_enemies` as `SIDE_ALIEN`.
    - `fire_bullet` as `SIDE_PLAYER`.
- **19:37:33**. Add `MAX` and `MIN` function definitions.
- **16:39:03*. Add constants values.
    - `SIDE_PLAYER` and `SIDE_ALIENT` this will affect when firing bullets.
- **16:08:59**. Add new features.
    - Changes the spawn rates of the enemies.
    - Make the enemies move on the `y` axis as well as the `x`.
    - Provent enemy from leaving the top and bottom of the screen.
- **15:29:58**. Fix `do_fighters` functions.
    - No render the fighters properly.
    - Inside the for loop missed to check:
        - If fighter entity is different to player and entity x property is lower than negative entity width.
- **10:49:11**. Implement `draw_fighters` function.
    - Replace the `draw_player` function for this one.
    - Loop through linked list of players in stage and draw each one of them.
    - Use `blit` command for this.
- **10:33:57**. Add `spawn_enemies` function.
    - Decrements `enemy_spawn_timer` once it falls below 1.
    - The `enemy_t` object is added to the linked list of the stage object.
    - Place it at the right-hand of the screen.
        - The `y` coordinate is choosen randomly based on `SCREEN_HEIGHT`.
    - Set the texture property of cached variables we placed before `enemy_texture`.
    - Load the enemy texture with `SDL_QueryTexture`.
    - Set enemy `dx` randomly between -2 and -5 causing them move from right to left at differents speeds.
    - `enemy_spawn_timer` is reset to between 30 and 89 milliseconds.
        - This create a enemy between 0.5 and 1.5 seconds.
- **09:53:18**. Add two new functions on `init_stage`.
    - `do_fighters` functions.
        - Checks all the fighters on screen, include player.
        - Step through all the fighters in the linked list of stage and add to each one's dx and dy to ther x and y respectively to move then.
        - Check is the fighter in question is the player.
             - If not and it reaches the left-hand side of the screen, we delete it.
- **09:38:31**. Update `stage.c` to handle enemies.
    - Add `enemy_texture` and `enemy_spawn_timer`.
- **09:23:13**. Add .gitignore on proyect 006.
- **09:20:47**. Update player and bullets sprite.
    - Change the graphics.
    - Change the background color.
- **08:33:42**. Update spread shoots.
    - Change the formula of the random number to be more preciselly.
        ```c
        bullet->dy = ((float)(rand() % 100) / 50.0f) - 1.0f;
        ```
- **08:20:03**. Add two shots at once.
    - Update the `fire_bullet` function.
        - Use a for loop to create two bullets instances.
        - Adjust the `x` and `y` por each bullets.
            - `-5` on y position when is the first bullet.
            - `5` on y for the second bullet.
    - Spread the bullets randomly.
        - Adjust the `dy` property.
        - Use the `rand()` function for the `stdlib` header.
            - `rand() % 5` generate a random number between 0 and 4.
            - Extract `2` on the generate number so we add value between -2 or 2 for each bullet.

### 06/01/2025

- **19:29:12**. Upgrade delay system with `cap_frame_rate` function.
    - Replace `SDL_Delay(16)`.
    - Create kind of maths to attempt an accurate 60fps.
- **19:21:25**. Update `main.c` game loop.
    - Remove all the referece of `player` and `bullet` entities. Now we handle it on stage file.
    - Now use the `init_stage()` to setup the main game.
        - Call `app.delegate.logic()` and `app.delegate.draw()` every loop of the game loop.To perform the game logic and draw the scene.
- **19:13:39**. Implement `draw_player` and `draw_bullet` functions.
    - Basically render on the screen the player texture and list of bullets texture.
- **19:06:10**. Implement `do_bullets` function.
    - Create two `entity_t` pointers variables called `*b` and `*prev`.
    - Loop through our linked list of bullets.
    - Move each bullet by adding the `dx` and `dy` to the `x` and `y` respectively.
    - If the bullets reaches the right-hand side of the screen, we delete the bullet.
- **18:56:15**. Implement `fire_bullet` function.
    - Create a bullet `entity_t` object.
    - Add the entity to the linked list.
    - Set bullet x and y coords to the same as player x and y coords.
    - Set bullet dx property to `PLAYER_BULLET_SPEED` this make the bullet move faster.
    - Set bullet health to 1.
    - Set bullet texture from the `bullet_texture` that we define on the file scope.
    - Change the bullet position a little more centrally of the player.
        - This is done by using player height and bullets height divide by 2.
    - Set `player->reload` to `8` this tell to the game that 8 frames (approx 0.133333 seconds) must pass before we can shoot another bullet.
- **18:49:09**. Implement `do_player` function.
    - Basically move the movement logic from `main.c` to `stage.c` file.
    - Check inside of `app.keyboard` array of what keys are active.
    - Decrease the `player->reload` in case that is greater than zero.
        - Reload controls how fast the player can fire.
- **15:31:58**. Implement `init_player` function.
    - Memory allocated entity instances and save on player variable.
    - Check is the memory allocation was successfully.
    - Set player values with `memset()`.
    - Asignate the `fighter_tail` next property to `player` variable.
        - Set the current stage fighter tail equals to `player`.
    - Set pointer `player` properties.
        - `x` equals to `100`.
        - `y` equals to `100`.
        - `texture` equals to the texture load of `rocket.png`.
    - Render the player texture on screent with `SDL_QueryTexture`.
- **15:28:44**. Implement `init_stage` function.
    - Sets up a number of things for playing the game. It assigns the delegate's logic and draw pointers to two static logic and draw functions of its own, and also prepares the fighter and bullet linked lists for use. It then calls the `init_player` function.
    - Add `logic` and `draw` function to `delegate` property of `app` instances.
    - Set stage global variables values with `memset()` function.
    - Set stage figther and bullet tails equals to memory stage fighter and bullet heads.
    - Call `init_player` function.
    - Load `fire_bullets.png` graphics textures.
- **15:26:40**. Add stage.c file.
    - Its responsabile for handling the game logic.
    - Initialice `player` and `bullet_texture` static pointer variables.
        ```c
        static entity_t *player;
        static SDL_Texture *bullet_texture;
        ```
    - NOTE. `static` function means that this functions only works on the current file (scope).
    - Initialice static function for this `stage.c` file.
- **14:06:19**. Refactor player inputs.
    - Change `do_key_down` and `do_key_up`.
        - Reduce ifs conditionals to only check repeated events, event scancode is less then `MAX_KEYBOARD_KEYS`.
            - If so, then add the scancode to our `app.keyboard array and set it to `1`.
            - Otherwise, for `do_key_up` set the value to 0.
- **13:41:59*. Add `stage_t` struct.
    - Handle the fither and bullet entities.
- **13:37:35**. Refactor `app_t` struct.
    - Remove arrow keys properties.
    - Add keyboard with `MAX_KEYBOARD_KEYS` that is 350 values.
        - This represent array of 350 slots of int type.
    - Add delete property of `delegate_t` type.
- **13:34:16**. Add new properties to `Entity` struct.
    - Update x, y, dx and dy to `float` type.
    - Add reloat `int` property and `*next` pointer of `entity_t`.
- **13:27:45**. Add `Delegate` struct.
    - Make to dynamic function as `Delagate` properties.
        - `void (*logic)(void)` a logic function that receives not args and return nothing.
        - `void (*draw)(void)` a draw function that receives not args and return nothing.
    - Use this functions to dynamic change the behavior of the game.
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
