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

    virtual bool isSpecial();

public:
    Encounter() = default;
    virtual ~Encounter() = default;
    virtual std::string getDescription() const = 0;
    virtual unsigned int calculate(const string &property) const = 0;

    unsigned int getCombatPower() const { return calculate("combatPower"); }
    unsigned int getLoot() const { return calculate("loot"); }
    unsigned int getDamage() const { return calculate("damage"); }
};

class Monster : public Encounter {
protected:
    EncounterData data;

public:
    Monster() = default;
    Monster(const string &monsterName, const unsigned int &combatPower, const unsigned int &loot, const unsigned int &damage);

    std::string getDescription() const override {
        return monsterName + " (power " + std::to_string(combatPower) +
               ", loot " + std::to_string(loot) +
               ", damage " + std::to_string(damage) + ")";
    }

    unsigned int calculate(const string &property) const override;
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
    Balrog() : Monster("Balrog", 15, 100, 9001) {}

    unsigned int calculate(const string &property) const override {
        if (property == "combatPower") return Monster::calculate(property) + 2;
        return Monster::calculate(property);
    }
};

class Pack : public Encounter {
private:
    vector<Encounter*> members;

public:
    Pack(const vector<Encounter*> &members);
    unsigned int calculate(const string &property) const override;
    std::string getDescription() const override;
};

#endif
