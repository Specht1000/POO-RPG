#include "Player.hpp"
#include "Dice.hpp"
#include <iostream>

using namespace std;

Player::Player()
    : Entity("", 0, 0)
{
    this->name = "Heros";
    this->life = 100;
    this->strength = 10;
    this->dexterity = 5;
    this->luck = 5;
    this->gold = 0;
    this->x = 0;
    this->y = 0;
    this->mana = 50;

    attacks.clear();
    attacks.push_back(Attack("Attaque légère", 10, 0, LIGHT));
    attacks.push_back(Attack("Attaque lourde", 25, 0, HEAVY));
    attacks.push_back(Attack("Sort magique", 35, 15, MAGIC));
}

Player::Player(const string& name)
    : Entity("", 0, 0)
{
    this->name = name;
    this->life = 100;
    this->strength = 10;
    this->dexterity = 5;
    this->luck = 5;
    this->gold = 0;
    this->x = 0;
    this->y = 0;
    this->mana = 50;

    attacks.clear();
    attacks.push_back(Attack("Attaque légère", 10, 0, LIGHT));
    attacks.push_back(Attack("Attaque lourde", 25, 0, HEAVY));
    attacks.push_back(Attack("Sort magique", 35, 15, MAGIC));
}

void Player::attack(Entity& enemy) {
    int damage = this->strength;

    if (useLuck()) {
        damage += Dice::roll(6);
        cout << "Chance utilisée ! Dégâts augmentés." << endl;
    }

    enemy.takeDamage(damage);
}

bool Player::useLuck() {
    int roll = Dice::roll(6);
    return roll <= this->luck;
}

void Player::addGold(int amount) {
    this->gold += amount;
}

Inventory& Player::getInventory() {
    return this->inventory;
}

void Player::setPosition(int x, int y)
{
    this->x = x;
    this->y = y;
}

int Player::getX() const
{
    return this->x;
}

int Player::getY() const
{
    return this->y;
}

int Player::getLife() const
{
    return this->life;
}

void Player::takeDamage(int dmg)
{
    this->life -= dmg;
    if (this->life < 0)
        this->life = 0;
}

bool Player::isAlive() const
{
    return this->life > 0;
}

void Player::showAttacks() const
{
    for (size_t i = 0; i < attacks.size(); i++) {
        cout << i + 1 << ". " << attacks[i].getName()
             << " (dégâts: " << attacks[i].getDamage() << ")" << endl;
    }
}

Attack Player::chooseAttack(int index)
{
    if (attacks.empty()) {
        // sécurité absolue
        return Attack("Attaque nulle", 0, 0, LIGHT);
    }

    if (index < 0 || index >= (int)attacks.size()) {
        return attacks[0];
    }

    return attacks[index];
}

void Player::heal(int amount)
{
    this->life += amount;
    if (this->life > 150)   // limite max (optionnel)
        this->life = 150;
}

void Player::boostDamage(int amount)
{
    for (Attack& atk : attacks) {
        atk = Attack(
            atk.getName(),
            atk.getDamage() + amount,
            atk.getManaCost(),
            atk.getType()
        );

    }
}

int Player::getMana() const
{
    return mana;
}

bool Player::useMana(int cost)
{
    if (mana < cost)
        return false;
    mana -= cost;
    return true;
}