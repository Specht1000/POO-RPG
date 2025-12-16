#include "Item.hpp"

Item::Item(ItemType type, int value)
{
    this->type = type;
    this->value = value;
}

ItemType Item::getType() const
{
    return type;
}

int Item::getValue() const
{
    return value;
}

string Item::getDescription() const
{
    if (type == BONUS_LIFE)
        return "Bonus de vie +" + to_string(value);

    if (type == BONUS_DAMAGE)
        return "Bonus de dégâts +" + to_string(value);

    return "Objet inconnu";
}
