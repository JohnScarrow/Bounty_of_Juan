/**
 * @file results.h
 * @author Nathan, Brayden, Tristan, John
 * @brief tracks and displays stats at end of game.
 * @date 2026-04-07
 */

#ifndef RESULTS_H
#define RESULTS_H
#include "states.h"
#include "button.h"

struct Stats{
    int enemiesSpawned = 0;
    int enemiesKilled = 0;
    int shotsFired = 0;
    int shotsMissed = 0;
    float timeSurvived = 0.0;
};

// Singleton stat tracker used throughout gameplay
class Results{
public:
    static Results& instance();

    void enemySpawned();
    void enemyKilled();
    void shotFired();
    void shotMissed();
    void updateTime(float dt);

    Stats getStats() const;
    void reset();
private:
    Stats stats;
    Results() = default;
};

// Screen shown when the player dies
class ResultsScreen
{
public:
    ResultsScreen();
    State handleInput(sf::Event& e, sf::RenderWindow& window);
    void render(sf::RenderWindow& window);

private:
    sf::Font mFont;
    sf::Text mHeader;
    Button mRestart;
};

#endif
