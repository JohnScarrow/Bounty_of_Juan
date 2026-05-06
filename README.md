# Bounty of Juan

A 2D top-down survivor-style shooter built in C++17 using the SFML graphics library. Survive waves of enemies as long as you can as Juan.

---

## Core Features

- **Infinite world** — tiling background that scrolls endlessly as Juan moves
- **Auto-shooting** — Juan automatically fires projectiles toward the nearest enemy
- **Enemy waves** — up to 5 enemies on screen at once; new ones spawn at the edges as others are killed
- **Health system** — Juan starts with 100 HP; enemies deal contact damage with a visual windup animation
- **Live HUD** — time survived, enemies killed, shots fired, and accuracy displayed during gameplay
- **Pause** — press ESC to freeze the game; press ESC again to resume
- **Results screen** — on death, shows final stats with an option to return to the main menu
- **Clean restart** — returning to the menu fully resets health, enemies, and stats

---

## How to Run

### Requirements
- g++ with C++17 support
- SFML 2.x development libraries

Install SFML on Ubuntu/Debian:
```
sudo apt install libsfml-dev
```

### Build & Run
```
make run
```

### Build Only
```
make game
```

### Clean Build Artifacts
```
make clean
```

The compiled executable is named `game`. All object files go into `objects/`.

---

## Design & Polymorphism

The game uses object-oriented design with a **Character base class** that provides shared health management for both Juan (player, 100 HP) and Enemy (ai, 3 HP). This enables:
- **Code reuse**: Health tracking, damage application, and death detection shared via inheritance
- **Polymorphism**: Both character types implement `getPosition() const` overrides, allowing future polymorphic collections or unified stat systems
- **Separation of concerns**: Combat logic in `Play::checkCollisions()` uses inherited methods (`takeDamage()`, `isDead()`) without caring about concrete types

---

## Controls

| Key | Action |
|-----|--------|
| W A S D | Move Juan |
| ESC | Pause / Unpause |

Juan shoots automatically toward the nearest enemy.

---

## Project Structure

```
source/      C++ implementation files
header/      Header files
assets/      Textures and fonts
objects/     Compiled object files (generated)
```

---

## Presentation Outline

### 1. Introduction
- 2D top-down survivor-style shooter
- Player is Juan — survive waves of enemies as long as possible
- Built in C++17 using the SFML graphics library
- Team of 4: John, Brayden, Tristan, Nathan

---

### 2. Live Demo
- Launch from welcome screen → click Play
- Show movement, auto-shooting, enemies chasing and attacking
- Take some damage to show health bar
- Press ESC to show pause overlay
- Die → show results screen with stats
- Click Main Menu → back to welcome, ready to play again

---

### 3. Architecture Overview
- **State machine** drives the whole game: `welcome → game → paused / results`
- `Game` class owns the state and delegates `handleInput`, `update`, `render` each frame
- `main.cpp` runs the loop, handles the infinite tiling background, and keeps the camera centered on Juan
- Assets (textures, fonts) loaded once in `main.cpp` and passed down by reference

```
main.cpp
  └── Game (state machine)
        ├── Welcome       (title screen)
        ├── Play          (gameplay — owns Juan + enemies)
        └── ResultsScreen (game over screen)
```

---

### 4. Contributors

#### Nathan — Project Skeleton & Core Engine
- Created the very first commit: project folder structure, Makefile, and all empty source/header files
- Built the core game loop in `main.cpp` including the SFML window, delta-time clock, and frame cycle
- Implemented the infinite tiling background system that seamlessly renders background tiles across world space
- Added the camera system in `main.cpp` that keeps the view centered on Juan as he moves
- Built out Juan's WASD movement with normalized diagonal movement so speed is consistent at all angles
- Constructed the `Game` state machine connecting `welcome`, `game`, `paused`, and `results` states
- Implemented the Welcome screen with the western-font title and wired it into the state machine

#### Brayden — Enemy System & Combat
- Built the `Enemy` class from scratch: texture loading, sprite scaling, and two constructors (one initializer, one for all subsequent enemies)
- Enemies use a shared static pointer to Juan and the window so all instances stay in sync without redundant references
- Enemy movement uses vector normalization (the same math as Juan's movement) to walk smoothly toward the player
- Enemies rotate to face Juan at all times using arc-sine angle calculation
- Implemented the full `Projectile` class and wired Juan to auto-shoot toward the nearest enemy every 15 frames
- Added collision detection between Juan's projectiles and enemy hitboxes (`checkCollisions` in `play.cpp`)
- Enemies have 3 HP and are removed from the heap when killed, with memory managed via pointer vector cleanup
- Integrated all enemies into `Play` with `initializeEnemyList`, `addEnemy`, `updateAllEnemies`, and `destroyEnemyList`
- **Update (Post-Sprint)**: Refactored `Enemy` to inherit from `Character` base class, eliminating duplicate health management code and enabling polymorphic character handling

#### Tristan — Button Class, Stats & HUD
- Added initial Juan stats structure to `juan.h` and `juan.cpp` (first stat tracking groundwork)
- Added Doxygen-style file headers and comments across all header files for documentation
- Implemented the full `Button` class with three visual states (normal, hovered, clicked), mouse hit detection, and color feedback
- Built the `Results` singleton stat tracker using a static instance pattern — tracks enemies spawned/killed, shots fired, shots missed, and time survived across the entire session
- Wired stat tracking calls into `juan.cpp` (shot fired/missed) and `play.cpp` (enemy spawned/killed, time update)
- Added the in-game HUD overlay that displays live time, enemies killed, shots fired, and accuracy in the top-left corner during gameplay

#### John — Screens, Health System & Polish
- Built the Welcome screen with the styled western-font title and Play button
- Built the Results screen showing final stats pulled from the tracker
- Added Juan's health system (100 HP), health bar, and the death → results transition
- Enemy contact damage with windup animation (scales to 110% before striking)
- ESC pause with a dimmed overlay and resume hint
- Restart resets health, clears enemies, and wipes stats for a clean new game
- Resolved merge conflicts across all branches throughout the project

---

### 5. Challenges & What We Learned
- Coordinating across 4 branches with overlapping files (`game.cpp`, `play.cpp`) required careful merging
- SFML's coordinate system is world-space, so enemy spawns had to account for Juan's position rather than raw screen dimensions
- Separating game logic (update) from rendering was important — shooting was accidentally tied to render, causing it to fire even while paused
