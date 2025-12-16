#include "Entity.hpp"

Entity::Entity(const string& name, int life, int strength)
{
    this->name = name;
    this->life = life;
    this->strength = strength;
}

Entity::~Entity() {}

bool Entity::isAlive() const {
    return this->life > 0;
}

int Entity::getLife() const {
    return this->life;
}

int Entity::getStrength() const {
    return this->strength;
}

void Entity::takeDamage(int dmg) {
    this->life -= dmg;
    if (this->life < 0)
        this->life = 0;
}
