#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <string>

using namespace std;

class Entity {
protected:
    string name;
    int life;
    int strength;

public:
    Entity(const string& name, int life, int strength);
    virtual ~Entity();

    bool isAlive() const;
    int getLife() const;
    int getStrength() const;

    void takeDamage(int dmg);
};

#endif
