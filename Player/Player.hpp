#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Entity.hpp"
#include "Inventory.hpp"
#include <string>
#include <vector>
#include "Attack.hpp"

using namespace std;

class Player : public Entity {
private:
    int dexterity;
    int luck;
    int gold;
    Inventory inventory;
    int x;
    int y;
    vector<Attack> attacks;
    int mana;

public:
    Player();                    // construtor padrão
    Player(const string& name);  // construtor com nome

    void attack(Entity& enemy);
    bool useLuck();

    void addGold(int amount);          // ← FALTAVA
    Inventory& getInventory();         // ← FALTAVA

    void setPosition(int x, int y);
    int getX() const;
    int getY() const;

    int getLife() const;
    void takeDamage(int dmg);
    bool isAlive() const;

    void showAttacks() const;
    Attack chooseAttack(int index);

    void heal(int amount);
    void boostDamage(int amount);

    int getMana() const;
    bool useMana(int cost);
};

#endif
