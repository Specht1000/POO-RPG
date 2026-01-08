#ifndef INVENTORY_HPP
#define INVENTORY_HPP

#include <vector>
#include <iostream>
#include "Item.hpp"

using namespace std;

class Inventory {
private:
    vector<Item> items;

public:
    void addItem(const Item& item);
    void show() const;
    int size() const;

    // helpers pour utiliser/retirer un objet par indice
    Item getItem(int index) const;
    void remove(int index);
};

#endif
