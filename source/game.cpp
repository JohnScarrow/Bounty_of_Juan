/**
 * @file game.cpp
 * @author Nathan, Brayden, Tristan, John
 * @brief 
 * @date 11-04-2026
 * 
 * 
 */

#include "../header/game.h"

Game::Game()
{
    mGameState = welcome;
    mPreviousState = welcome;
}

void Game::handleInput(sf::RenderWindow& window)
{
    sf::Event event;
    while(window.pollEvent(event))
    {
        if(event.type == sf::Event::Closed)
            window.close();

        switch (mGameState)
        {
        case welcome:
            mGameState = mWelcomeScreen.handleInput(event, window);
            break;
        case game:
            mGameState = mGame.handleInput(event, window);
            break;
        case paused:
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
                mGameState = game;
            break;
        case results:
            mGameState = mResults.handleInput(event, window);
            break;
        case quit:
            window.close();
            break;
        default:
            break;
        }
    }
}

void Game::update(double elapsedTime, sf::RenderWindow& window)
{
    switch (mGameState)
    {
    case welcome:
        mWelcomeScreen.update1();
        break;
    case game:
        mGame.update(elapsedTime, window);
        break;
    case paused:
        break; // game world frozen while paused
    case results:
        break;
    case quit:
        window.close();
        break;
    default:
        break;
    }
}

void Game::render(sf::RenderWindow& window)
{
    switch (mGameState)
    {
    case welcome:
        mWelcomeScreen.render(window);
        break;
    case game:
        mGame.render(window);
        break;
    case paused:
        mGame.render(window); // keep world visible while paused
        break;
    case results:
        mResults.render(window);
        break;
    default:
        break;
    }
}

sf::Vector2f Game::getJuanPosition() const
{
    return mGame.getJuanPosition();
}