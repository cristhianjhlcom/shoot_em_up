# Variables
CC = gcc
CFLAGS = -Wall -I./src $(shell sdl2-config --cflags)
LDFLAGS = $(shell sdl2-config --libs) -lSDL2_image

# Archivos fuente y ejecutable
SRC = $(wildcard src/*.c)
OBJ = $(SRC:.c=.o)
TARGET = game

# Reglas de compilación
all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

# Copiar los recursos gráficos al directorio de compilación
resources:
	@mkdir -p graphics
	@cp -r src/graphics ./graphics

# Limpiar archivos temporales
clean:
	rm -f $(OBJ) $(TARGET)
	rm -rf graphics

# Reglas de phony
.PHONY: all clean resources
