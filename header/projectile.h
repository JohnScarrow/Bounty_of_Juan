/**
 * @file projectile.h
 * @author Brayden Thompson
 * @brief a projectile to be shot and do damage to the enemy class
 * @version 62.0.1.0.2
 * @date 2026-04-24
 * 
 * @copyright Thompson Supreme Code™
 * 
 */
#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>
#include <sys/types.h>
class Projectile {
  public:
    Projectile(sf::Vector2f origin, sf::Vector2f direction);
    void moveProjectile(float elapsedTime);
    void render(sf::RenderWindow &window);
    void calculateDirection();
    bool shotState();
    void distanceHyp();
    void update(sf::RenderWindow &window, double elapsedTime);
    void markHit();
    bool wasHit() const;
    sf::Vector2f getPosition() const;
    float getRadius() const;
    int getDamage() const;

  private:
    bool mHit;
    float distanceTraveled;
    float distance;
    sf::Vector2f direction;
    sf::Vector2f calculatedDirection;
    float hypotenuse;
    float velocity;
    int damage;
    int range;
    sf::Color projectile_color;
    uint radiusEffect;
    sf::Vector2f origin;
    sf::Texture texture;
    sf::CircleShape body;
};

#endif
