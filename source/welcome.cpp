#include "../header/welcome.h"

Welcome::Welcome()
{
    if (!mFont.loadFromFile("assets/westernFont.otf"))
    {
        std::cout<<"Error opening file\n";
        exit(2);
    }
    
    mHeader.setFont(mFont);
    mHeader.setCharacterSize(72);
    mHeader.setString("Bounty of Juan");
    mHeader.setFillColor(sf::Color::White);
    sf::FloatRect hBounds = mHeader.getLocalBounds();
    mHeader.setOrigin(hBounds.left + hBounds.width / 2.f, hBounds.top + hBounds.height / 2.f);
    mHeader.setPosition(500.f, 250.f);

    mStart.setText("Play");
    mStart.setSize({160.f, 60.f});
    mStart.setPosition({420.f, 420.f});
}

State Welcome::handleInput(sf::Event& e, sf::RenderWindow& window)
{
    if (mStart.handleInput(e, window)){
        return game;
    }
    return welcome;
}

void Welcome::update1()
{
    mStart.update1();
}

void Welcome::render(sf::RenderWindow& window)
{
    sf::View saved = window.getView();
    window.setView(window.getDefaultView());
    window.draw(mHeader);
    mStart.render(window);
    window.setView(saved);
}