/**
 * @file results.cpp
 * @author Nathan, Brayden, Tristan, John
 * @brief tracks and displays stats at end of game.
 * @date 2026-04-07
 */

#include "../header/results.h"
#include <string>
#include <vector>

// --- Results singleton stat tracker ---

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

// --- ResultsScreen display ---

ResultsScreen::ResultsScreen()
{
    if (!mFont.loadFromFile("assets/westernFont.otf"))
    {
        std::cout << "Error opening font\n";
        exit(2);
    }

    mHeader.setFont(mFont);
    mHeader.setCharacterSize(80);
    mHeader.setString("Game Over");
    mHeader.setFillColor(sf::Color(200, 50, 50));
    sf::FloatRect hBounds = mHeader.getLocalBounds();
    mHeader.setOrigin(hBounds.left + hBounds.width / 2.f, hBounds.top + hBounds.height / 2.f);
    mHeader.setPosition(500.f, 130.f);

    mRestart.setText("Main Menu");
    mRestart.setSize({200.f, 60.f});
    mRestart.setPosition({400.f, 660.f});
}

State ResultsScreen::handleInput(sf::Event& e, sf::RenderWindow& window)
{
    if (mRestart.handleInput(e, window))
        return welcome;
    return results;
}

void ResultsScreen::render(sf::RenderWindow& window)
{
    sf::View saved = window.getView();
    window.setView(window.getDefaultView());
    window.draw(mHeader);

    // Pull live stats from the singleton tracker
    Stats s = Results::instance().getStats();
    int minutes = static_cast<int>(s.timeSurvived) / 60;
    int seconds = static_cast<int>(s.timeSurvived) % 60;
    int accuracy = 0;
    if (s.shotsFired > 0) {
        int hits = s.shotsFired - s.shotsMissed;
        accuracy = static_cast<int>((float)hits / s.shotsFired * 100.f);
    }

    std::vector<std::string> lines = {
        "Time: " + std::to_string(minutes) + ":" + (seconds < 10 ? "0" : "") + std::to_string(seconds),
        "Enemies Killed: " + std::to_string(s.enemiesKilled),
        "Shots Fired:    " + std::to_string(s.shotsFired),
        "Accuracy:       " + std::to_string(accuracy) + "%"
    };

    float y = 300.f;
    for (const auto& line : lines) {
        sf::Text t;
        t.setFont(mFont);
        t.setCharacterSize(32);
        t.setFillColor(sf::Color::White);
        t.setString(line);
        sf::FloatRect b = t.getLocalBounds();
        t.setOrigin(b.left + b.width / 2.f, b.top + b.height / 2.f);
        t.setPosition(500.f, y);
        window.draw(t);
        y += 70.f;
    }

    mRestart.render(window);
    window.setView(saved);
}
