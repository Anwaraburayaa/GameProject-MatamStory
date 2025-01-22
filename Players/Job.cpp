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


 void Job::caculateCompactPower(Player& player){
    player.getPlayerData().combatPower = player.getPlayerData().force + player.getPlayerData().level;
}
int Job::solarEclipseEvent(Player &player) {
    if(player.getPlayerData().force > 0) {
        player.getPlayerData().force +=-1;
        return -1;
    }
    return 0;
}
}
