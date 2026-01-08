#ifndef ATTACK_HPP
#define ATTACK_HPP

#include <string>

using namespace std;

enum AttackType {
    LIGHT,
    HEAVY,
    MAGIC
};

class Attack {
private:
    string name;
    int damage;
    int manaCost;
    AttackType type;

public:
    Attack(const string& name, int damage, int manaCost, AttackType type);
    string getName() const;
    int getDamage() const;
    int getManaCost() const;
    AttackType getType() const;
};

#endif
