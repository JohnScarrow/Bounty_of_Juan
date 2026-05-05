/**
 * @file game.cpp
 * @author Nathan, Brayden, Tristan, John
 * @brief
 * @date 11-04-2026
 */

#include "../header/game.h"
#include "../header/results.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <string>
#include <vector>

Game::Game(sf::RenderWindow &window) {
    mGameState = welcome;
    mPreviousState = welcome;
    mGame.initializeEnemyList(window);
}

void Game::handleInput(sf::RenderWindow &window) {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
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

void Game::update(double elapsedTime, sf::RenderWindow &window) {
    switch (mGameState)
    {
    case welcome:
        mWelcomeScreen.update(window);
        break;
    case game:
        mGame.update(elapsedTime, window);
        break;
    case paused:
        break;
    case results:
        break;
    case quit:
        window.close();
        break;
    default:
        break;
    }
}

void Game::render(sf::RenderWindow &window) {
    switch (mGameState)
    {
    case welcome:
        mWelcomeScreen.render(window);
        break;
    case game:
        mGame.render(window);
        break;
    case paused:
        mGame.render(window);
        break;
    case results:
        mResults.render(window);
        break;
    default:
        break;
    }
}

void Game::inGameStats(sf::RenderWindow &window, const sf::Font &font) {
    Stats stats = Results::instance().getStats();

    int minutes = static_cast<int>(stats.timeSurvived) / 60;
    int seconds = static_cast<int>(stats.timeSurvived) % 60;

    int accuracy = 0;
    if (stats.shotsFired > 0) {
        int shotsHit = stats.shotsFired - stats.shotsMissed;
        accuracy = static_cast<int>((float)shotsHit / stats.shotsFired * 100.f);
    }

    std::vector<std::string> lines = {
        "Time: " + std::to_string(minutes) + ":" + (seconds < 10 ? "0" : "") + std::to_string(seconds),
        "Enemies Killed: " + std::to_string(stats.enemiesKilled),
        "Shots Fired: " + std::to_string(stats.shotsFired),
        "Accuracy: " + std::to_string(accuracy) + "%"
    };

    sf::View gameView = window.getView();
    window.setView(window.getDefaultView());

    float y = 10.f;
    for (const auto &line : lines) {
        sf::Text text;
        text.setFont(font);
        text.setString(line);
        text.setCharacterSize(20);
        text.setFillColor(sf::Color::White);
        text.setOutlineColor(sf::Color::Black);
        text.setOutlineThickness(1.f);
        text.setPosition(10.f, y);
        window.draw(text);
        y += 28.f;
    }

    window.setView(gameView);
}

sf::Vector2f Game::getJuanPosition() const { return mGame.getJuanPosition(); }
