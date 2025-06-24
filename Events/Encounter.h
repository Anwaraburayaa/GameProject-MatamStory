
#pragma once

#include "Event.h"
#include <vector>
#include <string>
#include <memory>


using std::vector;
using std::string;


class Encounter : public Event {
protected:
    struct EncounterData {
        string monsterName;
        unsigned int combatPower;
        unsigned int loot;
        unsigned int damage;
      const unsigned int enounterNum=1;
    };
virtual unsigned int getEncounterSize() const {
    return 1;
}


    EncounterData encounterData;

public:
    void applyEvent(Player &player) override;
    Encounter() = default;
    ///this function is made to be used at the end of the applyEvent for barlog esspicially
    virtual void makeSpecialEffect() {}


    ///adding getters for encounter data
    EncounterData getEncounterData() const {
        return encounterData;
    }

    EncounterData getEncounterData() {
        return encounterData;
    }

    unsigned int getCombatPower() const;
    unsigned int getLoot() const;
    unsigned int getDamage() const;
};

class Monster : public Encounter {
public:
    Monster() = default;
    Monster(const Monster &other) = default;
    Monster(const string &monsterName, const unsigned int &combatPower, const unsigned int &loot,
            const unsigned int &damage) {
        encounterData.monsterName = monsterName;
        encounterData.combatPower = combatPower;
        encounterData.loot = loot;
        encounterData.damage = damage;
    }
    std::string getDescription() const override;
};

class Snail : public Monster {
public:
    Snail() : Monster("Snail", 5, 2, 10) {}
};

class Slime : public Monster {
public:
    Slime() : Monster("Slime", 12, 5, 25) {}
};


class Balrog : public Monster {
public:
    ///empty c'tor
    Balrog() {
        encounterData.monsterName = "Balrog";
        encounterData.combatPower = 15;
        encounterData.loot = 100;
        encounterData.damage = 9001;
    }
    ///after every event the compact power of balrog duplicates
    void makeSpecialEffect() override;
};

class Pack : public Encounter {
private:
    vector<std::unique_ptr<Encounter>> encounters;

public:
    Pack() = default;

    explicit Pack(vector<std::unique_ptr<Encounter>> &encounters) {
        this->encounters = std::move(encounters);
        encounterData.monsterName = "Pack";
        encounterData.combatPower = 0;
        encounterData.loot = 0;
        encounterData.damage = 0;

        for (std::unique_ptr<Encounter> &encounter: this->encounters) {
            encounterData.combatPower += encounter->getCombatPower();
            encounterData.loot += encounter->getLoot();
            encounterData.damage += encounter->getDamage();
        }
    }
    unsigned int getEncounterSize() const override;
    void updateStatus();

    void makeSpecialEffect() override;

    string getDescription() const override;
    friend Encounter;

};
