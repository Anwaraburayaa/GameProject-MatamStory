#include "SpecialEvent.h"
#include "Player.h"

void SolarEclips::applyEvent(Player& player) {
    if (player.getJob()->isMagical()) {
        player.gainLoot(1);
    } else {
        player.claculateDamage(1);
    }
}

void PotionsMerchant::applyEvent(Player& player) {
    unsigned int maxHealth = (player.getJob()->getJobName() == "Warrior") ? 150 : 100;
    unsigned int currentHealth = player.getHealthPoints();
    unsigned int healthNeeded = maxHealth - currentHealth;

    if (healthNeeded > 0) {
        if (player.getJob()->isResponsible()) {
            unsigned int potionsToBuy = healthNeeded / 10;
            unsigned int totalCost = potionsToBuy * 10;

            if (player.getCoins() >= totalCost) {
                player.gainLoot(-totalCost);
                player.claculateDamage(-healthNeeded);
            } else {
                unsigned int affordablePotions = player.getCoins() / 10;
                player.gainLoot(-affordablePotions * 10);
                player.claculateDamage(-(affordablePotions * 10));
            }
        }
        else if (player.getHealthPoints() < 50) {
            if (player.getCoins() >= 10) {
                player.gainLoot(-10);
                player.claculateDamage(-10);
            }
        }
    }
}

