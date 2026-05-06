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
#include <cmath>

Game::Game(sf::RenderWindow &window, const sf::Font &font) {
    mGameState = welcome;
    mPreviousState = welcome;
    mFont = font;
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
            if (mGameState == game) {
                mGame.reset(window);
                Results::instance().reset();
            }
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
            if (mGameState == welcome) {
                mGame.reset(window);
                Results::instance().reset();
            }
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
        mGame.update(elapsedTime, window, 0.5f, true);
        break;
    case game:
        mGame.update(elapsedTime, window, 1.0f, false);
        if (mGame.isJuanDead())
            mGameState = results;
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
        mGame.render(window, false);
        //dimmed display
        {
            sf::View saved = window.getView();
            window.setView(window.getDefaultView());
            sf::RectangleShape dim({(float)window.getSize().x, (float)window.getSize().y});
            dim.setFillColor(sf::Color(0, 0, 0, 100)); 
            window.draw(dim);
            window.setView(saved);
        }
        mWelcomeScreen.render(window);
        break;
    case game:
        mGame.render(window);
        inGameStats(window, mFont);
        break;
    case paused:
        mGame.render(window);
        inGameStats(window, mFont);
        {
            sf::View saved = window.getView();
            window.setView(window.getDefaultView());

            sf::RectangleShape overlay({1000.f, 800.f});
            overlay.setFillColor(sf::Color(0, 0, 0, 140));
            window.draw(overlay);

            sf::Text pauseText;
            pauseText.setFont(mFont);
            pauseText.setString("PAUSED");
            pauseText.setCharacterSize(72);
            pauseText.setFillColor(sf::Color::White);
            pauseText.setOutlineColor(sf::Color::Black);
            pauseText.setOutlineThickness(3.f);
            sf::FloatRect b = pauseText.getLocalBounds();
            pauseText.setOrigin(b.left + b.width / 2.f, b.top + b.height / 2.f);
            pauseText.setPosition(500.f, 350.f);
            window.draw(pauseText);

            sf::Text hint;
            hint.setFont(mFont);
            hint.setString("Press ESC to resume");
            hint.setCharacterSize(28);
            hint.setFillColor(sf::Color(200, 200, 200));
            sf::FloatRect hb = hint.getLocalBounds();
            hint.setOrigin(hb.left + hb.width / 2.f, hb.top + hb.height / 2.f);
            hint.setPosition(500.f, 450.f);
            window.draw(hint);

            window.setView(saved);
        }
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
