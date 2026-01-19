#include "Board.hpp"
#include <iostream>
#include <fstream>

Board::Board()
{
    heroEmoji = "🧑‍🚀";
    enemyEmoji = "👾";
    itemEmoji = "🎁";
    wallEmoji = "🧱";
    floorEmoji = "  ";
}

void Board::loadFromFile(const string& filename)
{
    map.clear();
    ifstream file(filename);
    string line;
    while (getline(file, line)) {
        if (!line.empty() && line.back() == '\r')
            line.pop_back();
        map.push_back(line);
    }
}

string Board::symbolToEmoji(char c) const
{
    switch (c) {
        case 'H': return heroEmoji;

        // Mapping
        // ennemis (races)
        case 'G': return "👺"; // Gobelin
        case 'N': return "🧌"; // Gnome
        case 'O': return "👹"; // Orc
        case 'S': return "💀"; // Squelette
        case 'E': return enemyEmoji; // fallback

        case 'I': return itemEmoji;
        case '#': return wallEmoji;
        case '.': return floorEmoji;
        default:  return "??";
    }
}

void Board::display() const
{
    for (const string& line : map) {
        for (char c : line)
            cout << symbolToEmoji(c);
        cout << endl;
    }
}

void Board::setHeroEmoji(const string& e)
{
    heroEmoji = e;
}

char Board::getCell(int x, int y) const
{
    if (!isInside(x, y)) return '#'; // detects out of bounds and caracter position 
    return map[y][x];
}

void Board::setCell(int x, int y, char c)
{
    if (!isInside(x, y)) return;
    map[y][x] = c; // modifies the character at position (x, y) to c
}

int Board::getWidth() const
{
    if (map.empty()) return 0;
    return map[0].size();
}

int Board::getHeight() const
{
    return map.size();
}

bool Board::isInside(int x, int y) const
{
    return y >= 0 && y < (int)map.size() && x >= 0 && x < (int)map[y].size();
}

void Board::findHero(int& x, int& y) const
{
    for (int j = 0; j < getHeight(); j++) {
        for (int i = 0; i < getWidth(); i++) {
            if (map[j][i] == 'H') {
                x = i;
                y = j;
                return;
            }
        }
    }
    x = 1;
    y = 1;
}

int Board::countEnemies() const
{
    int count = 0;
    for (const string& line : map)
        for (char c : line)
            if (c == 'E' || c == 'G' || c == 'N' || c == 'O' || c == 'S')
                count++;
    return count;
}
