/**
 * @file juan.h
 * @author Nathan, Brayden, Tristan, John
 * @brief handles player stats and player sprite
 * @date 2026-04-07
 */

#ifndef JUAN_H
#define JUAN_H
#include "../header/projectile.h"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>

class Juan {
  public:
    Juan();
    ~Juan();

    void update(double elapsedTime, sf::RenderWindow &window,
                sf::Vector2f target);
    void render(sf::RenderWindow &window);
    sf::Vector2f getPosition() const;
    void updateAllProjectiles(sf::RenderWindow &window, double elapsedTime);
    void renderAllProjectiles(sf::RenderWindow &window);
    void destoryProjectile(Projectile *x);
    void shoot();
    void setTarget(sf::Vector2f target) { mTarget = target; }

    // void setBondary(int xPosition, int yPosition, int width, int hight);

  private:
    std::vector<Projectile *> mShootingList;
    uint mAttackTiming;
    sf::Vector2f mTarget;
    sf::Texture mTextureTile;
    sf::CircleShape mJuan;
    // sf::Vector2f mIncrement;
    sf::Vector2i mPosition;
    sf::Vector2i mSize;
    void moveJuan(float speed, sf::RenderWindow &window);
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
