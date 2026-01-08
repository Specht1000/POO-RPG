#include "Merchant.hpp"

Merchant::Merchant()
{
    stock.push_back(Item("Petite potion", BONUS_LIFE, 20, 10));
    stock.push_back(Item("Grande potion", BONUS_LIFE, 40, 25));
    stock.push_back(Item("Pierre de force", BONUS_DAMAGE, 3, 20));
    stock.push_back(Item("Pierre de puissance", BONUS_DAMAGE, 5, 35));
}

void Merchant::show() const
{
    cout << "=== Marchand ===" << endl;
    for (int i = 0; i < (int)stock.size(); i++) {
        cout << i + 1 << ". " << stock[i].getName()
             << " (" << stock[i].getDescription()
             << ") - " << stock[i].getPrice() << " or" << endl;
    }
    cout << "0. Quitter" << endl;
}

bool Merchant::buy(int choice, int& playerGold, Inventory& playerInv)
{
    if (choice <= 0 || choice > (int)stock.size())
        return false;

    Item it = stock[choice - 1];

    if (playerGold < it.getPrice()) {
        cout << "Pas assez d'or !" << endl;
        return false;
    }

    playerGold -= it.getPrice();
    playerInv.addItem(it);
    cout << "Achat réussi: " << it.getName() << endl;
    return true;
}
