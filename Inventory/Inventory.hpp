#ifndef INVENTORY_HPP
#define INVENTORY_HPP

#include <vector>
#include <iostream>

using namespace std;

#include "Item.hpp"

class Inventory {
private:
    vector<Item> items;

public:
    void addItem(const Item& item);
    void show() const;
    int size() const;
};

#endif
