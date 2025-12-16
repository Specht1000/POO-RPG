#include "Input.hpp"
#include <termios.h>
#include <unistd.h>
#include <cstdio>

static struct termios oldt;
static struct termios newt;

void Input::init()
{
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;

    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
}

void Input::restore()
{
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
}

char Input::getKey()
{
    return getchar();
}
