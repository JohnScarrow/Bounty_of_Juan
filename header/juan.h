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
  friend class Game;
  public:
    Juan();
    ~Juan();

    void update(double elapsedTime, sf::RenderWindow &window, sf::Vector2f target, bool isWandering);
    void render(sf::RenderWindow &window);

    /// @brief Overrides Character::getPosition() using Juan's sprite position
    sf::Vector2f getPosition() const override;

    void setPosition(sf::Vector2f position) 
    { 
      mJuan.setPosition(position); // Replace mSprite with whatever your internal sprite is named
    }
    void updateAllProjectiles(sf::RenderWindow &window, double elapsedTime);
    void renderAllProjectiles(sf::RenderWindow &window);
    void destoryProjectile(Projectile *x);
    void shoot();
    void setTarget(sf::Vector2f target) { mTarget = target; }
    void faceTarget(sf::Vector2f target);
    const std::vector<Projectile *> &getProjectiles() const { return mShootingList; }
    void moveJuan(float speed, sf::RenderWindow &window);
    void moveJuan(sf::Vector2f movement); 

    void updateWander(float elapsedTime, sf::Vector2u windowSize);
    void reset();

  private:
    std::vector<Projectile *> mShootingList;
    uint mAttackTiming;
    sf::Vector2f mTarget;
    sf::Texture mTextureTile;
    sf::CircleShape mJuan;
    sf::Vector2i mPosition;
    sf::Vector2i mSize;

    // Movement Constants
    float mWanderAngle = 0.f;
    float mWanderTimer = 0.f;
    float mWanderInterval = 2.0f; // seconds between direction changes    
    const float WANDER_RING_DISTANCE = 100.f;
    const float WANDER_RING_RADIUS = 50.f;
    const float WANDER_JITTER = 2.0f;
    const float WANDER_SPEED = 120.f;
    
};

#endif
