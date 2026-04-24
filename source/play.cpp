/**
 * @file play.cpp
 * @author Nathan, Brayden, John, Tristan
 * @brief
 * @date 11-04-2026
 *
 *
 */

#include "../header/play.h"
#include <SFML/System/Vector2.hpp>
Play::Play() {
    // mJuan.setBondary(30, 20, 580, 400);

    // mRules.setPosition(sf::Vector2f(60, 450));
    // mRules.setSize(sf::Vector2f(60, 20));
    // mRules.setText("Rules");
    // mRules.setColorTextNormal(sf::Color::Blue);

    // mRestart.setPosition(sf::Vector2f(220, 450));
    // mRestart.setSize(sf::Vector2f(60, 20));
    // mRestart.setText("Restart");
    // mRestart.setColorTextNormal(sf::Color::Blue);

    // mResults.setPosition(sf::Vector2f(420, 450));
    // mResults.setSize(sf::Vector2f(60, 20));
    // mResults.setText("Results");
    // mResults.setColorTextNormal(sf::Color::Blue);

    // mExit.setText("Exit");
    // mExit.setPosition({580, 450});
    // mExit.setSize({60, 20});
    // mExit.setColorTextNormal(sf::Color::Blue);
}

// State Play::handleInput(sf::Event& e,  sf::RenderWindow& window)
// {
//     if (mRules.handleInput(e, window)){
//         return welcome;
//     }
//     if (mRestart.handleInput(e, window)){
//         return game;
//     }
//     if (mResults.handleInput(e, window)){
//         return results;
//     }
//     if (mExit.handleInput(e, window)){
//         return quit;
//     }
//     return game;
// }

sf::Vector2f Play::getJuanPosition() const { return mJuan.getPosition(); }
/**
 * @brief iterates over the list of enemies and picks the enemy closest to the 
 * PC and returns the position of that enemy
 * 
 * @return sf::Vector2f 
 */
sf::Vector2f Play::selectTarget() {
    float min = mEnemyList.at(0)->getHypotenuse();
    size_t target{};
    for (size_t x{1}; x < mEnemyList.size(); x++) {
        if (mEnemyList[x]->getHypotenuse() < min) {
            min = mEnemyList[x]->getHypotenuse();
            target = x;
        }
    }
    return mEnemyList[target]->getEnemyPos();
}

void Play::update(double elapsedTime, sf::RenderWindow &window) {
    mJuan.update(elapsedTime, window, selectTarget());
    updateAllEnemies(elapsedTime);

    // mRules.update();
    // mRestart.update();
    // mResults.update();
    // mExit.update();
}

void Play::render(sf::RenderWindow &window) {
    mJuan.render(window);
    if (mEnemyList.size() < 5) {
        addEnemy();
    }
    renderAllEnemies();

    // window.draw(mRules);
    // window.draw(mRestart);
    // window.draw(mResults);
    // window.draw(mExit);
}
/**
 * @brief Makes the first enemy which initializes the static variables
 * for all other Enemy objects
 * 
 * @param window 
 */
void Play::initializeEnemyList(sf::RenderWindow &window) {
    mEnemyList.push_back(new Enemy(&mJuan, &window));
}
/**
 * @brief makes a pointer to a new enemy and pushes it to the vector
 * 
 */
void Play::addEnemy() { mEnemyList.push_back(new Enemy()); }
/**
 * @brief iterates over the list of enemies and calls the update method on all of them
 * 
 * @param elapsedTime 
 */
void Play::updateAllEnemies(double elapsedTime) {
    for (Enemy *x : mEnemyList) {
        x->update(elapsedTime);
    }
}

/**
 * @brief iterates over the vector of the enemies and calls the render method on all of them
 * 
 */
void Play::renderAllEnemies() {
    for (Enemy *x : mEnemyList) {
        x->render();
    }
}
/**
 * @brief takes in a pointer to an enemy and frees up the memory allocated to them
 * 
 * @param enemy 
 */
void Play::destroyEnemy(Enemy *enemy) { delete enemy; }
/**
 * @brief removes the entire list of enemies
 * 
 */
void Play::destroyEnemyList() {
    for (Enemy *x : mEnemyList) {
        destroyEnemy(x);
    }
}
Play::~Play() { destroyEnemyList(); }
