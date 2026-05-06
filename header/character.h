/**
 * @file character.h
 * @author Nathan, Brayden, Tristan, John
 * @brief Abstract base class for all characters (player and enemies).
 *        Provides shared health management and enforces a common interface
 *        via pure virtual functions (polymorphism).
 * @date 2026-04-07
 */

#ifndef CHARACTER_H
#define CHARACTER_H
#include <SFML/System/Vector2.hpp>

class Character {
public:
    /**
     * @brief Construct a Character with a given max health
     * @param maxHealth Starting and maximum HP
     */
    Character(int maxHealth);
    virtual ~Character() = default;

    /**
     * @brief Reduce health by dmg. Health will not go below 0.
     * @param dmg Amount of damage to apply
     */
    void takeDamage(int dmg);

    /// @return true if health has reached 0
    bool isDead() const;

    /// @return Current health value
    int getHealth() const;

    /// @return Maximum health value
    int getMaxHealth() const;

    /**
     * @brief Returns the character's world position.
     *        Pure virtual — each subclass owns its own sprite.
     */
    virtual sf::Vector2f getPosition() const = 0;

protected:
    int mHealth;
    int mMaxHealth;
};

#endif
