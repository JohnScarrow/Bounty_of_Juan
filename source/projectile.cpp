/**
 * @file projectile.cpp
 * @author Brayden Thompson
 * @brief Source code for the projectile class
 * @version 62.0.1.0.2
 * @date 2026-04-24
 * 
 * @copyright Thompson Supreme Code™
 * 
 */
#include "../header/projectile.h"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <cmath>

Projectile::Projectile(sf::Vector2f origin, sf::Vector2f direction) {
    this->origin = origin;
    this->direction = direction;
    radiusEffect = 5.f;
    range = 200;
    distance = 1000;
    velocity = 1000;

    projectile_color = sf::Color::Red;
    body.setRadius(radiusEffect);
    body.setFillColor(projectile_color);
    body.setPosition(origin);
}
void Projectile::render(sf::RenderWindow &window) { window.draw(body); }
bool Projectile::shotState() {
    if (distanceTraveled > distance) {

        return false;
    }
    return true;
}

void Projectile::distanceHyp() {
    distanceTraveled = std::sqrt(std::pow(origin.x - body.getPosition().x, 2) +
                                 std::pow(origin.y - body.getPosition().y, 2));
}
void Projectile::update(sf::RenderWindow &window, double elapsedTime) {
    calculateDirection();
    moveProjectile(elapsedTime);
    distanceHyp();
    render(window);
}
void Projectile::moveProjectile(float elapsedTime) {
    if (hypotenuse != 0) {
        body.move((calculatedDirection / hypotenuse) *
                  (velocity * elapsedTime));
    }
}

void Projectile::calculateDirection() {
    float scalefactor{};
    calculatedDirection.x = direction.x - origin.x;
    calculatedDirection.y = direction.y - origin.y;

    hypotenuse = std::sqrt(calculatedDirection.x * calculatedDirection.x +
                           calculatedDirection.y * calculatedDirection.y);
    scalefactor = range / hypotenuse;
    calculatedDirection.x *= scalefactor;
    calculatedDirection.y *= scalefactor;
}
