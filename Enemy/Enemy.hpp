#ifndef ENEMY_HPP
#define ENEMY_HPP

#include "Entity.hpp"
#include "Attack.hpp"
#include <vector>
#include <string>

using namespace std;

class Enemy : public Entity {
private:
    int rewardGold;
    vector<Attack> attacks;

public:
    Enemy(const string& race);

    int getReward() const;
    Attack randomAttack() const;
};

#endif
