
#include "Player.h"
#include "../Events/Encounter.h"
class Job;

string Player::getName() const {
    return playerData.name;
}


unsigned int Player::getCoins() const {
    return playerData.coins;
}

unsigned int Player::getForce() const {
    return playerData.force;
}

unsigned int Player::getLevel() const {
    return playerData.level;
}

unsigned int Player::getHealthPoints() const {
    return playerData.currentHP;
}

void Player::raisLevel() {
    if (playerData.level < PlayerData::MaxLevel) {
        playerData.level += 1;
        caculateCompactPower();
    }
}

bool Player::PlayerKnockOut() {
   return this->playerData.isKnockedOut = true;
}

string Player::getDescription() const {
    return getName() + ", " + this->getJob()->getJobName() + " with " + getCharacter()->getCharacterName()
           + " character (level " + std::to_string(getLevel()) + ", force " + std::to_string(getForce()) + ")";
}


void Player::caculateCompactPower() {
    job->caculateCompactPower(*this);
}

Player &Player::operator=(const Player &other) {
    if (this == &other) {
        return *this;
    }
    playerData = other.playerData;
    job = other.job;
    character = other.character;
    return *this;
}

bool Player::operator<(const Player &other) const {
    if (playerData.level < other.getLevel()) {
        return true;
    }
    if (playerData.level > other.getLevel()) {
        return false;
    }
    if (playerData.coins < other.getCoins())
        return true;
    if (playerData.coins > other.getCoins())
        return false;

    return playerData.name > other.getName();
}

void Player::gainLoot(const unsigned int loot) {
    playerData.coins += loot;
}

bool Player::applyEvent(const Encounter &encounter) {
    ///if wining
    if (this->getPlayerData().combatPower > encounter.getEncounterData().combatPower) {
        job->fight(*this, encounter);
        gainLoot(encounter.getEncounterData().loot);
        raisLevel();
        return true;
        ///if losing
    } else {
        claculateDamage(encounter.getEncounterData().damage);
        return false;
    }
}

void Player::PlayerData::drinkPotion() {
    assert(this->coins >= 5);
    this->coins -= 5;
    this->currentHP += 10;
}

void Player::claculateDamage(const unsigned int &damage) {
    int currentHPTotal = playerData.currentHP;
    if (currentHPTotal <= damage) {
        playerData.currentHP =0;
        PlayerKnockOut();
    }
    job->calculateDamage(*this, damage);
}
std::ostream &operator<<(std::ostream &out, const Player::PlayerData &playerData) {
  out << "Name: " + playerData.name << std::endl;
  out << "Level: " << playerData.level << std::endl;
  out << "HP: " << playerData.currentHP << std::endl;
  out << "Force: " << playerData.force << std::endl;
  out << "Combat Power: " << playerData.combatPower << std::endl;
  out << "Coins: " << playerData.coins << std::endl;
  out << "Is KO'ed: " << playerData.isKnockedOut;
  return out;
 }

int Player::solarEclipseEvent() {
    int solarEclipseEffect;
    solarEclipseEffect = job->solarEclipseEvent(*this);
    caculateCompactPower();
    return solarEclipseEffect;
}

int Player::potionMerchantEvent() {
    return character->potionMerchantEvent(*this, job);
}





