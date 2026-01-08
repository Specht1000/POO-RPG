#include "Item.hpp"

Item::Item(ItemType type, int value)
{
    this->type = type;
    this->value = value;
    // defaults
    this->name = "Objet";
    this->price = 0;
}

Item::Item(string name, ItemType type, int value, int price)
{
    this->name = name;
    this->type = type;
    this->value = value;
    this->price = price;
}

ItemType Item::getType() const 
{ 
    return type; 
}

int Item::getValue() const 
{ 
    return value; 
}

string Item::getName() const 
{ 
    return name; 
}

int Item::getPrice() const 
{ 
    return price; 
}

string Item::getDescription() const
{
    if (type == BONUS_LIFE)
        return "❤️ " + name + " (+" + to_string(value) + " vie)";

    if (type == BONUS_DAMAGE)
        return "⚔️ " + name + " (+" + to_string(value) + " dégâts)";

    return "Objet inconnu";
}
