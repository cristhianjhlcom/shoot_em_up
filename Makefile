BUILD_DIR 		= build
SOURCE_DIR 		?= src
INCLUDE_DIR 	= include
SDL2_PATH		= D:/SDL2-2.30.11
DEBUG			= 1
STANDART 		= -std=c99

CC 				= gcc
INCLUDE 		= -I include -I ${SDL2_PATH}/include
LDLIBS 			= -L ${SDL2_PATH}/lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer
SOURCES			= $(wildcard ${SOURCE_DIR}/**/*.c ${SOURCE_DIR}/*.c)
OBJECTS			= $(patsubst ${SOURCE_DIR}/%.c, ${BUILD_DIR}/%.o, $(SOURCES))
TARGET 			= ${BUILD_DIR}/app.exe

ifeq ($(OS), Windows_NT)
	# CLEAN 		= del /f ${TARGET} & if exist ${BUILD_DIR} rmdir /s /q ${BUILD_DIR}
	CLEAN 		= rm -f ${TARGET} && [ -d ${BUILD_DIR} ] && rm -r ${BUILD_DIR}
else
	CLEAN 		= rm -r ${TARGET} ${BUILD_DIR}
endif

ifeq (${DEBUG}, 1)
	CFLAGS		= -Wall -Werror -Wpedantic -Wwrite-strings -Wconversion \
					-g -DDEBUG -Wshadow -Wmissing-prototypes -Wmissing-declarations \
					-Wfloat-equal -Wsign-compare -Wundef -Wcast-align -Wstrict-prototypes \
					-Wno-switch-default -Wold-style-definition -Wmissing-include-dirs
else
	CFLAGS		= -Wall -Werror -Wpedantic -Wwrite-strings -Wconversion \
					-O0 -Wshadow -Wmissing-prototypes -Wmissing-declarations \
					-Wfloat-equal -Wsign-compare -Wundef -Wcast-align -Wstrict-prototypes \
					-Wno-switch-default -Wold-style-definition -Wmissing-include-dirs
endif

.PHONY: all clean run build

all: build run

rebuild: clean build run
	
build/%.o: src/%.c
	@mkdir -p $(dir $@)
	$(CC) ${STANDART} $(CFLAGS)  -c $< -o $@ ${INCLUDE}

$(TARGET): $(OBJECTS)
	$(CC) ${STANDART} $(OBJECTS) -o $(TARGET) ${INCLUDE} $(LDLIBS)

clean:
	${CLEAN}

run: $(TARGET)
	./$(TARGET)
