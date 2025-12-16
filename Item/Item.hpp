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

public:
    Item(ItemType type, int value);

    ItemType getType() const;
    int getValue() const;
    string getDescription() const;
};

#endif
