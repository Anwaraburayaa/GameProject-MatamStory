#include "Encounter.h"
#include "Utilities.h"
#include "Player.h"

unsigned int Encounter::getCombatPower() const {
    return encounterData.combatPower;
}

unsigned int Encounter::getLoot() const {
    return encounterData.loot;
}

unsigned int Encounter::getDamage() const {
    return encounterData.damage;
}

void Encounter::applyEvent(Player &player) {
    ///todo understand this and fix it
    ///if player won
    ///using player applyEvent here
    if (player.applyEvent(*this)) {
        result = getEncounterWonMessage(player, encounterData.loot);
    }
    ///if the player lost
    else {
        result = getEncounterLostMessage(player, encounterData.damage);
    }
    SpecialEffect();
}
std::string Monster::getDescription() const {
    return encounterData.monsterName +
         " (power " + std::to_string(encounterData.combatPower) + ", loot " +
         std::to_string(encounterData.loot) +
         ", damage " + std::to_string(encounterData.damage) + ")";
}

std :: string Pack::getDescription() const {
    return "Pack of " + std::to_string(encounters.size()) + " members (power " +
          std::to_string(encounterData.combatPower) + ", loot " +
          std::to_string(encounterData.loot) + ", damage " +
          std::to_string(encounterData.damage) + ")";
}

