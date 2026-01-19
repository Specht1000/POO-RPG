#include "Enemy.hpp"

Enemy::Enemy(const string& r) : Entity("", 0)
{
    race = r;
    attacks.clear();

    // defaults
    rewardGold = 10;
    emoji = "👾";

    if (race == "Gobelin") {
        name = "Gobelin";
        life = 60;
        emoji = "👺";
        rewardGold = 8;

        attacks.push_back(Attack("Griffe", 8, 0, LIGHT));
        attacks.push_back(Attack("Morsure", 12, 0, HEAVY));
    }
    else if (race == "Gnome") {
        name = "Gnome";
        life = 50;
        emoji = "🧌";
        rewardGold = 10;

        attacks.push_back(Attack("Coup", 7, 0, LIGHT));
        attacks.push_back(Attack("Marteau", 14, 0, HEAVY));
    }
    else if (race == "Orc") {
        name = "Orc";
        life = 80;
        emoji = "👹";
        rewardGold = 15;

        attacks.push_back(Attack("Cogne", 10, 0, LIGHT));
        attacks.push_back(Attack("Charge", 18, 0, HEAVY));
    }
    else if (race == "Squelette") {
        name = "Squelette";
        life = 55;
        emoji = "💀";
        rewardGold = 12;

        attacks.push_back(Attack("Os", 8, 0, LIGHT));
        attacks.push_back(Attack("Frappe", 13, 0, HEAVY));
    }
    else {
        name = race;
        life = 55;
        emoji = "👾";
        rewardGold = 10;

        attacks.push_back(Attack("Coup", 8, 0, LIGHT));
        attacks.push_back(Attack("Frappe", 12, 0, HEAVY));
    }
}

string Enemy::getRace() const 
{ 
    return race; 
}

string Enemy::getEmoji() const 
{ 
    return emoji;
}

int Enemy::getReward() const 
{ 
    return rewardGold; 
}

Attack Enemy::randomAttack() const
{
    if (attacks.empty())
        return Attack("Coup", 5, 0, LIGHT);

    int idx = rand() % attacks.size();
    return attacks[idx];
}
