#pragma once

#include "Event.h"
#include <vector>

using std::vector;

#ifndef ENCOUNTER_H
#define ENCOUNTER_H
///in this file we will have a class monster
///and we will have pack class
///and monsters classes if needed(depending on if they are changeable or not, we might create only for part of them not all
///the class encounter should inherit from event, also it should have a protected struct containing the data of encounter


class Encounter: public Event{
protected:
    struct EncounterData {
        string monsterName;
        unsigned int combatPower;
        unsigned int loot;
        unsigned int damage;
    };
    void applyEvent(Player &player) override;
    /*
     * this function checks if anything magical happens at the event
     */
    virtual void isMagical();
    ///here we should add the other methods that monster and pack should inherit
    public:
    Encounter()=default;
    ///getters to the date & virtual functions if needed
    unsigned int getCombatPower() const;
    unsigned int getLoot() const;
    unsigned int getDamage() const;

};

class Monster: public Encounter {
    public:
    Monster()=default;
    Monster(const Monster& monster)=default;
    ///todo add implementation later
    Monster(const string &monsterName,
          const unsigned int &combatPower,
          const unsigned int &loot,
          const unsigned int &damage);
};
///todo add fields tommowrow
class snail: public Monster {};
class Slime: public Monster {};
class Balrog : public Monster {};
///in pack sence we have more that one monster we will use vector of encounters
class Pack : public Encounter {};




#endif //ENCOUNTER_H
