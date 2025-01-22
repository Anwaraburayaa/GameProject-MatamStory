//
// Created by anwar on 1/15/2025.
//

#include "Job.h"
void Job::takeDamage(Player &player, const unsigned int &damage) {
    if(player.getPlayerData().currentHP <= damage) {
        return;
    }
        player.getPlayerData().currentHP -= damage;
    }


// virtual void calculateCombatPower(Player& player) const {
//     // Access PlayerData through Player
//     Player::PlayerData& data = player.getPlayerData();
//     data.combatPower = data.force * data.level;  // Example combat power formula
// }