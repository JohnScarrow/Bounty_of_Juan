/**
 * @file juan.cpp
 * @author Nathan, John, Tristan, Brayden
 * @brief
 * @date 11-04-2026
 *
 *
 */

#include "../header/juan.h"
#include "../header/results.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <cmath>
#include <iostream>

/**
 * @brief Construct a new Juan:: Juan object
 *
 */
Juan::Juan() {
    if (!mTextureTile.loadFromFile("assets/juan_texture.jpg")) {
        std::cout << "Failed to load juan texture\n";
    }
    mJuan.setRadius(31);
    mJuan.setTexture(&mTextureTile);
    // mJuan.setTextureRect(sf::IntRect(64, 32, 62, 62));
    mJuan.setOrigin(62.f / 2.f, 62.f / 2.f);
    mJuan.setPosition(400.f, 300.f);

    // mIncrement = sf::Vector2f(4.f, 4.f);

    mPosition.x = 0;
    mPosition.y = 0;
    mSize.x = 0;
    mSize.y = 0;
    mAttackTiming = 0;
    mHealth = 100;
}

sf::Vector2f Juan::getPosition() const { return mJuan.getPosition(); }

/**
 * @brief update player
 *
 * @param elapsedTime time since last update
 * @param window
 */
void Juan::update(double elapsedTime, sf::RenderWindow &window,
                  sf::Vector2f target) {
    mTarget = target;
    moveJuan(200.f * elapsedTime, window);
    faceTarget(mTarget);
    mAttackTiming++;
    if (mAttackTiming % 15 == 0)
        shoot();
    updateAllProjectiles(window, elapsedTime);
}

/**
 * @brief reposition player on the screen
 *
 * @param speed
 * @param window
 */
void Juan::moveJuan(float speed, sf::RenderWindow &window) {
    sf::Vector2f movement(0.f, 0.f);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        movement.y -= 1.f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        movement.y += 1.f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        movement.x -= 1.f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        movement.x += 1.f;

    // Normalize: prevents moving faster diagonally
    float length = std::sqrt(movement.x * movement.x + movement.y * movement.y);
    if (length != 0) {
        movement /= length; // Scale vector to length of 1
        mJuan.move(movement * speed);
    }
}

/**
 * @brief Render objects from the scene onto the window
 *
 * @param window
 */
void Juan::render(sf::RenderWindow &window) {
    window.draw(mJuan);
    renderAllProjectiles(window);

    // Health bar drawn in screen space
    sf::View saved = window.getView();
    window.setView(window.getDefaultView());

    const float barW = 200.f, barH = 16.f, barX = 10.f, barY = 770.f;
    sf::RectangleShape bg({barW, barH});
    bg.setPosition(barX, barY);
    bg.setFillColor(sf::Color(80, 0, 0));
    window.draw(bg);

    float pct = std::max(0, mHealth) / 100.f;
    sf::RectangleShape fill({barW * pct, barH});
    fill.setPosition(barX, barY);
    fill.setFillColor(sf::Color(220, 40, 40));
    window.draw(fill);

    window.setView(saved);
}

void Juan::takeDamage(int dmg) { if (mHealth > 0) mHealth -= dmg; }
bool Juan::isDead() const { return mHealth <= 0; }
int Juan::getHealth() const { return mHealth; }
void Juan::reset()
{
    mHealth = 100;
    mAttackTiming = 0;
    mJuan.setPosition(400.f, 300.f);
    for (auto x : mShootingList) delete x;
    mShootingList.clear();
}

// #include "juan.h"

// float Player::getHealth(){
//     return health;
// }

// float Player::getDamage(){
//     return damage;
// }

// void Player::setHealth(float hp){
//     health = hp;
// }
// void Player::setDamage(float dmg){
//     damage = dmg;
// }
void Juan::updateAllProjectiles(sf::RenderWindow &window, double elapsedTime) {
    std::vector<Projectile *> temp;
    for (Projectile *x : mShootingList) {
        x->update(window, elapsedTime);
    }
    for (auto x : mShootingList) {
        if (x->shotState()) {
            temp.push_back(x);
        } else {
            if (!x->wasHit())
                Results::instance().shotMissed();
            delete x;
        }
    }

    mShootingList = temp;
}
/**
 * @brief calls the render() method on all Projectile objects in the vector
 * 
 * @param window 
 */
void Juan::renderAllProjectiles(sf::RenderWindow &window) {
    for (Projectile *x : mShootingList)
        x->render(window);
}
/**
 * @brief creates a new Projectile object and pushes it onto the vector
 * 
 */
void Juan::shoot() {
    mShootingList.push_back(new Projectile(mJuan.getPosition(), mTarget));
    Results::instance().shotFired();
}
/**
 * @brief Deletes all projectiles from the vector ensuring no memory leaks
 * 
 */
Juan::~Juan() {
    for (auto x : mShootingList) {
        delete x;
    }
}

void Juan::faceTarget(sf::Vector2f target){
    sf::Vector2f position = mJuan.getPosition();
    sf::Vector2f direction = target - position;
    float angle = std::atan2(direction.y, direction.x) * 180.f / 3.14159265f;
    mJuan.setRotation(angle + 270.f);
}