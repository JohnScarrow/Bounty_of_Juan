/**
 * @file game.h
 * @author Nathan, Brayden, Tristan, John
 * @brief handles the visible window, updates to window:(rendering, updating,
 * input)
 * @date 2026-04-07
 */

#ifndef GAME_H
#define GAME_H
#include "enemy.h"
#include "play.h"
#include "results.h"
#include "states.h"
#include "welcome.h"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <iostream>
#include <vector>

class Game {
  public:
    Game(sf::RenderWindow &window, const sf::Font &font);
    ~Game() {};

    void handleInput(sf::RenderWindow &mWindow);
    void update(double elapsedTime, sf::RenderWindow &mWindow);
    void render(sf::RenderWindow &mWindow);
    sf::Vector2f getJuanPosition() const;
    // bool isDone() const;

  private:
    // sf::RenderWindow mWindow;
    //  bool mIsDone;
    void inGameStats(sf::RenderWindow &mWindow, const sf::Font &font);
    State mGameState;
    State mPreviousState;
    sf::Font mFont;
    Welcome mWelcomeScreen;
    Play mGame;
    ResultsScreen mResults;
};

#endif
