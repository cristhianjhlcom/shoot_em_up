##############
# INIT SETUP #
##############
cmake_minimum_required(VERSION 3.30.4)
project(SDL2Guide C)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
add_compile_options(-Wall -Werror -Wpedantic)

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

###########
# FOLDERS #
###########
set(SOURCE_DIR "src")
set(INCLUDE_DIR "include")
set(BUILD_DIR "build")
set(SDL_DIR "D:/SDL2-2.30.11")

include_directories(${INCLUDE_DIR} "${SDL_DIR}/include/SDL2")

file(GLOB SOURCES "${SOURCE_DIR}/*.c")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR})

set(OUTPUT "output")
if (CMAKE_BUILD_TYPE STREQUAL "Release")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O2")
    set(OUTPUT "app")
else()
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -DDEBUG")
endif()

###################
# COMPILE OPTIONS #
###################
set(CMAKE_C_STANDARD 23) # c2x
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Werror -Wpedantic")

##############
# EXECUTABLE #
##############
add_executable(${OUTPUT} ${SOURCES})

set_property(TARGET ${OUTPUT} PROPERTY C_STANDARD 23)

set(SDL2_LIBS "-L${SDL_DIR}/lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf")

target_link_libraries(${OUTPUT} ${SDL2_LIBS})
