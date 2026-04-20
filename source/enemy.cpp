#include "../header/enemy.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Window.hpp>
#include <cmath>
#include <cstdlib>
#include <iostream>

sf::RenderWindow *Enemy::window = nullptr;
Juan *Enemy::juan = nullptr;
unsigned int Enemy::enemyCount = 0;
Enemy::Enemy(Juan *juan, sf::RenderWindow *window) {
    this->window = window;
    this->juan = juan;
    enemyCount++;
    if (!enemyTexture.loadFromFile("")) {
        std::cerr << "Failed to load enemy texture!\n";
    }
    enemy.setTexture(enemyTexture);
    enemy.setOrigin(enemyTexture.getSize().x / 2.f,
                    enemyTexture.getSize().y / 2.f);
    getRandomSpawn();
}
Enemy::Enemy() {}

void Enemy::getRandomSpawn() {
    switch ((rand() % 4) + 1) {
    case Top:
        spawnLocation.y = 0;
        spawnLocation.x = rand() % static_cast<int>(window->getSize().x);
        currentRotation = 0;
        break;
    case Bottom:
        spawnLocation.y = window->getSize().y;
        spawnLocation.x = rand() % static_cast<int>(window->getSize().x);
        currentRotation = 180;
        break;
    case Left:
        spawnLocation.x = 0;
        spawnLocation.y = rand() % static_cast<int>(window->getSize().y);
        currentRotation = 90;
        break;
    case Right:
        spawnLocation.x = window->getSize().x;
        spawnLocation.y = rand() % static_cast<int>(window->getSize().y);
        currentRotation = 270;
        break;
    }
    enemy.setPosition(spawnLocation);
    enemy.setRotation(currentRotation);
}
void Enemy::getPlayerPos() { this->target = juan->getPosition(); }
void Enemy::setVector() {
    vectorToPlayer.x = currentPosition.x - target.x;
    vectorToPlayer.y = currentPosition.y - target.y;

    // c^2 = a^2 + b^2
    hypotenuse = std::sqrt((vectorToPlayer.x * vectorToPlayer.x) +
                           (vectorToPlayer.y * vectorToPlayer.y));
}
void Enemy::moveEnemy() { // Normalize: prevents moving faster diagonally
    setVector();
    rotateToPlayer();
    float length = std::sqrt(vectorToPlayer.x * vectorToPlayer.x +
                             vectorToPlayer.y * vectorToPlayer.y);
    if (length != 0) {
        vectorToPlayer /= length; // Scale vector to length of 1
        enemy.move(vectorToPlayer * speed);
    }
}
void Enemy::update(double elapsedTime) {
    getPlayerPos();
    setVector();
    rotateToPlayer();
    moveEnemy();
}
void Enemy::render() { window->draw(enemy); }
void Enemy::rotateToPlayer() {
    // take the vector and find the angle that the enemy needs to be rotated to
    // in order to face the player
    float rotationAdjustment{}; // adjustment to the rotation for the specific
                                // texture
                                // arcsin(a*sin(C)/c) = A
                                // need to check for cardinal directions
    currentRotation = std::asin(vectorToPlayer.x / hypotenuse);
    currentRotation += rotationAdjustment;
    enemy.setRotation(currentRotation);
}
