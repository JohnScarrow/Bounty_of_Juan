/**
 * @file play.h
 * @author Nathan, Brayden, Tristan, John
 * @brief handles the game, updates to game:(rendering, updating, input)
 * @date 2026-04-07
 */

#ifndef PLAY_H
#define PLAY_H

#include "button.h"
#include "enemy.h"
#include "juan.h"
#include "states.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <vector>

class Play {
  public:
    Play();
    ~Play();
    State handleInput(sf::Event &e, sf::RenderWindow &window);
    void update(double elapsedTime, sf::RenderWindow &window);
    void render(sf::RenderWindow &window);
    sf::Vector2f getJuanPosition() const;
    bool isJuanDead() const;
    void reset(sf::RenderWindow &window);
    void initializeEnemyList(sf::RenderWindow &window);
    void addEnemy();
    void updateAllEnemies(double elapsedTime);
    void renderAllEnemies();
    void destroyEnemy(Enemy *enemy);
    void destroyEnemyList();
    void checkCollisions();
    sf::Vector2f selectTarget();

  private:
    Juan mJuan;
    std::vector<Enemy *> mEnemyList;
    // Button mRestart;
    // Button mRules;
    // Button mResults;
    // Button mExit;
};

#endif
