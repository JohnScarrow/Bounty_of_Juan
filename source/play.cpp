/**
 * @file play.cpp
 * @author Nathan, Brayden, John, Tristan
 * @brief
 * @date 11-04-2026
 *
 *
 */

#include "../header/play.h"
#include "../header/results.h"
#include <SFML/System/Vector2.hpp>
#include <algorithm>
#include <cmath>

Play::Play() {

}
// Pausing Game Feature
State Play::handleInput(sf::Event& e, sf::RenderWindow& window)
{
    if (e.type == sf::Event::KeyPressed && e.key.code == sf::Keyboard::Escape)
        return paused;
    return game;
}

sf::Vector2f Play::getJuanPosition() const { return mJuan.getPosition(); }
bool Play::isJuanDead() const { return mJuan.isDead(); }

void Play::reset(sf::RenderWindow &window)
{
    mJuan.reset();
    for (Enemy *x : mEnemyList) delete x;
    mEnemyList.clear();
    initializeEnemyList(window);
}
/**
 * @brief iterates over the list of enemies and picks the enemy closest to the 
 * PC and returns the position of that enemy
 * 
 * @return sf::Vector2f 
 */
sf::Vector2f Play::selectTarget() {
    if (mEnemyList.empty())
        return mJuan.getPosition();
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

void Play::checkCollisions() {
    const std::vector<Projectile *> &projectiles = mJuan.getProjectiles();

    std::vector<Enemy *> dead;
    for (Enemy *enemy : mEnemyList) {
        sf::FloatRect bounds = enemy->getGlobalBounds();
        for (Projectile *proj : projectiles) {
            if (proj->wasHit())
                continue;
            float r = proj->getRadius();
            sf::Vector2f pos = proj->getPosition();
            sf::FloatRect projRect(pos.x - r, pos.y - r, r * 2.f, r * 2.f);
            if (bounds.intersects(projRect)) {
                enemy->takeDamage(proj->getDamage());
                proj->markHit();
            }
        }
        if (enemy->isDead())
            dead.push_back(enemy);
    }

    for (Enemy *e : dead) {
        mEnemyList.erase(std::remove(mEnemyList.begin(), mEnemyList.end(), e), mEnemyList.end());
        destroyEnemy(e);
    }
}

void Play::update(double elapsedTime, sf::RenderWindow &window, float speedMultiplier, bool wander) {
    double scaledTime = elapsedTime * speedMultiplier;

    mJuan.update(scaledTime, window, selectTarget(), wander);

    Results::instance().updateTime(scaledTime);
    updateAllEnemies(scaledTime);
    checkCollisions();
}

void Play::render(sf::RenderWindow &window, bool showHealthBar) {
    mJuan.render(window, showHealthBar);
    if (mEnemyList.size() < 5) {
        addEnemy();
    }
    renderAllEnemies();
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
void Play::addEnemy() { mEnemyList.push_back(new Enemy()); Results::instance().enemySpawned(); }
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

void Play::destroyEnemy(Enemy *enemy) { Results::instance().enemyKilled(); delete enemy; }
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
