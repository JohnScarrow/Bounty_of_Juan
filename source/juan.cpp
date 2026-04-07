#include "juan.h"
    
float Player::getHealth(){
    return health;
}

float Player::getDamage(){
    return damage;
}

void Player::setHealth(float hp){
    health = hp;
}
void Player::setDamage(float dmg){
    damage = dmg;
}