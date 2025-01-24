///in this file we will have a class monster
///and we will have pack class
///and monsters classes if needed(depending on if they are changeable or not, we might create only for part of them not all
///the class encounter should inherit from event, also it should have a protected struct containing the data of encounter

#pragma once

#include "Event.h"
#include <vector>
#include <string>

using std::vector;
using std::string;

#ifndef ENCOUNTER_H
#define ENCOUNTER_H

class Encounter : public Event {
protected:
    struct EncounterData {
        string monsterName;
        unsigned int combatPower;
        unsigned int loot;
        unsigned int damage;
    };

    void applyEvent(Player &player) override;

    EncounterData data;

public:
    Encounter() = default;
    ///this function is made to be used at the end of the applyEvent for barlog esspicially
    virtual void SpecialEffect() {}


    ///adding getters for encounter data
    EncounterData getEncounterData() const {
        return data;
    }

    EncounterData getEncounterData() {
        return data;
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
        data.monsterName = monsterName;
        data.combatPower = combatPower;
        data.loot = loot;
        data.damage = damage;
    }
    static Monster Snail() {
        return {"Snail", 5, 2, 10};
    }
    static Monster Slime() {
        return {"Slime", 12, 5, 25};
    }
    std::string getDescription() const override;

};


class Balrog : public Monster {
public:
    ///empty c'tor
    Balrog() {
        data.monsterName = "Balrog";
        data.combatPower = 15;
        data.loot = 100;
        data.damage = 9001;
    }
    ///after every event the compact power of balrog duplicates
    void SpecialEffect() override;
};

class Pack : public Encounter {
private:
    vector<std::unique_ptr<Encounter>> encounters;

public:
    Pack() = default;

    explicit Pack(vector<std::unique_ptr<Encounter>> &encounters) {
        this->encounters = std::move(encounters);
        data.monsterName = "Pack";
        data.combatPower = 0;
        data.loot = 0;
        data.damage = 0;

        for (std::unique_ptr<Encounter> &encounter: this->encounters) {
           data.combatPower += encounter->getCombatPower();
            data.loot += encounter->getLoot();
           data.damage += encounter->getDamage();
        }
    }
    void sync();

    void SpecialEffect() override;

    string getDescription() const override;

};

#endif
