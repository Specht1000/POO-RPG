#include "Entity.hpp"

Entity::Entity(const string& name, int life)
{
    this->name = name;
    this->life = life;
}

Entity::~Entity() {}

bool Entity::isAlive() const {
    return this->life > 0;
}

int Entity::getLife() const {
    return this->life;
}

void Entity::takeDamage(int dmg) {
    this->life -= dmg;
    if (this->life < 0)
        this->life = 0;
}
