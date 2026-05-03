/**
 * @file welcome.h
 * @author Nathan, John, Brayden, Tristan
 * @brief handles the start of the game, the welcome screen state
 * @date 2026-04-07
 */

#ifndef WELCOME_H
#define WELCOME_H
#include "states.h"
#include "button.h"

class Welcome
{
public:
    Welcome();
    State handleInput(sf::Event& e,  sf::RenderWindow& mWindow);
    void update();
    void update1();
    void render(sf::RenderWindow& mWindow);

private:
    sf::Text mHeader;
    sf::Font mFont;
    Button mStart;  
};

#endif