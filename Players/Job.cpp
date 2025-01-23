
#include "Job.h"
#include "Player.h"
void Job::calculateDamage(Player &player, const unsigned int &damage) {
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
string Archer::getJobName() const {
    return "Archer";
}
string Magician::getJobName() const {
    return "Magician";
}
int Magician::solarEclipseEvent(Player &player) {
    player.getPlayerData().force += 1;
    return 1;
}

string Warrior::getJobName() const {
    return "Warrior";
}
void Warrior::caculateCompactPower(Player& player) {
    player.getPlayerData().combatPower=2*(player.getPlayerData().force)+(player.getPlayerData().level);
}
void Warrior::fight(Player &player, const Encounter &encounter) {
    calculateDamage(player, DAMAGE_FIGHT);
}