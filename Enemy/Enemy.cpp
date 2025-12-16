#include "Enemy.hpp"

Enemy::Enemy(const string& race)
    : Entity("", 0, 0)
{
    this->name = race;
    this->life = 50;
    this->strength = 8;
    this->rewardGold = 20;
    attacks.clear();
    attacks.push_back(Attack("Griffe", 8, 0, LIGHT));
    attacks.push_back(Attack("Morsure", 12, 0, HEAVY));

}

int Enemy::getReward() const {
    return this->rewardGold;
}

Attack Enemy::randomAttack() const
{
    int i = rand() % attacks.size();
    return attacks[i];
}

