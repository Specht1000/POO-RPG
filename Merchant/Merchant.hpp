#ifndef MERCHANT_HPP
#define MERCHANT_HPP

#include <vector>
#include <iostream>
#include "Item.hpp"
#include "Inventory.hpp"

using namespace std;

class Merchant {
private:
    vector<Item> stock;

public:
    Merchant();

    void show() const;
    bool buy(int choice, int& playerGold, Inventory& playerInv);
};

#endif
