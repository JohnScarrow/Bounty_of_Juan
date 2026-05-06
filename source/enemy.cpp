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
    if (!enemyTexture.loadFromFile("assets/enemy_texture.jpg")) {
        std::cerr << "Failed to load enemy texture!\n";
    }
    enemy.setTexture(enemyTexture);
    enemy.setOrigin(enemyTexture.getSize().x / 2.f,
                    enemyTexture.getSize().y / 2.f);
    enemy.scale(.125, .125);
    getRandomSpawn();
    enemy.setPosition(spawnLocation);
    speed = 100;
    health = 3;
    attackTiming = 0;
    mDamageTimer = 0.f;
}
/**
 * @brief General constructor for majority of the Enemy class
 *
 */
Enemy::Enemy() {

    if (!enemyTexture.loadFromFile("assets/enemy_texture.jpg")) {
        std::cerr << "Failed to load enemy texture!\n";
    }
    enemy.setTexture(enemyTexture);
    enemy.setOrigin(enemyTexture.getSize().x / 2.f,
                    enemyTexture.getSize().y / 2.f);
    enemy.scale(.125, .125);
    speed = (rand() % 50) + 100;
    health = 3;
    attackTiming = 0;
    mDamageTimer = 0.f;
    getRandomSpawn();
    enemy.setPosition(spawnLocation);
    enemyCount++;
}
/**
 * @brief Generates a random spawn point for the Enemies
 *
 */
void Enemy::getRandomSpawn() {
    sf::Vector2f playerPos = juan->getPosition();
    int w = static_cast<int>(window->getSize().x);
    int h = static_cast<int>(window->getSize().y);

    switch ((rand() % 4) + 1) {
    case Top:
        spawnLocation.y = playerPos.y - h / 2.f;
        spawnLocation.x = playerPos.x - w / 2.f + rand() % w;
        break;
    case Bottom:
        spawnLocation.y = playerPos.y + h / 2.f;
        spawnLocation.x = playerPos.x - w / 2.f + rand() % w;
        break;
    case Left:
        spawnLocation.x = playerPos.x - w / 2.f;
        spawnLocation.y = playerPos.y - h / 2.f + rand() % h;
        break;
    case Right:
        spawnLocation.x = playerPos.x + w / 2.f;
        spawnLocation.y = playerPos.y - h / 2.f + rand() % h;
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
    float gap = 35.f;
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

    // Deal contact damage to Juan once per second when in range
    if (hypotenuse <= 40.f) {
        mDamageTimer += elapsedTime;
        if (mDamageTimer >= 1.0f) {
            juan->takeDamage(10);
            mDamageTimer = 0.f;
        }
    } else {
        mDamageTimer = 0.f;
    }

    // Scale up during windup, back to normal otherwise
    if (hypotenuse <= 40.f && mDamageTimer > 0.6f)
        enemy.setScale(0.1375f, 0.1375f);
    else
        enemy.setScale(0.125f, 0.125f);
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
    sf::Vector2f direction = target - enemy.getPosition();
    float angle = std::atan2(direction.y, direction.x) * 180.f / 3.14159265f;
    enemy.setRotation(angle + 270.f);
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

void Enemy::takeDamage(int dmg) { health -= dmg; }
bool Enemy::isDead() const { return health <= 0; }
sf::FloatRect Enemy::getGlobalBounds() const { return enemy.getGlobalBounds(); }
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
