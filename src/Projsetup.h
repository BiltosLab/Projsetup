#ifndef PROJSETUP
#define PROJSETUP
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>

#define NAMELEN 100

const char cext[] = ".c";
const char headerext[] = ".h";
const char cppext[] = ".cpp";

const char readme[] = R"(
# This is a new project created by Projsetup app
)";

const char gitignore[] = R"(
/build
)";


const char header[] = R"(
#ifndef HEADER
#define HEADER
#endif
)";

// this is so we can concate the gcc command with the name of the file we have chosen :D idk if there's a better way to implement this
const char makeftop[] = R"(
CC = gcc
all:

)";

const char makefbot[] = R"(
clean:
	rm -rf ./build/*
)";

const char cfile[] = R"(
#include <stdio.h>

int main(int argc, char *argv[]) {
    printf("Hello, world!\n");
    return 0;
}
)";


const char cppfile[] = R"(
#include <iostream>

int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
)";





#endif