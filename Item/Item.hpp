#ifndef ITEM_HPP
#define ITEM_HPP

#include <string>
using namespace std;

enum ItemType {
    BONUS_LIFE,
    BONUS_DAMAGE
};

class Item {
private:
    ItemType type;
    int value;

    string name;
    int price;

public:
    Item(ItemType type, int value);

    Item(string name, ItemType type, int value, int price);

    ItemType getType() const;
    int getValue() const;

    string getName() const;
    int getPrice() const;

    string getDescription() const;
};

#endif
