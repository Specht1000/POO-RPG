#ifndef GAME_HPP
#define GAME_HPP

#include "Player.hpp"
#include "Board.hpp"
#include "Merchant.hpp"
#include "Enemy.hpp"
#include "Dice.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>

using namespace std;

// 🔹 Forward declaration
class Enemy;

class Game {
private:
    Player player;
    Board board;
    Merchant merchant;
    bool justInteracted;

public:
    Game();

    void run();
    void loop();
    void doTurnMenu();
    void moveWithDice();
    void openMerchant();
    void useItemMenu();
    void loadMap(const string& filename);
    bool movePlayer(int dx, int dy);

    void combat(Enemy& enemy);
    Item generateRandomItem();

    void checkEndGame();
    void showVictory();
    void showGameOver();

    void chooseClass();
};

#endif
