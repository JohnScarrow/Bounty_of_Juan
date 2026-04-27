/**
 * @file enemy.h
 * @author Brayden Thompson
 * @brief Creates an instance of the enemy class that tracks the player and
 * attacks
 * @version 62.0.1.0.2
 * @date 2026-04-21
 *
 * @copyright Thompson Supreme Code™
 *
 */

/**
 * This class has a few quirks compared to how the Play and Game were initially
 * written.
 * - two constructors | one for initialization and one for the rest of the
 * enemies
 * - the main difference on these contructors is that the initialization one
 * takes in a Window and an instance of a Juan obj
 * - the window and juan obj are stored as static pointers so they are shared
 * between all Juan obj's
 * -
 *
 */
#ifndef ENEMY_H
#define ENEMY_H
/**
 * make an enemy and have him attack the player while walking at the player
 *
 */
#include "../header/juan.h"
#include "../header/projectile.h"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Shape.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>
#include <list>
#include <sys/types.h>
#include <vector>
enum Location { Top = 1, Bottom, Left, Right };
class Enemy {
  public:
    /*
     * load in enemy textures and attacks
     */
    Enemy(Juan *juan, sf::RenderWindow *window);
    Enemy();
    ~Enemy();
    float getHypotenuse() { return hypotenuse; }
    sf::Vector2f getEnemyPos() { return this->enemy.getPosition(); }
    void getPlayerPos();
    void setVector();
    void getRandomSpawn();
    void update(double elapsedTime);
    void moveEnemy(float elapsedTime);
    void setCurrentPosition();
    void rotateToPlayer();
    void render();
    void updateAllProjectiles(double elapsedTime);
    void renderAllProjectiles();
    void destoryProjectile(Projectile *x);
    void shoot();
    void takeDamage(int dmg);
    bool isDead() const;
    sf::FloatRect getGlobalBounds() const;
    static sf::RenderWindow *window;
    static Juan *juan;
    static unsigned int enemyCount;

  private:
    std::vector<Projectile *> shootingList;
    uint attackTiming;
    unsigned int attackSpeed;
    int health;
    float speed;
    float hypotenuse;
    float currentRotation;
    sf::Vector2f vectorToPlayer;
    sf::Vector2f target;
    sf::Vector2f currentPosition;
    sf::Vector2f spawnLocation;
    sf::Texture enemyTexture;
    sf::Sprite enemy;
};

#endif
