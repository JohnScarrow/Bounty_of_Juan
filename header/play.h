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
#include <vector>

class Play {
  public:
    Play();
    State handleInput(sf::Event &e, sf::RenderWindow &window);
    void update(double elapsedTime, sf::RenderWindow &window);
    void render(sf::RenderWindow &window);
    sf::Vector2f getJuanPosition() const;
    void initializeEnemyList(sf::RenderWindow &window);
    void addEnemy();

  private:
    Juan mJuan;
    std::vector<Enemy> mEnemyList;
    // Button mRestart;
    // Button mRules;
    // Button mResults;
    // Button mExit;
};

#endif
