///in this file we will have a class monster
///and we will have pack class
///and monsters classes if needed(depending on if they are changeable or not, we might create only for part of them not all
///the class encounter should inherit from event, also it should have a protected struct containing the data of encounter

#include "Event.h"
#include <vector>

using std::vector;

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
    virtual void isMagical();

public:
    Encounter() = default;


    virtual unsigned int calculate(const string &property) const = 0;

    unsigned int getCombatPower() const { return calculate("combatPower"); }
    unsigned int getLoot() const { return calculate("loot"); }
    unsigned int getDamage() const { return calculate("damage"); }
};

class Monster : public Encounter {
protected:
    string monsterName;
    unsigned int combatPower;
    unsigned int loot;
    unsigned int damage;

public:
    Monster() = default;
    Monster(const Monster &monster) = default;

    Monster(const string &monsterName,
            const unsigned int &combatPower,
            const unsigned int &loot,
            const unsigned int &damage)
        : monsterName(monsterName), combatPower(combatPower), loot(loot), damage(damage) {}

    unsigned int calculate(const string &property) const override {
        if (property == "combatPower") return combatPower;
        if (property == "loot") return loot;
        if (property == "damage") return damage;
        return 0;
    }
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
    Pack(const vector<Encounter*> &members) : members(members) {}

    unsigned int calculate(const string &property) const override {
        unsigned int total = 0;
        for (const auto& member : members) {
            total += member->calculate(property);
        }
        return total;
    }
};

#endif