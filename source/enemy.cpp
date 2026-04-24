/**
 * @file enemy.cpp
 * @author Brayden Thompson
 * @brief Source for Enemy.h
 * @version 62.0.1.0.2
 * @date 2026-04-21
 *
 * @copyright Thompson Supreme Code™
 *
 */
#include "../header/enemy.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Window.hpp>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <vector>

/**
 * commented out shooting funcionality from this class and moved it to Juan.cpp
 * can be re-added if needed by uncommenting a few lines
 * 
 */

// initializing the window pointer before the constructor
sf::RenderWindow *Enemy::window = nullptr;
// initializing the Juan pointer before the constructor
Juan *Enemy::juan = nullptr;
// counter shared to keep track of all enemies
unsigned int Enemy::enemyCount = 0;
/**
 * @brief This is the inizialization contructor.
 * Needs an enemy with this constructor ran first before any other enemies are
 * created
 *
 * @param juan Pointer to the PC
 * @param window Pointer to the Window object
 */
Enemy::Enemy(Juan *juan, sf::RenderWindow *window) {
    this->window = window;
    this->juan = juan;
    enemyCount++;
    if (!enemyTexture.loadFromFile("assets/juan_texture.jpg")) {
        std::cerr << "Failed to load enemy texture!\n";
    }
    enemy.setTexture(enemyTexture);
    enemy.setOrigin(enemyTexture.getSize().x / 2.f,
                    enemyTexture.getSize().y / 2.f);
    enemy.scale(.125, .125);
    getRandomSpawn();
    enemy.setPosition(spawnLocation);
    speed = 100;
    attackTiming = 0;
    ;
}
/**
 * @brief General constructor for majority of the Enemy class
 *
 */
Enemy::Enemy() {

    if (!enemyTexture.loadFromFile("assets/juan_texture.jpg")) {
        std::cerr << "Failed to load enemy texture!\n";
    }
    enemy.setTexture(enemyTexture);
    enemy.setOrigin(enemyTexture.getSize().x / 2.f,
                    enemyTexture.getSize().y / 2.f);
    enemy.scale(.125, .125);
    speed = (rand() % 50) + 100;
    getRandomSpawn();
    enemy.setPosition(spawnLocation);
    enemyCount++;
}
/**
 * @brief Generates a random spawn point for the Enemies
 *
 */
void Enemy::getRandomSpawn() {
    switch ((rand() % 4) + 1) {
    case Top:
        spawnLocation.y = 0;
        spawnLocation.x = rand() % static_cast<int>(window->getSize().x);
        break;
    case Bottom:
        spawnLocation.y = window->getSize().y;
        spawnLocation.x = rand() % static_cast<int>(window->getSize().x);
        break;
    case Left:
        spawnLocation.x = 0;
        spawnLocation.y = rand() % static_cast<int>(window->getSize().y);
        break;
    case Right:
        spawnLocation.x = window->getSize().x;
        spawnLocation.y = rand() % static_cast<int>(window->getSize().y);
        break;
    }
}
/**
 * @brief sets the target member variable to the current position of the PC */
void Enemy::getPlayerPos() { this->target = juan->getPosition(); }
/**
 * @brief Generates a vector based on the last received position of the PC
 *
 */
void Enemy::setVector() {
    currentPosition = enemy.getPosition();
    vectorToPlayer.x = target.x - currentPosition.x;
    vectorToPlayer.y = target.y - currentPosition.y;

    // c^2 = a^2 + b^2
    // can be used for various things. I have used it to set the spacing an
    // enemy can approach to
    hypotenuse = std::sqrt((vectorToPlayer.x * vectorToPlayer.x) +
                           (vectorToPlayer.y * vectorToPlayer.y));
}
/**
 * @brief Uses code i stole from nathans Juan class
 * sets the vector and determines whether to move to the Juan or return early
 *
 *
 * @param elapsedTime
 */
void Enemy::moveEnemy(float elapsedTime) {

    // increase to increase the radius that the enemies go before stopping
    float gap = 150.f;
    if (hypotenuse <= gap) {
        return;
    }
    // Normalize: prevents moving faster diagonally
    float length = std::sqrt(vectorToPlayer.x * vectorToPlayer.x +
                             vectorToPlayer.y * vectorToPlayer.y);
    if (length != 0) {
        sf::Vector2f newVec = vectorToPlayer /=
            length; // Scale vector to length of 1
        enemy.move(newVec * (speed * elapsedTime));
    }
}

/**
 * @brief updates all player position data and vectors
 *
 * @param elapsedTime
 */
void Enemy::update(double elapsedTime) {
    if (this->window == nullptr) {
        std::cerr << "no window!\n";
        exit(1);
    }
    attackTiming += elapsedTime;

    getPlayerPos();
    setVector();
    rotateToPlayer();
    // updateAllProjectiles(elapsedTime);

    moveEnemy(elapsedTime);
}
// renders the enemy
void Enemy::render() {
    window->draw(enemy);
    /*
      attackTiming++;
      if (hypotenuse < 500 and attackTiming % 15 == 0) {
          shoot();
      }

      renderAllProjectiles();
      */
}

/**
 * @brief May remove. it just calculates the amount of rotation needed
 * for the enemy to facing at the character and rotates the enemy based on that
 *
 */
void Enemy::rotateToPlayer() {
    // take the vector and find the angle that the enemy needs to be rotated to
    // in order to face the player
    float rotationAdjustment{0}; // adjustment to the rotation for the specific
                                 // texture
                                 // arcsin(a*sin(C)/c) = A
                                 // need to check for cardinal directions
    currentRotation =
        std::asin(vectorToPlayer.x / hypotenuse) * (180 / 3.14) / 10;
    if (currentRotation < 0) {
        currentRotation = -1 * (currentRotation + currentRotation);
    }
    currentRotation += rotationAdjustment;
    enemy.setRotation(currentRotation);
}
/**
 * @brief iterates over the list of projectiles and calls the update() method on all of them
 * 
 * also will check the state of the projectiles and remove them if theyve gone 
 * far enough
 * @param elapsedTime 
 */
void Enemy::updateAllProjectiles(double elapsedTime) {
    std::vector<Projectile *> temp;
    for (Projectile *x : shootingList) {
        x->update(*window, elapsedTime);
    }
    for (auto x : shootingList) {
        if (x->shotState()) {
            temp.push_back(x);
        } else {
            delete x;
        }
    }

    shootingList = temp;
}


/**
 * @brief iterates over the vector of projectiles and 
 * calls the render method on them
 * 
 */
void Enemy::renderAllProjectiles() {
    for (Projectile *x : shootingList)
        x->render(*window);
}
/**
 * @brief creates a new Projectile object and pushes it to the vector
 * 
 */
void Enemy::shoot() {
    shootingList.push_back(new Projectile(currentPosition, target));
}
/**
 * @brief Destroy the Enemy:: Enemy object
 * ensures no memory leaks by freeing up all memory allocated to the shooting list
 * 
 */
Enemy::~Enemy() {
    for (auto x : shootingList) {
        delete x;
    }
}
