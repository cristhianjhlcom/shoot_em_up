# Shoot 'em Up
# cp D:/SDL2-2.30.11/bin/*.dll build/

DEBUG = 1

INCLUDE_DIR = include
SOURCE_DIR = src
BUILD_DIR = build
SDL_DIR = D:/SDL2-2.30.11

C_STANDARD = c2x
CC = gcc
C_WARNINGS = -Wall -Werror -Wpedantic
C_FLAGS = $(C_WARNINGS) -std=$(C_STANDARD) -I $(INCLUDE_DIR) -I$(SDL_DIR)/include/SDL2
LD_FLAGS = -L$(SDL_DIR)/lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer

ifeq ($(DEBUG), 1)
C_FLAGS += -g -DDEBUG
else
C_FLAGS += -O2
endif

OUTPUT = output
COMPILER = $(CC) $(C_FLAGS)

C_SOURCES = $(wildcard $(SOURCE_DIR)/*.c)
C_OBJECTS = $(patsubst $(SOURCE_DIR)/%.c, $(BUILD_DIR)/%.o, $(C_SOURCES))

all: create build

create:
	@mkdir -p build

build: $(C_OBJECTS)
	$(COMPILER) $(C_OBJECTS) $(LD_FLAGS) -o $(BUILD_DIR)/$(OUTPUT)

execute:
	./$(BUILD_DIR)/$(OUTPUT)

# install:
#     sudo apt-get update
#     sudo apt-get install libsdl2-dev libsdl2-image-dev

clean:
	rm -rf $(BUILD_DIR)/*

$(BUILD_DIR)/%.o: $(SOURCE_DIR)/%.c
	$(COMPILER) -c $< -o $@

.PHONY: create build execute clean
