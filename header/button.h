/**
* @file button.h
* @author Nathan, Brayden, Tristan, John
* @brief makes and handles button input, what all to do when a button is pressed.
* @date 2026-04-13
*/
#ifndef BUTTON_H
#define BUTTON_H
#include <SFML/Graphics.hpp>

class Button{
public:
    Button(sf::Vector2f size, sf::Vector2f position, sf::Font& font, const std::string& text);
    void render(sf::RenderWindow& window);
    void update(const sf::RenderWindow& window);
    bool buttonClicked();
private:
    sf::RectangleShape mShape;
    sf::Text mText;
    bool mClicked = false;
};

#endif