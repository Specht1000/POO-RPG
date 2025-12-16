#include "Game.hpp"
#include "Input.hpp"
#include "Enemy.hpp"
#include <iostream>
#include <cstdlib>

using namespace std;

Game::Game()
{
    loadMap("Maps/Map3.txt");
}

void Game::loadMap(const string& filename)
{
    board.loadFromFile(filename);

    int hx, hy;
    board.findHero(hx, hy);
    player = Player("Heros");
    player.setPosition(hx, hy);
}

void Game::run()
{
    Input::init();
    loop();
    Input::restore();
}

void Game::loop()
{
    char key;
    bool running = true;

    while (running) {
        system("clear");
        cout << "Vie du héros : " << player.getLife() << endl;
        board.display();

        key = Input::getKey();

        switch (key) {
        case 'w': movePlayer(0, -1); break;
        case 's': movePlayer(0, 1);  break;
        case 'a': movePlayer(-1, 0); break;
        case 'd': movePlayer(1, 0);  break;
        case 'q': running = false;   break;
        }
    }
}

void Game::movePlayer(int dx, int dy)
{
    int newX = player.getX() + dx;
    int newY = player.getY() + dy;

    if (!board.isInside(newX, newY)) {
        return;
    }

    char target = board.getCell(newX, newY);

    if (target == '#') return;

    if (target == 'I') {
        Item item = generateRandomItem();

        cout << "Objet trouvé : " << item.getDescription() << endl;

        if (item.getType() == BONUS_LIFE) {
            player.heal(item.getValue());
        }
        else if (item.getType() == BONUS_DAMAGE) {
            player.boostDamage(item.getValue());
        }

        cout << "Bonus appliqué !" << endl;
        cin.ignore();
        cin.get();
    }

    if (target == 'E') {
        Input::restore();

        Enemy enemy("Gobelin");
        combat(enemy);

        if (!player.isAlive()) {
            showGameOver();
            exit(0);
        }

        // inimigo derrotado → remove do mapa
        board.setCell(newX, newY, '.');

        Input::init();
    }

    board.setCell(player.getX(), player.getY(), '.');
    player.setPosition(newX, newY);
    board.setCell(newX, newY, 'H');
    checkEndGame();
}

void Game::combat(Enemy& enemy)
{
    bool fighting = true;

    while (player.isAlive() && enemy.isAlive() && fighting) {
        system("clear");

        cout << "=== COMBAT ===\n";
        cout << "Héros HP: " << player.getLife()
             << " | MP: " << player.getMana() << endl;
        cout << "Ennemi HP: " << enemy.getLife() << "\n\n";

        cout << "Que voulez-vous faire ?\n";
        cout << "1. Attaquer\n";
        cout << "2. Fuite\n";
        cout << "Choix: ";

        int menu;
        cin >> menu;

        if (menu == 2) {
            cout << "Vous prenez la fuite !\n";
            cin.ignore();
            cin.get();
            return;
        }

        // --- Attaques ---
        cout << "\nChoisissez une attaque:\n";
        cout << "1. Légère (10 dmg)\n";
        cout << "2. Lourde (25 dmg)\n";
        cout << "3. Magie (35 dmg / 15 MP)\n";
        cout << "Choix: ";

        int atkChoice;
        cin >> atkChoice;

        Attack atk = player.chooseAttack(atkChoice - 1);

        // mana check
        if (atk.getType() == MAGIC) {
            if (!player.useMana(atk.getManaCost())) {
                cout << "Pas assez de mana !\n";
                cin.ignore();
                cin.get();
                continue;
            }
        }

        // heavy attack chance
        if (atk.getType() == HEAVY && rand() % 100 < 30) {
            cout << "L'attaque lourde échoue !\n";
        } else {
            enemy.takeDamage(atk.getDamage());
            cout << "Vous utilisez " << atk.getName() << " !\n";
        }

        if (!enemy.isAlive())
            break;

        // Enemy turn
        Attack enemyAtk = enemy.randomAttack();
        player.takeDamage(enemyAtk.getDamage());
        cout << "L'ennemi attaque !\n";

        cin.ignore();
        cin.get();
    }
}

Item Game::generateRandomItem()
{
    int r = rand() % 2;

    if (r == 0)
        return Item(BONUS_LIFE, 20 + rand() % 20);   // +20 à +40 HP

    return Item(BONUS_DAMAGE, 5 + rand() % 6);      // +5 à +10 dégâts
}

void Game::checkEndGame()
{
    if (board.countEnemies() == 0) {
        Input::restore();
        showVictory();
        exit(0);
    }
}

void Game::showVictory()
{
    system("clear");
    cout << "==============================" << endl;
    cout << "        VICTOIRE ! 🏆          " << endl;
    cout << "==============================" << endl;

    cout << "Stats du héros :" << endl;
    cout << "- Vie restante : " << player.getLife() << endl;
    cout << "- Or collecté : " << player.getInventory().size() << endl;
    cout << "- Attaques :" << endl;

    player.showAttacks();

    cout << "\nTous les ennemis ont été vaincus !" << endl;
    cout << "\nMerci d'avoir joué." << endl;
}

void Game::showGameOver()
{
    system("clear");
    cout << "==============================" << endl;
    cout << "         GAME OVER 💀          " << endl;
    cout << "==============================" << endl;

    cout << "Le héros est tombé au combat." << endl;
    cout << "Fin de l'aventure." << endl;
}
