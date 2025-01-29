#include "Encounter.h"
#include "Utilities.h"


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
    ///if player won
    ///using player applyEvent here
    if (player.handleEvent(*this)) {
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

unsigned int Pack::getEncounterSize() const {
    unsigned int totalMonsters = 0;
    for (const auto &encounter: encounters) {
        if (auto subPack = dynamic_cast<const Pack *>(encounter.get())) {
            totalMonsters += subPack->getEncounterSize();
        } else {
            totalMonsters += encounter->getEncounterData().enounterNum;
        }
    }

    return totalMonsters;
}


std::string Pack::getDescription() const {
    return "Pack of " + std::to_string(getEncounterSize()) + " members (power " +
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

void Pack::updateStatus() {
    encounterData.combatPower = 0;
    encounterData.loot = 0;
    encounterData.damage = 0;

    for (const std::unique_ptr<Encounter> &encounter: encounters) {
        encounterData.combatPower += encounter->getCombatPower();
        encounterData.loot += encounter->getLoot();
        encounterData.damage += encounter->getDamage();
    }
}
