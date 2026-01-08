#ifndef ENEMY_HPP
#define ENEMY_HPP

#include "Entity.hpp"
#include "Attack.hpp"
#include <vector>
#include <string>

using namespace std;

class Enemy : public Entity {
private:
    string race;
    string emoji;

    vector<Attack> attacks;
    int rewardGold;

public:
    Enemy(const string& race);

    string getRace() const;
    string getEmoji() const;
    int getReward() const;

    Attack randomAttack() const;
};

#endif
