#ifndef GAME_HPP
#define GAME_HPP

#include "Player.hpp"
#include "Board.hpp"
#include <string>

using namespace std;

// 🔹 Forward declaration
class Enemy;

class Game {
private:
    Player player;
    Board board;

public:
    Game();

    void run();
    void loop();
    void loadMap(const string& filename);
    void movePlayer(int dx, int dy);

    void combat(Enemy& enemy);   // agora OK
    Item generateRandomItem();

    void checkEndGame();
    void showVictory();
    void showGameOver();
};

#endif
