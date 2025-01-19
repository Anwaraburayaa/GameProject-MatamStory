//
// Created by anwar on 1/19/2025.
//
#include "Player.h"
string Player::getName() const {
    return data.name;
}
unsigned int Player::getCoins() const {
    return data.coins;
}
int Player::getForce() const {
    return data.force;
}
int Player::getLevel() const {
    return data.level;
}



