#include "setup.h"
#include <stdlib.h>

int main(int argc, char *argv[]) {
    init_SDL();

    cleanup();

    return EXIT_SUCCESS;
}
