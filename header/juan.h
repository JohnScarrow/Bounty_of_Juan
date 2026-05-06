/**
 * @file juan.h
 * @author Nathan, Brayden, Tristan, John
 * @brief Player character. Inherits health management from Character.
 * @date 2026-04-07
 */

#ifndef JUAN_H
#define JUAN_H
#include "../header/character.h"
#include "../header/projectile.h"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>

class Juan : public Character {
  public:
    Juan();
    ~Juan();

    void update(double elapsedTime, sf::RenderWindow &window, sf::Vector2f target);
    void render(sf::RenderWindow &window);

    /// @brief Overrides Character::getPosition() using Juan's sprite position
    sf::Vector2f getPosition() const override;

    void updateAllProjectiles(sf::RenderWindow &window, double elapsedTime);
    void renderAllProjectiles(sf::RenderWindow &window);
    void destoryProjectile(Projectile *x);
    void shoot();
    void setTarget(sf::Vector2f target) { mTarget = target; }
    const std::vector<Projectile *> &getProjectiles() const { return mShootingList; }
    void reset();

  private:
    std::vector<Projectile *> mShootingList;
    uint mAttackTiming;
    sf::Vector2f mTarget;
    sf::Texture mTextureTile;
    sf::CircleShape mJuan;
    sf::Vector2i mPosition;
    sf::Vector2i mSize;
    void moveJuan(float speed, sf::RenderWindow &window);
};

#endif
