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

int Player::getHealthPoints() const {
    return data.currentHP;
}

void Player::raisLevel() {
    if (data.level < PlayerData::MaxLevel) {
        data.level = +1;
        caculateCompactPower();
    }
}

void Player::isPlayerKnockedOut() {
    this->data.isKnockedOut = true;
}

string Player::getDescription() const {
    return getName() + ", " + this->getJob()->getJobName() + "with" + getCharacter()->getCharacterName() +
           "character (level" + std::to_string(getLevel()) + "force" + std::to_string(getForce()) + ")";
}

///how  to do this?
void Player::caculateCompactPower() {
}

Player &Player::operator=(const Player &other) {
    if (this == &other) {
        return *this;
    }
    data = other.data;
    job = other.job;
    character = other.character;
    return *this;
}

bool Player::operator<(const Player &other) const {
    if(data.level < other.getLevel()) {
        return true;
    }
    if(data.level > other.getLevel()) {
        return false;
    }
    if (data.coins < other.getCoins())
        return true;
    if (data.coins > other.getCoins())
        return false;

    return data.name > other.getName();
}

//**//
