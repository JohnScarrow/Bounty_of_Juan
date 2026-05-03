#include "../header/welcome.h"

Welcome::Welcome()
{
    if (!mFont.loadFromFile("assets/westernFonts.otf"))
    {
        std::cout<<"Error opening file\n";
        exit(2);
    }
    
    mHeader.setFont(mFont);
    //choose the font size based on button size (I choose half)
    mHeader.setCharacterSize(20);

    // //set label
    mHeader.setString("Bounty of Juan");

    mStart.setText("Start");
    mStart.setPosition({580, 450});
    mStart.setSize({60, 20});
    // mStart.setColorTextNormal(sf::Color::Blue);
    //mStart.setColor(sf::Color(255,255,0));
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
    window.draw(mHeader);
    // window.draw(mStart);
}