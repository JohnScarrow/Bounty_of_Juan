/**
* @file button.h
* @author Nathan, Brayden, Tristan, John
* @brief makes and handles button input, what all to do when a button is pressed.
* @date 2026-04-13
*/
#ifndef BUTTON_H
#define BUTTON_H
#include <SFML/Graphics.hpp>
#include <iostream>

enum state {normal, hovered, clicked};

class Button{
public:
    Button();
    Button(sf::Vector2f size, sf::Vector2f position, sf::Font& font, const std::string& text);
    ~Button(){};
    void render(sf::RenderWindow& window);
    void update(const sf::RenderWindow& window);
    bool buttonClicked();
    
    // nathan added 
    void setText(std::string s);
    void setPosition(sf::Vector2f position);
    void setSize(sf::Vector2f  size);
    void setColor(sf::Color btnColor);
    bool handleInput(sf::Event& e, sf::RenderWindow& window);
    void update1();
    virtual void draw(sf::RenderTarget& target,sf::RenderStates states) const;

private:
    sf::RectangleShape mShape;
    sf::Text mText;
    bool mClicked = false;

    //nathan added
    sf::Sprite mButton;
    sf::Texture mTexture;
    sf::Color mButtonColor;
    sf::Vector2f mPosition;
    sf::Uint32 mBtnState;

    sf::Font mFont;
    sf::Color mTextNormal;
    sf::Color mTextHover;
};

#endif