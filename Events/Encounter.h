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
    virtual void SpecialEffect(){}

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
    Balrog() : Monster("Balrog", 15, 100, 9001) {
    }

    unsigned int calculate(const string &property) const override {
        if (property == "combatPower") return Monster::calculate(property) + 2;
        return Monster::calculate(property);
    }
};

class Pack : public Encounter {
private:
    vector<Encounter *> members;

public:
    Pack(const vector<Encounter *> &members);

    unsigned int calculate(const string &property) const override;

    std::string getDescription() const override;
};

#endif
