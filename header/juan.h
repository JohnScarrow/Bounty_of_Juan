/**
 * @file juan.h
 * @author Nathan, Brayden, Tristan, John
 * @brief handles player stats and player sprite
 * @date 2026-04-07
 */

#ifndef JUAN_H
#define JUAN_H
#include <SFML/Graphics.hpp>

class Juan
{
public:
    Juan();

    void update(double elapsedTime, sf::RenderWindow& window);
    void render(sf::RenderWindow& window);
    sf::Vector2f getPosition() const;
    // void setBondary(int xPosition, int yPosition, int width, int hight);

private:
    sf::Texture mTextureTile;
    sf::CircleShape mJuan;
    // sf::Vector2f mIncrement;
    sf::Vector2i mPosition;
    sf::Vector2i mSize;

    void moveJuan(float speed, sf::RenderWindow& window);
};

// class Juan{
// public:
//     Juan(float hp, float dmg) : health(hp), damage(dmg) {}

//     float getHealth();
//     float getDamage();

//     void setHealth(float hp);
//     void setDamage(float dmg);

// private:
//     float health{};
//     float damage{};
// };

#endif