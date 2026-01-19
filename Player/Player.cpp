#include "Player.hpp"

using namespace std;

Player::Player()
    : Entity("", 0)
{
    this->name = "Heros";
    this->life = 100;
    this->luck = 5;
    this->gold = 0;
    this->x = 0;
    this->y = 0;
    this->mana = 50;
    skipNextTurn = false;

    attacks.clear();
    attacks.push_back(Attack("Attaque légère", 10, 0, LIGHT));
    attacks.push_back(Attack("Attaque lourde", 25, 0, HEAVY));
    attacks.push_back(Attack("Sort magique", 35, 15, MAGIC));
}

bool Player::useLuck() {
    int roll = Dice::roll(6);
    return roll <= this->luck;
}

Inventory& Player::getInventory() {
    return this->inventory;
}

void Player::setPosition(int x, int y)
{
    this->x = x;
    this->y = y;
}

int Player::getX() const
{
    return this->x;
}

int Player::getY() const
{
    return this->y;
}

int Player::getLife() const
{
    return this->life;
}

void Player::takeDamage(int dmg)
{
    this->life -= dmg;
    if (this->life < 0)
        this->life = 0;
}

bool Player::isAlive() const
{
    return this->life > 0;
}

void Player::showAttacks() const
{
    for (size_t i = 0; i < attacks.size(); i++) {
        cout << i + 1 << ". " << attacks[i].getName()
             << " (dégâts: " << attacks[i].getDamage() << ")" << endl;
    }
}

Attack Player::chooseAttack(int index)
{
    if (attacks.empty()) {
        // sécurité absolue
        return Attack("Attaque nulle", 0, 0, LIGHT);
    }

    if (index < 0 || index >= (int)attacks.size()) {
        return attacks[0];
    }

    return attacks[index];
}

void Player::heal(int amount)
{
    this->life += amount;
    if (this->life > 150)   // limite max
        this->life = 150;
}

void Player::boostDamage(int amount)
{
    for (Attack& atk : attacks) {
        atk = Attack(
            atk.getName(),
            atk.getDamage() + amount,
            atk.getManaCost(),
            atk.getType()
        );

    }
}

int Player::getMana() const
{
    return mana;
}

bool Player::useMana(int cost)
{
    if (mana < cost)
        return false;
    mana -= cost;
    return true;
}

bool Player::mustSkipTurn() const
{
    return skipNextTurn;
}

void Player::setSkipTurn(bool value)
{
    skipNextTurn = value;
}

string Player::getClassName() const
{
    return className;
}

void Player::applyClass(int choice)
{
    // default
    className = "Chevalier";

    // base stats (vai ser sobrescrito no switch)
    life = 100;
    luck = 5;
    mana = 50;
    skipNextTurn = false;

    attacks.clear();

    // 1 Chevalier, 2 Sorcier, 3 Archer, 4 Voleur
    switch (choice) {
    case 1: // 🛡️ Chevalier
        className = "Chevalier";
        emoji = "🛡️";
        life = 130;
        luck = 4;
        mana = 25;

        attacks.push_back(Attack("Coup léger", 12, 0, LIGHT));
        attacks.push_back(Attack("Coup lourd", 32, 0, HEAVY));
        attacks.push_back(Attack("Coup sacré", 22, 10, MAGIC));
        break;

    case 2: // 🔮 Sorcier
        className = "Sorcier";
        emoji = "🧙‍♂️";
        life = 90;
        luck = 6;
        mana = 90;

        attacks.push_back(Attack("Bâton", 9, 0, LIGHT));
        attacks.push_back(Attack("Incantation", 18, 0, HEAVY));
        attacks.push_back(Attack("Boule de feu", 45, 20, MAGIC));
        break;

    case 3: // 🏹 Archer
        className = "Archer";
        emoji = "🏹";
        life = 105;
        luck = 6;
        mana = 35;

        attacks.push_back(Attack("Flèche rapide", 11, 0, LIGHT));
        attacks.push_back(Attack("Tir chargé", 28, 0, HEAVY));
        attacks.push_back(Attack("Flèche élémentaire", 26, 12, MAGIC));
        break;

    case 4: // 🗡️ Voleur
        className = "Voleur";
        emoji = "🗡️";
        life = 95;
        luck = 10;
        mana = 30;

        attacks.push_back(Attack("Coup furtif", 10, 0, LIGHT));
        attacks.push_back(Attack("Backstab", 26, 0, HEAVY));
        attacks.push_back(Attack("Poison", 20, 10, MAGIC));
        break;

    default:
        // se input errado, mantém Chevalier
        className = "Chevalier";
        life = 130;
        luck = 4;
        mana = 25;

        attacks.push_back(Attack("Coup léger", 12, 0, LIGHT));
        attacks.push_back(Attack("Coup lourd", 32, 0, HEAVY));
        attacks.push_back(Attack("Coup sacré", 22, 10, MAGIC));
        break;
    }
}

string Player::getEmoji() const { return emoji; }

void Player::useItem(int index)
{
    if (index < 0 || index >= inventory.size()) {
        cout << "Objet invalide.\n";
        return;
    }

    Item it = inventory.getItem(index);

    if (it.getType() == BONUS_LIFE) {
        life += it.getValue();
        cout << "Vie augmentée de +" << it.getValue() << " !\n";
    }
    else if (it.getType() == BONUS_DAMAGE) {
        boostDamage(it.getValue());
        cout << "Dégâts augmentés de +" << it.getValue() << " !\n";
    }

    inventory.remove(index);
}

int Player::getGold() const
{
    return gold;
}

void Player::addGold(int amount)
{
    gold += amount;
    if (gold < 0) gold = 0;
}

void Player::useItemFromInventory(int index)
{
    // index esperado: 0..size-1
    if (index < 0 || index >= inventory.size()) {
        cout << "Indice invalide." << endl;
        return;
    }

    Item it = inventory.getItem(index);

    cout << "Vous utilisez: " << it.getName()
         << " -> " << it.getDescription() << endl;

    // Aplica efeito
    if (it.getType() == BONUS_LIFE) {
        life += it.getValue();
        cout << "HP + " << it.getValue() << endl;
    }
    else if (it.getType() == BONUS_DAMAGE) {
        boostDamage(it.getValue());
        cout << "Dégâts + " << it.getValue() << endl;
    }

    // remove do inventário
    inventory.remove(index);
}

int& Player::goldRef()
{
    return gold;
}

void Player::addItemToInventory(const Item& it)
{
    inventory.addItem(it);
}

int Player::getLuck() const
{
    return luck;
}
