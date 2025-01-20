#pragma once

#include <string>
#include <memory>
#include "Character.h"
#include "Job.h"
#include <cassert>
using std::string;
///forward declaration to the class job
class Job;
class Player {
private:
    struct PlayerData {
        string name;
      static const int MaxLevel = 10;
        unsigned int level = 1;
        unsigned int force = 5;
        unsigned int combatPower = force * level;
        unsigned int coins = 10;
        unsigned int currentHP = 100;
        bool isKnockedOut = false;
    };

    PlayerData data;
    std::shared_ptr<Job> job;
    std::shared_ptr<Character> character;
 ///to update the compact power after raising the level
    void caculateCompactPower();

public:

    Player() = default;

    /*we also should have a real ctor that takes job and chatechter*/
    Player(const string &name, const std::shared_ptr<Job> &job,
           const std::shared_ptr<Character> &character) {
        this->data.name = name;
        this->job = job;
        this->character = character;
        data.coins = job->getStartCoins();
        data.force = job->getStartForce();
        data.level = job->getStartLevel();
        data.currentHP = job->getMaxHP();
        job->caculateCompactPower(*this);


    }
 ///TO SOLVE THE PROBLEM OF THE DATA BEING NOT ACESSABLE
 PlayerData& getPlayerData() { return data; }
 const PlayerData& getPlayerData() const { return data; }
    /**
     * Gets the description of the player
     *
     * @return - description of the player
    */
    string getDescription() const;

    /**
     * Gets the name of the player
     *
     * @return - name of the player
    */
    string getName() const; ///done

    /**
     * Gets the current level of the player
     *
     * @return - level of the player
    */
    int getLevel() const; ///done

    ///function to get job
    std::shared_ptr<Job> getJob() const { return job; }
    ///function to get job charachter
    std::shared_ptr<Character> getCharacter() const { return character; }


    /**
     * Gets the of force the player has
     *
     * @return - force points of the player
    */
    int getForce() const; ///done

    /**
     * Gets the amount of health points the player currently has
     *
     * @return - health points of the player
    */
    int getHealthPoints() const; ///done

    /**
     * Gets the amount of coins the player has
     *
     * @return - coins of the player
    */
    unsigned int getCoins() const; ///done

    ///mehtods that we need currently:
    ///1.function to chech if the player is knocked out
    void isPlayerKnockedOut();

    ///2.function to enable the player to gain loot:
    void gainLoot();

    ///3.function to level up the player
    void raisLevel();
};
