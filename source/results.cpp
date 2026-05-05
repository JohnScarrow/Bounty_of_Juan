/**
 * @file results.cpp
 * @author Nathan, Brayden, Tristan, John
 * @brief tracks and displays stats at end of game.
 * @date 2026-04-07
 */

#include "../header/results.h"

Results::Results()
{
    if (!mFont.loadFromFile("assets/westernFont.otf"))
    {
        std::cout << "Error opening font\n";
        exit(2);
    }

    mHeader.setFont(mFont);
    mHeader.setCharacterSize(72);
    mHeader.setString("Game Over");
    mHeader.setFillColor(sf::Color(200, 50, 50));
    sf::FloatRect hBounds = mHeader.getLocalBounds();
    mHeader.setOrigin(hBounds.left + hBounds.width / 2.f, hBounds.top + hBounds.height / 2.f);
    mHeader.setPosition(500.f, 250.f);

    mRestart.setText("Main Menu");
    mRestart.setSize({200.f, 60.f});
    mRestart.setPosition({400.f, 420.f});
}

State Results::handleInput(sf::Event& e, sf::RenderWindow& window)
{
    if (mRestart.handleInput(e, window))
        return welcome;
    return results;
}

void Results::render(sf::RenderWindow& window)
{
    sf::View saved = window.getView();
    window.setView(window.getDefaultView());
    window.draw(mHeader);
    mRestart.render(window);
    window.setView(saved);
}
