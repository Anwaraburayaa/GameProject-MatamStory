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
    makeSpecialEffect();
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

void Balrog::makeSpecialEffect() {
    encounterData.combatPower += 2;
}
///it iterates through the monsters in the pack and if they are balrogs it updates their compactPower
///then updates the pack status
void Pack::makeSpecialEffect() {
    for (const std::unique_ptr<Encounter> &encounter: encounters) {
        encounter->makeSpecialEffect();
    }
    updateStatus();
}
