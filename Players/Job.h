#pragma once
#include <string>

//#include "Events/Encounter.h"
//#include "Player.h"
#ifndef JOB_H
#define JOB_H
using std::string;
///need methods for compactpower and special events also get job string for the factory

class Encounter;
class Player;

class Job {
protected:
    virtual void caculateCompactPower(Player &player);

    ///this function we add to see the behavior of each job under this special event
    virtual int solarEclipseEvent(Player &player);

    ///this function we add for the encounter when faces a player
    virtual void fight(Player &player, const Encounter &encounter) {
    }

    virtual void calculateDamage(Player &player, const unsigned int &damage);

public:
    virtual ~Job() = default;

    friend class Player;
    ///methods that is common for each job:
    ///getters for the default values
    virtual unsigned int getStartLevel() const {
        return 1;
    }

    virtual unsigned int getMaxHP() const {
        return 100;
    }

    virtual unsigned int getStartForce() const {
        return 5;
    }

    virtual unsigned int getStartCoins() const {
        return 10;
    }

    ///function to get the string for job, we will use that in the factory :)
    virtual string getJobName() const =0;
};

class Archer : public Job {
public:
    Archer() = default;

    string getJobName() const override;

    unsigned int getStartCoins() const override {
        return 20; ///as menthoned archer gets 20 coins in beggining.
    }
};

class Magician : public Job {
private:
    int solarEclipseEvent(Player &player) override;

public:
    Magician() = default;

    string getJobName() const override;
};

class Warrior : public Job {
private:
    void fight(Player &player, const Encounter &encounter) override;

    void caculateCompactPower(Player &player) override;

public:
    Warrior() = default;

    static const int DAMAGE_FIGHT = 10;

    string getJobName() const override;

    unsigned int getMaxHP() const override {
        return 150;
    }
};


#endif //JOB_H
