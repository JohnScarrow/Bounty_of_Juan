#ifndef JUAN_H
#define JUAN_H

class Player{
public:
    Player(float hp, float dmg) : health(hp), damage(dmg) {}

    float getHealth();
    float getDamage();

    void setHealth(float hp);
    void setDamage(float dmg);
private:
    float health{};
    float damage{};
};

#endif