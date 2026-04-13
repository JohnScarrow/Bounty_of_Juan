/**
 * @file juan.cpp
 * @author Nathan, John, Tristan, Brayden
 * @brief 
 * @date 11-04-2026
 * 
 * 
 */

#include "../header/juan.h"
#include <iostream>
#include <cmath>

/**
 * @brief Construct a new Juan:: Juan object
 * 
 */
Juan::Juan() 
{
    if (!mTextureTile.loadFromFile("assets/juan_texture.jpg"))
    {
        std::cout << "Failed to load juan texture\n";
    }
    mJuan.setRadius(31);
    mJuan.setTexture(&mTextureTile);
    // mJuan.setTextureRect(sf::IntRect(64, 32, 62, 62));
    mJuan.setOrigin(62.f / 2.f, 62.f / 2.f);
    mJuan.setPosition(400.f, 300.f);

    // mIncrement = sf::Vector2f(4.f, 4.f);

    mPosition.x=0;
    mPosition.y=0;
    mSize.x=0;
    mSize.y=0;
}

sf::Vector2f Juan::getPosition() const
{
    return mJuan.getPosition();
}

/**
 * @brief update player
 * 
 * @param elapsedTime time since last update
 * @param window 
 */
void Juan::update(double elapsedTime, sf::RenderWindow& window)
{
    moveJuan(200.f * elapsedTime, window);
}

/**
 * @brief reposition player on the screen
 * 
 * @param speed
 * @param window 
 */
void Juan::moveJuan(float speed, sf::RenderWindow& window)
{
    sf::Vector2f movement(0.f, 0.f);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) movement.y -= 1.f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) movement.y += 1.f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) movement.x -= 1.f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) movement.x += 1.f;

    // Normalize: prevents moving faster diagonally
    float length = std::sqrt(movement.x * movement.x + movement.y * movement.y);
    if (length != 0) 
    {
        movement /= length; // Scale vector to length of 1
        mJuan.move(movement * speed);
    }
}

/**
 * @brief Render objects from the scene onto the window
 * 
 * @param window 
 */
void Juan::render(sf::RenderWindow& window)
{
    window.draw(mJuan);
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