/**
 * @file main.cpp
 * @author Nathan, Brayden, Tristan, John
 * @brief will create window and call from game/play to update everything
 * @date 2026-04-07
 */

#include "../header/game.h"
#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>

int main() {
    sf::RenderWindow window(sf::VideoMode(1000, 800), "Bounty of Juan");
    sf::View view(sf::FloatRect(0, 0, 1000, 800));

    sf::Texture backTexture;
    if (!backTexture.loadFromFile("assets/background.png")) {
        std::cout << "Failed to load background texture!\n";
        return -1;
    }

    sf::Font font;
    if (!font.loadFromFile(
            "assets/ARIAL.TTF")) { // replace with whatever font you choose
        return -1;
    }

    sf::Sprite bgSprite;
    bgSprite.setTexture(backTexture);

    sf::Vector2u windowSize = window.getSize();
    sf::Vector2u textureSize = backTexture.getSize();

    // Scale to fit screen
    bgSprite.setScale((float)windowSize.x / textureSize.x,
                      (float)windowSize.y / textureSize.y);

    window.setPosition({50, 50});
    Game game;

    sf::Clock clock;

    while (window.isOpen()) {
        float dt = clock.restart().asSeconds();

        game.handleInput(window);
        game.update(dt, window);

        view.setCenter(game.getJuanPosition());
        window.setView(view);

        window.clear();

        // tile setup for infinite background
        sf::Vector2f camCenter = window.getView().getCenter();
        sf::Vector2f viewSize = window.getView().getSize();

        sf::Vector2u texSize = backTexture.getSize();

        // find top-left corner of view in world space
        float left = camCenter.x - viewSize.x / 2.f;
        float top = camCenter.y - viewSize.y / 2.f;

        // convert to tile coordinates
        int startX = (int)(left) / (int)texSize.x - 1;
        int startY = (int)(top) / (int)texSize.y - 1;

        // how many tiles fit on screen
        int endX = startX + (int)(viewSize.x / texSize.x) + 3;
        int endY = startY + (int)(viewSize.y / texSize.y) + 3;

        for (int x = startX; x <= endX; x++) {
            for (int y = startY; y <= endY; y++) {
                sf::Sprite tile;
                tile.setTexture(backTexture);

                tile.setPosition(x * (int)texSize.x, y * (int)texSize.y);

                window.draw(tile);
            }
        }
        game.render(window);

        window.display();
    }
    return 0;
}
