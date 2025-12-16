#include "Inventory.hpp"

void Inventory::addItem(const Item& item) {
    this->items.push_back(item);
}

void Inventory::show() const {
    cout << "Inventaire :" << endl;
    for (const Item& item : items) {
        cout << item.getDescription() << endl;
    }
}

int Inventory::size() const
{
    return items.size();
}