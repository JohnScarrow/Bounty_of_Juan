/**
 * @file play.h
 * @author Nathan, Brayden, Tristan, John
 * @brief definition file for button.h
 * @date 2026-04-13
 */
#include "../header/button.h"

/**
 * @brief Constructor for the button
 * 
 * @param size size of button in some form "{int, int}"
 * @param position position of button relative to window in some form "{int, int}"
 * @param font a provided font, in main.cpp just call "font"
 * @param text the text inside the button
 */
Button::Button(sf::Vector2f size, sf::Vector2f position, sf::Font& font, const std::string& text){
    mShape.setSize(size);
    mShape.setPosition(position);
    mShape.setFillColor(sf::Color::Blue);

    mText.setFont(font);
    mText.setString(text);
    mText.setCharacterSize(20);
    mText.setFillColor(sf::Color::White);

    sf::FloatRect textBounds = mText.getLocalBounds();
    mText.setOrigin(textBounds.left + (textBounds.width / 2), textBounds.top + (textBounds.height / 2));

    mText.setPosition(position.x + (size.x / 2), position.y + (size.y / 2));
}

/**
 * @brief draws button
 * 
 * @param window window used
 */
void Button::render(sf::RenderWindow& window){
    window.draw(mShape);
    window.draw(mText);
}

/**
 * @brief updates state of button, first if statement makes it change color when mouse is over it
 * 
 * @param window window used
 */
void Button::update(const sf::RenderWindow& window){
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    bool hovering = mShape.getGlobalBounds().contains(mousePos.x, mousePos.y);

    if(hovering){
        mShape.setFillColor(sf::Color(75, 100, 255));
    }else{
        mShape.setFillColor(sf::Color::Blue);
    }

    if(sf::Mouse::isButtonPressed(sf::Mouse::Left) && hovering){
        mClicked = true;
    }
}

/**
 * @brief returns true or false if button is clicked. should be used for if statements like:
 *          
 *        if(someButton.buttonClicked()){
 *            do something (exit, play, etc.)
 *        }
 * 
 * @return true if button is clicked
 * @return false if button is not clicked
 */
bool Button::buttonClicked()
{
    if(mClicked){
        mClicked = false;
        return true;
    }
    return false;
}