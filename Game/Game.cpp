#include "Game.hpp"

Game::Game()
{
    srand(time(nullptr)); // RNG start
    justInteracted = false;
    loadMap("Maps/Map3.txt");

    int hx, hy;
    board.findHero(hx, hy);
    player.setPosition(hx, hy);
}

void Game::loadMap(const string& filename)
{
    board.loadFromFile(filename);

    int hx, hy;
    board.findHero(hx, hy);
    player.setPosition(hx, hy);
}

void Game::run()
{
    chooseClass();
    loop();
}

void Game::loop()
{
    while (player.isAlive()) {
        system("clear");

        board.display();
        cout << "\n";
        cout << "Classe: " << player.getClassName()
             << " | HP: " << player.getLife()
             << " | MP: " << player.getMana()
             << " | Or: " << player.getGold()
             << " | Ennemis restants: " << board.countEnemies()
             << "\n";

        doTurnMenu();

        if (!player.isAlive()) {
            showGameOver();
            return;
        }
    }
}

void Game::doTurnMenu()
{
    cout << "\n=== TOUR ===\n";
    cout << "1. Se déplacer (dé)\n";
    cout << "2. Inventaire (utiliser un objet)\n";
    cout << "3. Marchand\n";
    cout << "4. Quitter\n";
    cout << "Choix: ";

    int choice;
    cin >> choice;

    if (choice == 1) {
        moveWithDice();
    } else if (choice == 2) {
        useItemMenu();
    } else if (choice == 3) {
        openMerchant();
    } else if (choice == 4) {
        exit(0);
    }
}

void Game::moveWithDice()
{
    int steps = Dice::roll(6);
    cout << "\nDé = " << steps << " cases.\n";
    cout << "Utilisez WASD pour bouger (" << steps << " mouvements).\n";
    cout << "(Appuyez sur une touche puis ENTER)\n";
    cin.ignore();

    for (int i = 0; i < steps; i++) {
        system("clear");
        board.display();
        cout << "\nHP: " << player.getLife()
             << " | MP: " << player.getMana()
             << " | Or: " << player.getGold()
             << " | Steps restants: " << (steps - i)
             << "\n";

        char c;
        cin >> c;

        int dx = 0, dy = 0;
        if (c == 'w') dy = -1;
        else if (c == 's') dy = 1;
        else if (c == 'a') dx = -1;
        else if (c == 'd') dx = 1;
        else {
            cout << "Touche invalide.\n";
            i--;
            continue;
        }

        bool moved = movePlayer(dx, dy);
        if (!moved) i--;
        if (!player.isAlive()) return;
    }
}

void Game::useItemMenu()
{
    system("clear");
    Inventory& inv = player.getInventory();

    if (inv.size() == 0) {
        cout << "Inventaire vide.\n";
        cin.ignore();
        cin.get();
        return;
    }

    inv.show();
    cout << "\nQuel objet utiliser ? (0 annuler)\nChoix: ";
    int idx;
    cin >> idx;

    if (idx == 0) return;
    player.useItem(idx - 1);

    cin.ignore();
    cin.get();
}

void Game::openMerchant()
{
    while (true) {
        system("clear");
        cout << "Or: " << player.getGold() << "\n\n";
        merchant.show();
        cout << "Choix: ";

        int choice;
        cin >> choice;

        if (choice == 0) break;

        merchant.buy(choice, player.goldRef(), player.getInventory());
        cin.ignore();
        cin.get();
    }
}

Item Game::generateRandomItem()
{
    int r = rand() % 2;
    if (r == 0) {
        int v = 10 + (rand() % 21);
        return Item("Potion trouvée", BONUS_LIFE, v, 0);
    } else {
        int v = 1 + (rand() % 5);
        return Item("Rune trouvée", BONUS_DAMAGE, v, 0);
    }
}

bool Game::movePlayer(int dx, int dy)
{
    int nx = player.getX() + dx;
    int ny = player.getY() + dy;

    if (!board.isInside(nx, ny))
        return false;

    char cell = board.getCell(nx, ny);

    if (cell == '#')
        return false;

    if (cell == 'E' || cell == 'G' || cell == 'N' || cell == 'O' || cell == 'S') {
        string race = "Gobelin";
        if (cell == 'G') race = "Gobelin";
        else if (cell == 'N') race = "Gnome";
        else if (cell == 'O') race = "Orc";
        else if (cell == 'S') race = "Squelette";

        Enemy enemy(race);
        combat(enemy);

        if (!player.isAlive())
            return false;

        if (enemy.isAlive()) {
            cout << "L'ennemi reste sur place...\n";
            cin.ignore();
            cin.get();
            return false;
        }

        board.setCell(nx, ny, '.');
        player.addGold(enemy.getReward());
        checkEndGame();
    }

    board.setCell(player.getX(), player.getY(), '.');
    player.setPosition(nx, ny);
    board.setCell(nx, ny, 'H');

    // item
    if (cell == 'I') {
        Item it = generateRandomItem();
        cout << "Objet trouvé: " << it.getName()
             << " -> " << it.getDescription() << "\n";
        player.getInventory().addItem(it);
        cin.ignore();
        cin.get();
    }

    return true;
}

