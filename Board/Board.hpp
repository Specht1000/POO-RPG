#ifndef BOARD_HPP
#define BOARD_HPP

#include <vector>
#include <string>
using namespace std;

class Board {
private:
    vector<string> map;
    string heroEmoji;
    string enemyEmoji;
    string itemEmoji;
    string wallEmoji;
    string floorEmoji;

    string symbolToEmoji(char c) const;

public:
    Board();                       // par défaut

    void loadFromFile(const string& filename);
    void display() const;

    void setHeroEmoji(const string& e);

    char getCell(int x, int y) const;
    void setCell(int x, int y, char c);

    int getWidth() const;
    int getHeight() const;

    void findHero(int& x, int& y) const;

    int countEnemies() const;

    bool isInside(int x, int y) const;
};

#endif
