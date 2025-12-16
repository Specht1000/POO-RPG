#include "Board.hpp"
#include <iostream>
#include <fstream>

using namespace std;

Board::Board()
{
    heroEmoji  = "🧙";
    enemyEmoji = "👹";
    itemEmoji  = "🎁";
    wallEmoji  = "🧱";
    floorEmoji = "  ";
}

void Board::loadFromFile(const string& filename)
{
    map.clear();

    ifstream file(filename);
    string line;

    while (getline(file, line)) {
        if (!line.empty() && line.back() == '\r') {
            line.pop_back(); // remove CR do Windows
        }
        map.push_back(line);
    }

    file.close();
}

string Board::symbolToEmoji(char c) const
{
    switch (c) {
        case 'H': return heroEmoji;
        case 'E': return enemyEmoji;
        case 'I': return itemEmoji;
        case '#': return wallEmoji;
        case '.': return floorEmoji;
        default:  return "?";
    }
}

void Board::display() const
{
    for (const string& line : map) {
        for (char c : line) {
            cout << symbolToEmoji(c);
        }
        cout << endl;
    }
}

char Board::getCell(int x, int y) const
{
    return map[y][x];
}

void Board::setCell(int x, int y, char c)
{
    map[y][x] = c;
}

int Board::getWidth() const
{
    return map[0].size();
}

int Board::getHeight() const
{
    return map.size();
}

int Board::countEnemies() const
{
    int count = 0;
    for (const string& line : map)
        for (char c : line)
            if (c == 'E')
                count++;
    return count;
}

void Board::findHero(int& x, int& y) const
{
    for (int y0 = 0; y0 < getHeight(); y0++)
        for (int x0 = 0; x0 < getWidth(); x0++)
            if (map[y0][x0] == 'H') {
                x = x0;
                y = y0;
                return;
            }
}

bool Board::isInside(int x, int y) const
{
    return x >= 0 && y >= 0 &&
           x < getWidth() && y < getHeight();
}