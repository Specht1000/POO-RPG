# 🧙 RPG Tour par Tour — Projet POO (C++)

Projet de **jeu de rôle (RPG) en terminal**, développé en **C++**, respectant strictement les consignes du **projet de Programmation Orientée Objet et Modélisation**.  
Le jeu repose sur une **carte 2D**, des **déplacements au dé**, des **combats tour par tour**, un **système de classes**, d’ennemis par **race**, d’objets, d’or et de marchand.

---

## 🎯 Objectif du jeu

- Explorer une carte fermée
- Affronter tous les ennemis présents
- Gérer ses statistiques (vie, mana, force, dextérité, chance)
- Collecter des objets et de l’or
- Vaincre **tous les ennemis** pour gagner la partie

---

## 🧑‍🎓 Conformité au sujet du PDF

✔️ Plateau de jeu sous forme de carte  
✔️ Personnage créé au début via le choix d’une **classe**  
✔️ Caractéristiques dépendantes de la classe  
✔️ Ennemis avec caractéristiques selon leur **race**  
✔️ Déplacements via **lancer de dé**  
✔️ Interactions case par case  
✔️ Combat tour par tour  
✔️ Système de chance influençant les dégâts  
✔️ Gain d’or après un combat  
✔️ Marchand accessible hors combat  
✔️ Inventaire et objets améliorant les stats  

---

## 🧙 Classes jouables

Lors du lancement du jeu, le joueur choisit une classe :

- 🛡️ **Chevalier**  
  - Vie élevée  
  - Force importante  
  - Mana faible  

- 🧙 **Sorcier**  
  - Mana élevé  
  - Attaques magiques puissantes  
  - Vie plus faible  

- 🏹 **Archer**  
  - Dextérité élevée  
  - Bon compromis dégâts / critiques  

- 🗡️ **Voleur**  
  - Chance élevée  
  - Esquive et bonus aléatoires fréquents  

Chaque classe définit :
- Vie (HP)
- Mana (MP)
- Force
- Dextérité
- Chance
- Emoji du héros

---

## 👹 Ennemis (races)

Les ennemis sont définis par leur **race**, chacune ayant ses propres stats, attaques et emoji :

- 👺 **Gobelin**
- 🧌 **Gnome**
- 👹 **Orc**
- 💀 **Squelette**

Chaque ennemi possède :
- Vie
- Force
- Attaques propres
- Récompense en or

---

## ⚔️ Système de combat (tour par tour)

Combat déclenché lorsqu’un ennemi est rencontré sur la carte.

### Actions possibles :
1. Attaquer
2. Utiliser un objet
3. Fuir

### Types d’attaques :
- **Attaque légère**
  - Dégâts moyens
  - Aucun effet secondaire

- **Attaque lourde**
  - Dégâts élevés
  - Le joueur **perd son tour suivant** (fatigue)

- **Magie**
  - Dégâts élevés
  - Consomme du mana (MP)

🎲 La **chance** peut ajouter un bonus de dégâts aléatoire.

---

## 🎒 Objets & inventaire

- Objets trouvés aléatoirement sur la carte
- Stockés dans un **inventaire**
- Utilisables en combat ou hors combat

Types d’objets :
- ❤️ Bonus de vie
- ⚔️ Bonus de dégâts

---

## 🧑‍💼 Marchand

- Accessible à tout moment **hors combat**
- Achat d’objets contre de l’or
- Stock géré indépendamment du joueur

---

## 🗺️ Carte & affichage

- Cartes chargées depuis des fichiers `.txt`
- Carte fermée par des murs
- Affichage terminal avec **emojis**
- Symboles internes → emojis à l’affichage

Exemples :
- `H` → héros 🧑‍🚀 (selon la classe)
- `G` → Gobelin 👺
- `#` → mur 🧱
- `.` → sol
- `I` → objet 🎁

---

## 🏆 Conditions de fin

- 🎉 **Victoire** : tous les ennemis de la carte sont éliminés
- 💀 **Défaite** : la vie du héros tombe à 0

Affichage des statistiques finales :
- Classe
- Vie restante
- Mana restante
- Or collecté
- Nombre d’objets

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

✔️ Séparation claire `.hpp / .cpp`  
✔️ Respect de l’encapsulation  
✔️ Héritage (`Player`, `Enemy` ← `Entity`)  
✔️ Code modulaire et extensible  

---

## ⚙️ Compilation et exécution

### Prérequis
- Linux ou WSL
- `g++` (C++17)
- `make`

### Compiler et lancer
```bash
make run
