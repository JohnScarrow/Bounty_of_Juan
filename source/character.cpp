/**
 * @file character.cpp
 * @author Nathan, Brayden, Tristan, John
 * @brief Implementation of the Character base class.
 * @date 2026-04-07
 */

#include "../header/character.h"

/**
 * @brief Initializes health to maxHealth
 * @param maxHealth Starting HP for this character
 */
Character::Character(int maxHealth) : mHealth(maxHealth), mMaxHealth(maxHealth) {}

/**
 * @brief Reduces health by dmg, clamped at 0
 * @param dmg Damage amount
 */
void Character::takeDamage(int dmg)
{
    if (mHealth > 0)
        mHealth -= dmg;
}

/// @return true when health is 0 or below
bool Character::isDead() const { return mHealth <= 0; }

/// @return Current health
int Character::getHealth() const { return mHealth; }

/// @return Max health set at construction
int Character::getMaxHealth() const { return mMaxHealth; }
