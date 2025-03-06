# Shoot'em Up

## Commands

Production

```bash
gcc -std=c99 -Wall -Werror -Wpedantic main.c -o app.exe
```

Development

```bash
gcc -Wall -Werror -Wpedantic \
-g -DDEBUG -std=c99 \
src/main.c -o build/app.exe \
-I D:/SDL2-2.30.11/include/SDL2 \
-L D:/SDL2-2.30.11/lib \
-lmingw32 -lSDL2main \
-lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer \
&& ./build/app
```
