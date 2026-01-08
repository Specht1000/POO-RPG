#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Entity.hpp"
#include "Inventory.hpp"
#include "Dice.hpp"
#include "Attack.hpp"
#include <iostream>
#include <string>
#include <vector>

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
    bool skipNextTurn;
    string className;
    string emoji;


public:
    Player();
    Player(const string& name);

    void attack(Entity& enemy);
    bool useLuck();

    void addGold(int amount);
    Inventory& getInventory();

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

    bool mustSkipTurn() const;
    void setSkipTurn(bool value);

    void applyClass(int choice);
    string getClassName() const;
    string getEmoji() const;

    void useItem(int index);

    int getGold() const;

    void useItemFromInventory(int index);

    int& goldRef();

    void addItemToInventory(const Item& it);

    int getDexterity() const;
    int getLuck() const;
};

#endif
