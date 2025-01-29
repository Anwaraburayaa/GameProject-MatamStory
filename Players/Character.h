//
// Created by anwar on 1/18/2025.
//
#pragma once

#include <string>
#include <memory>
#include "Job.h"
//#include "Player.h"
using std::string;
class Player;
//class Job;
class Character {

    public:
    ///we have to add function for special event sence each charechter acts with it deffrintly
    virtual int potionMerchantEvent(Player &player,const std::shared_ptr<Job> &job) = 0;
    virtual string getCharacterName() const = 0;

};
class Responsible : public Character {
    public:
    int potionMerchantEvent(Player &player,const std::shared_ptr<Job> &job) override;
    string getCharacterName() const override;

};
class RiskTaking : public Character {
    public:
    int potionMerchantEvent(Player &player,const std::shared_ptr<Job> &job) override;
    string getCharacterName() const override;

};