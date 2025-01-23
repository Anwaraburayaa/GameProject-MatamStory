//
// Created by anwar on 1/18/2025.
//

#include "Character.h"
///helper function to prevent code duplication
void checkIfHPisMax(Player &player, const std::shared_ptr<Job> &job) {
    if (player.getPlayerData().currentHP > job->getMaxHP()) {
        player.getPlayerData().currentHP = job->getMaxHP();
    }
    else return;

}

string Responsiple::getCharacterName() const {
    return "Responsiple";
}


int Responsiple::potionMerchantEvent(Player &player, const std::shared_ptr<Job> &job) {
    int counter = 0;
    while (player.getPlayerData().currentHP < job->getMaxHP()) {
        if (player.getPlayerData().coins >= 5) {
            player.getPlayerData().drinkPotion();
            //check if curr health points got the max or above
           checkIfHPisMax(player, job);
        }
        counter++;
    }
    return counter;
}

string RiskTaking::getCharacterName() const {
    return "RiskTaking";
}

int RiskTaking::potionMerchantEvent(Player &player, const std::shared_ptr<Job> &job) {
    if(player.getPlayerData().currentHP <50 && player.getPlayerData().coins >=5) {
        player.getPlayerData().drinkPotion();
        checkIfHPisMax(player, job);
        return 1;
    }
    return 0;
}
}

