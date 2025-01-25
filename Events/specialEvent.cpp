#include "SpecialEvent.h"
#include "Utilities.h"
#include "Player.h"



string SolarEclipse::getDescription() const {
    return "SolarEclipse";
}

string PotionMerchant::getDescription() const {
    return "PotionsMerchant";
}

void SolarEclipse::applyEvent(Player &player) {
    int solarEclipseEffect = player.solarEclipseEvent();
    result = getSolarEclipseMessage(player, solarEclipseEffect);
}

void PotionMerchant::applyEvent(Player &player) {
    int amountOfPotions = player.potionMerchantEvent();
    result = getPotionsPurchaseMessage(player, amountOfPotions);
}
