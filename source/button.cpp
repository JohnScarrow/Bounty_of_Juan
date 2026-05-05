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

Button::Button() : mClicked(false), mBtnState(state::normal)
{
    mTextNormal = sf::Color::White;
    mTextHover  = sf::Color::Yellow;
    mText.setFillColor(mTextNormal);
    mShape.setFillColor(sf::Color(80, 50, 20));
}

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

// nathan added
void Button::setText(std::string s)
{
    mText.setString(s);
    //set origin to the middle
    mText.setOrigin(mText.getGlobalBounds().width/2, mText.getGlobalBounds().height/2);
    //set position at the middle of the button
    unsigned int fontSize = mButton.getGlobalBounds().height/2;
    mText.setPosition(mPosition.x, mPosition.y-fontSize/4);
}

void Button::setPosition(sf::Vector2f position)
{
    mPosition = position;
    mShape.setPosition(position);
    sf::FloatRect b = mShape.getGlobalBounds();
    mText.setPosition(b.left + b.width / 2.f, b.top + b.height / 2.f);
}

void Button::setSize(sf::Vector2f size)
{
    mShape.setSize(size);
    mShape.setFillColor(sf::Color::Blue);
    sf::FloatRect b = mShape.getGlobalBounds();
    unsigned int fontSize = static_cast<unsigned int>(size.y / 2.f);
    mText.setCharacterSize(fontSize);
    mText.setOrigin(mText.getGlobalBounds().width / 2.f, mText.getGlobalBounds().height / 2.f);
    mText.setPosition(b.left + b.width / 2.f, b.top + b.height / 2.f);
}

void Button::setColor(sf::Color btnColor)
{
    mButtonColor = btnColor;
    mButton.setColor(mButtonColor);
}

bool Button::handleInput(sf::Event& e, sf::RenderWindow& window)
{
    sf::Vector2i mPos = sf::Mouse::getPosition(window);
    sf::Vector2f mousePosition = window.mapPixelToCoords(mPos, window.getDefaultView());
    bool mouseInButton = mShape.getGlobalBounds().contains(mousePosition);
    if(e.type == sf::Event::MouseMoved)
    {
        if(mouseInButton)
        {
            mBtnState = state::hovered;
        }
        else
        {
            mBtnState = state::normal;
        }
    }
    if (e.type == sf::Event::MouseButtonPressed)
    {
        if(e.mouseButton.button==sf::Mouse::Left)
        {
            if(mouseInButton)
            {
                mBtnState = state::clicked;
                return true;
            }
            else
            {
                mBtnState = state::normal;
            }
        }
    }
    if (e.type == sf::Event::MouseButtonReleased)
    {
        if (e.mouseButton.button==sf::Mouse::Left)
        {
            if(mouseInButton)
            {
                mBtnState = state::hovered;
            }
            else
            {
                mBtnState = state::normal;
            }
        }
    }
    return false;
}

void Button::update1()
{
    switch (mBtnState)
    {
    case normal:
        mButton.setRotation(0);
        mText.setFillColor(mTextNormal);
        break;
    case hovered:
        mButton.setRotation(0);
        mText.setFillColor(mTextHover);
        break;
    case clicked:
        mButton.setRotation(180);
        mText.setFillColor(mTextHover);
        break;
    }
}
void Button::draw(sf::RenderTarget& target,sf::RenderStates states) const
{
    target.draw(mButton, states);
    target.draw(mText, states);
}