void Game::combat(Enemy& enemy)
{
    bool skipPlayerNextTurn = false;

    while (player.isAlive() && enemy.isAlive()) {
        system("clear");

        cout << "=== COMBAT ===\n";
        cout << player.getEmoji() << " " << player.getClassName()
             << " | HP: " << player.getLife()
             << " | MP: " << player.getMana()
             << " | Or: " << player.getGold() << "\n";
        cout << "Ennemi: " << enemy.getRace()
             << " | HP: " << enemy.getLife() << "\n\n";

        cout << "Que voulez-vous faire ?\n";
        cout << "1. Attaquer\n";
        cout << "2. Utiliser objet\n";
        cout << "3. Fuite\n";
        cout << "Choix: ";

        int menu;
        cin >> menu;

        if (menu == 3) {
            cout << "Vous prenez la fuite !\n";
            cin.ignore();
            cin.get();
            return;
        }

        if (menu == 2) {
            player.getInventory().show();
            cout << "\nChoix objet (0 annuler): ";
            int idx;
            cin >> idx;
            if (idx > 0) player.useItem(idx - 1);
        }

        if (menu == 1) {
            if (skipPlayerNextTurn) {
                cout << "Vous êtes fatigué: vous sautez ce tour !\n";
                skipPlayerNextTurn = false;
            } else {
                cout << "\nChoisissez une attaque:\n";
                cout << "1. Légère (dmg moyen)\n";
                cout << "2. Lourde (gros dmg, tour suivant: KO)\n";
                cout << "3. Magie (consomme MP)\n";
                cout << "Choix: ";

                int atkChoice;
                cin >> atkChoice;

                Attack atk = player.chooseAttack(atkChoice - 1);

                if (atk.getType() == MAGIC) {
                    if (!player.useMana(atk.getManaCost())) {
                        cout << "Pas assez de mana !\n";
                        cin.ignore();
                        cin.get();
                        continue;
                    }
                }

                if (atk.getType() == HEAVY) {
                    skipPlayerNextTurn = true;
                }

                int bonus = 0;
                if (rand() % 100 < player.getLuck() * 5) bonus = 3 + rand() % 6;

                enemy.takeDamage(atk.getDamage() + bonus);
                cout << "Vous utilisez " << atk.getName();
                if (bonus > 0) cout << " (Chance +" << bonus << ")";
                cout << " !\n";
            }
        }

        if (!enemy.isAlive())
            break;

        Attack enemyAtk = enemy.randomAttack();
        player.takeDamage(enemyAtk.getDamage());
        cout << "L'ennemi attaque: " << enemyAtk.getName()
             << " (-" << enemyAtk.getDamage() << ")\n";

        cin.ignore();
        cin.get();
    }
}

void Game::checkEndGame()
{
    if (board.countEnemies() == 0) {
        showVictory();
        exit(0);
    }
}

void Game::showVictory()
{
    system("clear");
    cout << "🎉 VICTOIRE ! Tous les ennemis sont vaincus.\n\n";
    cout << "=== Stats du héros ===\n";
    cout << "- Classe : " << player.getClassName() << endl;
    cout << "- Vie restante : " << player.getLife() << endl;
    cout << "- Mana restante : " << player.getMana() << endl;
    cout << "- Or : " << player.getGold() << endl;
    cout << "- Objets en inventaire : " << player.getInventory().size() << endl;
    cout << "\n";
}

void Game::showGameOver()
{
    system("clear");
    cout << "💀 GAME OVER\n";
    cout << "Vous êtes mort...\n";
    cout << "Classe: " << player.getClassName() << "\n";
    cout << "Or: " << player.getGold() << "\n";
    cout << "Objets: " << player.getInventory().size() << "\n";
    cout << endl;
}

void Game::chooseClass()
{
    system("clear");
    cout << "=== Création du personnage ===\n";
    cout << "Choisissez une classe:\n";
    cout << "1. Chevalier 🛡️ (HP haut, Force)\n";
    cout << "2. Sorcier 🧙 (MP haut, Magie)\n";
    cout << "3. Archer 🏹 (Dex, critiques)\n";
    cout << "4. Voleur 🗡️ (Dex/Luck)\n";

    int choice = 0;

    while (true) {
        cout << "Choix: ";
        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Entrée invalide.\n";
            continue;
        }

        if (choice >= 1 && choice <= 4) break;

        cout << "Choix invalide.\n";
    }

    player.applyClass(choice);

    board.setHeroEmoji(player.getEmoji());

    cout << "\nClasse choisie: " << player.getClassName() << " " << player.getEmoji() << "\n";
    cout << "HP: " << player.getLife()
         << " | MP: " << player.getMana()
         << " | Force: " << player.getStrength()
         << " | Dex: " << player.getDexterity()
         << " | Luck: " << player.getLuck() << "\n";

    cout << "\nAppuyez sur ENTER...\n";
    cin.ignore();
    cin.get();
}
