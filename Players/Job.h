#pragma once
#include <string>
#include "Player.h"
#ifndef JOB_H
#define JOB_H
using std::string;



class Job {
    protected:
    ///we will fill that later
    public:
    friend class Player;
    ///methods that is common for each job:
    ///getters for the default values
    virtual unsigned int getStartLevel()const {
        return 1;
    }
    virtual unsigned int getMaxHP()const {
        return 100;
    }
    virtual unsigned int getStartForce()const {
        return 5;
    }
    virtual unsigned int getStartCoins() const {
        return 10;
    }

};
class Archer : public Job {
    public:

};



#endif //JOB_H
