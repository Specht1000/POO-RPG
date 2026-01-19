#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <string>

using namespace std;

class Entity {
protected:
    string name;
    int life;

public:
    Entity(const string& name, int life);
    virtual ~Entity();

    bool isAlive() const;
    int getLife() const;

    void takeDamage(int dmg);
};

#endif
