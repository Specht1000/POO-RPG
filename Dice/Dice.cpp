#include "Dice.hpp"

int Dice::roll(int max)
{
    return (rand() % max) + 1;
}
