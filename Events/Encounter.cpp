#include "Encounter.h"
#include "Utilities.h"
#include "Player.h"

void Encounter::applyEvent(Player &player) {
    ///todo understand this and fix it
    ///if player won
    ///using player applyEvent here
    if (player.applyEvent(*this)) {
        result = getEncounterWonMessage(player, data.loot);
    }
    ///if the player lost
    else {
        result = getEncounterLostMessage(player, data.damage);
    }
    SpecialEffect();
}
