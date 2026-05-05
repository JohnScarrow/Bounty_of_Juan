/**
 * @file results.h
 * @author Nathan, Brayden, Tristan, John
 * @brief tracks and displays stats at end of game.
 * @date 2026-04-07
 */

#ifndef RESULTS_H
#define RESULTS_H
#include "states.h"
#include "button.h"

class Results
{
public:
    Results();
    State handleInput(sf::Event& e, sf::RenderWindow& window);
    void render(sf::RenderWindow& window);

private:
    sf::Font mFont;
    sf::Text mHeader;
    Button mRestart;
};

#endif
