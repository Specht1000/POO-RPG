#include "Attack.hpp"

Attack::Attack(const string& name, int damage, int manaCost, AttackType type)
{
    this->name = name;
    this->damage = damage;
    this->manaCost = manaCost;
    this->type = type;
}

string Attack::getName() const
{
    return name;
}

int Attack::getDamage() const
{
    return damage;
}

int Attack::getManaCost() const
{
    return manaCost;
}

AttackType Attack::getType() const
{
    return type;
}
