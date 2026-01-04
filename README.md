# 🧙 RPG Tour par Tour — Projet POO (C++)

Projet de jeu **RPG en terminal**, développé en **C++**, mettant en œuvre les principes de la **Programmation Orientée Objet (POO)**.  
Le jeu combine exploration de carte et combats **tour par tour inspirés des RPG classiques (style Pokémon)**.

---

## 🎮 Fonctionnalités

- 🗺️ Carte 2D chargée depuis des fichiers `.txt`
- 🔒 Carte fermée par des murs (impossible de sortir)
- 🧙 Déplacement du héros sur la carte
- 👹 Ennemis positionnés sur la carte
- 🎁 Objets récupérables
- ⚔️ Système de combat tour par tour
- 🔵 Gestion de mana (MP)
- 🔴 Trois types d’attaques :
  - **Attaque légère** : dégâts modérés, sans contrainte
  - **Attaque lourde** : dégâts élevés mais perte du tour suivant
  - **Magie** : dégâts élevés avec consommation de mana
- ⏳ Système de fatigue après attaque lourde
- 🧠 IA simple pour les ennemis
- 🎨 Affichage amélioré avec emojis en terminal
- 🧩 Architecture modulaire (`.hpp` / `.cpp`)

---

## 🧱 Architecture du projet

Projet/
├── Attack/  
├── Board/  
├── Dice/  
├── Enemy/  
├── Entity/  
├── Game/  
├── Input/  
├── Inventory/  
├── Item/  
├── Player/  
├── Main/  
├── Maps/    
├── obj/            (généré à la compilation)  
├── Makefile  
└── README.md  

---

## ⚙️ Compilation et exécution

### Prérequis
- Linux / WSL
- `g++` compatible C++17
- `make`

### Compiler et lancer le projet
```bash
make run
