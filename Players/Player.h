#pragma once

#include <string>
#include <memory>
#include "Character.h"
#include "Job.h"
#include "Events/Encounter.h"
#include <cassert>
using std::string;
class Character;
class Encounter;


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

        ///function for the player when choosing to buy potion to change his data
        void drinkPotion();
    };

    PlayerData data;
    std::shared_ptr<Job> job;
    std::shared_ptr<Character> character;

    ///to update the compact power after raising the level
    void caculateCompactPower();

    bool applyEvent(const Encounter &encounter);

    ///method to use during the SolarEclipse-Event
    int solarEclipseEvent();

    ///method to use during the PotionMerchant-Event
    int potionMerchantEvent();

    ///we have to friend these classes to access their fields
    friend class Encounter;

    friend class SolarEclipse;

    friend class PotionMerchant;

public:
    Player() = default;

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

    ///getters for the PlayerData
    PlayerData &getPlayerData() { return data; }
    const PlayerData &getPlayerData() const { return data; }


    ///in case if losing to an encounter we need this function to take the damage
    void claculateDamage(const unsigned int &damage);

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
    string getName() const;

    /**
     * Gets the current level of the player
     *
     * @return - level of the player
    */
    int getLevel() const;

    ///function to get job
    std::shared_ptr<Job> getJob() const { return job; }
    ///function to get job character
    std::shared_ptr<Character> getCharacter() const { return character; }


    /**
     * Gets the of force the player has
     *
     * @return - force points of the player
    */
    int getForce() const;

    /**
     * Gets the amount of health points the player currently has
     *
     * @return - health points of the player
    */
    int getHealthPoints() const;

    /**
     * Gets the amount of coins the player has
     *
     * @return - coins of the player
    */
    unsigned int getCoins() const;


    ///function to check if the player is knocked out
    void isPlayerKnockedOut();

    ///function to enable the player to gain loot:
    void gainLoot(const unsigned int loot);

    ///function to level up the player
    void raisLevel();


    ///operators overload for player :
    bool operator<(const Player &other) const;
    Player &operator=(const Player &other);

};
