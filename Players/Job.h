#pragma once
#include <string>
#include "Player.h"
#ifndef JOB_H
#define JOB_H
using std::string;
///need methods for compactpower and special events also get job string for the factory
class Player;

class Job {
   // class Player;
protected:
    ///we will fill that later
public:
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


  virtual void caculateCompactPower(Player& player);

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
public:
    Magician() = default;

    string getJobName() const override;
};

class Warrior : public Job {
private:
public:
    Warrior() = default;

    string getJobName() const override;

    unsigned int getMaxHP() const override {
        return 150;
    }
};


#endif //JOB_H
