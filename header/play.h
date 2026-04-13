/**
 * @file play.h
 * @author Nathan, Brayden, Tristan, John
 * @brief handles the game, updates to game:(rendering, updating, input)
 * @date 2026-04-07
 */

#ifndef PLAY_H
#define PLAY_H

#include "states.h"
#include "button.h"
#include "juan.h"

class Play
{
public:
    Play();
    State handleInput(sf::Event& e,  sf::RenderWindow& window);
    void update(double elapsedTime, sf::RenderWindow& window);
    void render(sf::RenderWindow& window);
    sf::Vector2f getJuanPosition() const;

private:
    Juan mJuan;
    // Button mRestart;  
    // Button mRules;
    // Button mResults;
    // Button mExit;
};

#endif