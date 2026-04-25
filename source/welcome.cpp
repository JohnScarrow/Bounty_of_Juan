#include "../header/welcome.h"
#include <iostream>

Welcome::Welcome()
{
    if (!mFont.loadFromFile("assets/westernFonts.otf"))
    {
        std::cout << "Error opening file\n";
        exit(2);
    }

    mHeader.setFont(mFont);
    mHeader.setCharacterSize(20);
    mHeader.setString("Bounty of Juan");

    mRules.setFont(mFont);
    mRules.setCharacterSize(16);
    mRules.setString("Start\n");
    mRules.setPosition({10, 30});

    mStart = std::make_unique<Button>(
        sf::Vector2f(120, 40),
        sf::Vector2f(440, 380),
        mFont,
        "Start"
    );
}

State Welcome::handleInput(sf::Event& e, sf::RenderWindow& window)
{
    if (mStart->buttonClicked())
        return game;
    return welcome;
}

void Welcome::update(const sf::RenderWindow& window)
{
    mStart->update(window);
}

void Welcome::render(sf::RenderWindow& window)
{
    window.draw(mHeader);
    window.draw(mRules);
    mStart->render(window);
}
