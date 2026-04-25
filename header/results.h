/**
 * @file results.h
 * @author your name (you@domain.com)
 * @brief tracks and displays stats at end of game.
 * @date 2026-04-07
 */

#ifndef RESULTS_H
#define RESULTS_H

struct Stats{
    int enemiesSpawned = 0;
    int enemiesKilled = 0;
    int shotsFired = 0;
    int shotsMissed = 0;
    float timeSurvived = 0.0;
};

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

#endif