#include "Inventory.hpp"

void Inventory::addItem(const Item& item)
{
    items.push_back(item);
}

void Inventory::show() const
{
    if (items.empty()) {
        cout << "Inventaire vide." << endl;
        return;
    }

    cout << "=== Inventaire ===" << endl;
    for (int i = 0; i < (int)items.size(); i++) {
        cout << i + 1 << ". " << items[i].getName()
             << " (" << items[i].getDescription() << ")" << endl;
    }
}

int Inventory::size() const
{
    return items.size();
}

Item Inventory::getItem(int index) const
{
    if (index < 0 || index >= (int)items.size())
        return Item(BONUS_LIFE, 0);
    return items[index];
}

void Inventory::remove(int index)
{
    if (index < 0 || index >= (int)items.size())
        return;
    items.erase(items.begin() + index);
}
