#include "Encounter.h"
#include <stdexcept>

Monster::Monster(const string &monsterName, const unsigned int &combatPower, const unsigned int &loot, const unsigned int &damage) {
    data = {monsterName, combatPower, loot, damage};
}

unsigned int Monster::calculate(const string &property) const {
    if (property == "combatPower") return data.combatPower;
    if (property == "loot") return data.loot;
    if (property == "damage") return data.damage;
    return 0; // Default for unsupported property
}

Pack::Pack(const vector<Encounter*> &members) : members(members) {
    if (members.size() < 2) {
        throw std::invalid_argument("A pack must contain at least two members.");
    }
}

unsigned int Pack::calculate(const string &property) const {
    unsigned int total = 0;
    for (const auto &member : members) {
        total += member->calculate(property);
    }
    return total;
}

void Encounter::applyEvent(Player &player) {
    unsigned int monsterCombatPower = getCombatPower();
    unsigned int playerCombatPower = player.getForce() + player.getLevel();


    if (playerCombatPower > monsterCombatPower) {
        player.raisLevel();
        player.gainLoot(getLoot());
        if (player.getJob()->isCloseRange()) {
            player.claculateDamage(10);
        }
    } else {
        player.claculateDamage(getDamage());
    }

    result = (playerCombatPower > monsterCombatPower) ? "Player wins" : "Player loses";
}


void Encounter::isSpecial() {
}
