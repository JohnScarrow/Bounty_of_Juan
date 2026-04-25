/**
 * @file results.cpp
 * @author your name (you@domain.com)
 * @brief tracks and displays stats at end of game.
 * @date 2026-04-07
 */

#include "../header/results.h"

Results& Results::instance(){
    static Results instance;
    return instance;
}

void Results::enemySpawned(){
    stats.enemiesSpawned++;
}

void Results::enemyKilled(){
    stats.enemiesKilled++;
}

void Results::shotFired(){
    stats.shotsFired++;
}

void Results::shotMissed(){
    stats.shotsMissed++;
}

void Results::updateTime(float dt){
    stats.timeSurvived += dt;
}

Stats Results::getStats() const{
    return stats;
}

void Results::reset(){
    stats = Stats();
}