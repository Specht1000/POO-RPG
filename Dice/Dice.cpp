#include "Dice.hpp"
#include <cstdlib>

int Dice::roll(int max)
{
    return (rand() % max) + 1;
}
