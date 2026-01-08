#ifndef INPUT_HPP
#define INPUT_HPP

#include <termios.h>
#include <unistd.h>
#include <cstdio>

class Input {
public:
    static void init();
    static void restore();
    static char getKey();
};

#endif
