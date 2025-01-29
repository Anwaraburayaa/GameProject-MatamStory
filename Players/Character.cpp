#include "Character.h"
#include "Player.h"
///helper function to prevent code duplication
void checkIfHPisMax(Player &player, const std::shared_ptr<Job> &job) {
    if (player.getPlayerData().currentHP > job->getMaxHP()) {
        player.getPlayerData().currentHP = job->getMaxHP();
    } else return;
}

string Responsible::getCharacterName() const {
    return "Responsible";
}


int Responsible::potionMerchantEvent(Player &player, const std::shared_ptr<Job> &job) {
    int counter = 0;
    while (player.getPlayerData().currentHP < job->getMaxHP() && player.getPlayerData().coins >= 5) {
        player.getPlayerData().drinkPotion();
        counter++;
        if (player.getPlayerData().currentHP == job->getMaxHP()) {
            break;
        }
    }
    return counter;
}

string RiskTaking::getCharacterName() const {
    return "RiskTaking";
}

int RiskTaking::potionMerchantEvent(Player &player, const std::shared_ptr<Job> &job) {
    if (player.getPlayerData().currentHP < 50 && player.getPlayerData().coins >= 5) {
        player.getPlayerData().drinkPotion();
        checkIfHPisMax(player, job);
        return 1;
    }
    return 0;
}