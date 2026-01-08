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

    // ✅ novo (para marchand)
    string name;
    int price;

public:
    // ✅ mantém compatibilidade com teu código atual
    Item(ItemType type, int value);

    // ✅ novo: item com nome + preço (para loja)
    Item(string name, ItemType type, int value, int price);

    ItemType getType() const;
    int getValue() const;

    // ✅ novo
    string getName() const;
    int getPrice() const;

    string getDescription() const;
};

#endif
