# Bounty of Juan

A 2D top-down survivor-style shooter built in C++17 using the SFML graphics library. Survive waves of enemies as long as you can.

## Features

- **Infinite world** — tiling background scrolls endlessly as the player moves
- **Auto-shooting** — player fires automatically toward the nearest enemy
- **Enemy waves** — up to 5 enemies on screen; new ones spawn at random edges as others die
- **Health system** — 100 HP player, enemy contact damage with a visual windup animation
- **Live HUD** — time survived, enemies killed, shots fired, and accuracy updated each frame
- **Pause** — ESC freezes the game; ESC again resumes
- **Results screen** — on death, shows final stats with a return-to-menu option
- **Clean restart** — menu transition fully resets health, enemies, and stats

## Build & Run

Requires g++ (C++17) and SFML 2.x:

```bash
sudo apt install libsfml-dev   # Ubuntu/Debian
make                           # build and run
make game                      # build only
make clean
```

Always run from the project root — asset paths are relative.

## Architecture

A state machine drives the entire game loop:

```
main.cpp
  └── Game          — state machine; owns Play, delegates handleInput / update / render
        ├── Welcome — title screen and Play button
        ├── Play    — gameplay; owns Juan + vector<Enemy*>
        │     ├── Juan      — WASD movement, auto-shoot, projectile list
        │     └── Enemy     — vector-normalized movement toward player, arc-sine rotation
        └── Results — game-over screen; reads from Results singleton
```

`main.cpp` owns the `sf::RenderWindow` and delta-time clock. The camera tracks Juan via `window.setView`. Assets load once in `main.cpp` and pass down by reference.

**`Character` base class** provides shared health management (`takeDamage`, `isDead`, `getHP`) for both Juan (100 HP) and Enemy (3 HP). `Play::checkCollisions()` calls these without knowing the concrete type.

**`Enemy`** stores `static` pointers to Juan and the window set on the first constructor call, so all subsequent `Enemy()` instances share them without redundant parameters.

**`Results`** is a global singleton (`Results::instance()`) that accumulates enemies spawned/killed, shots fired/missed, and time survived — callable from anywhere, renders nothing itself.

## Controls

| Input | Action |
|---|---|
| W A S D | Move |
| ESC | Pause / Unpause |

Shooting is automatic.
