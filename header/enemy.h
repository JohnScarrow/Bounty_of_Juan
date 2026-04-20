#ifndef ENEMY_H
#define ENEMY_H
/**
 * make an enemy and have him attack the player while walking at the player
 *
 */
#include "../header/juan.h"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Shape.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>
enum Location { Top = 1, Bottom, Left, Right };
class Enemy {
  public:
    /*
     * load in enemy textures and attacks
     */
    Enemy(Juan *juan, sf::RenderWindow *window);
    Enemy();
    void getPlayerPos();
    void setVector();
    void getRandomSpawn();
    void update(double elapsedTime);
    void moveEnemy();
    void setCurrentPosition();
    void rotateToPlayer();
    void render();
    static sf::RenderWindow *window;
    static Juan *juan;
    static unsigned int enemyCount;

  private:
    unsigned int attackSpeed;
    unsigned int health;
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
