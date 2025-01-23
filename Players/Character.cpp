//
// Created by anwar on 1/18/2025.
//

#include "Character.h"

string Responsiple::getCharacterName() const {
    return "Responsiple";
}

int Responsiple::potionMerchantEvent(Player &player, const std::shared_ptr<Job> &job) {
    int counter = 0;
    while (player.getPlayerData().currentHP < job->getMaxHP()) {
        if (player.getPlayerData().coins >= 5) {
            player.getPlayerData().drinkPotion();
            //check if curr health points got the max or above
            if (player.getPlayerData().currentHP > job->getMaxHP()) {
                player.getPlayerData().currentHP = job->getMaxHP();
            }
        }
        counter++;
    }
    return counter;
}

string RiskTaking::getCharacterName() const {
    return "RiskTaking";
}
