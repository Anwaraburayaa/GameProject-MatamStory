

#pragma once

#include <string>
#include <memory>
#include "Character.h"
#include "Job.h"
#include <cassert>
using std::string;

class Player {

private:
 struct PlayerData {
  string name;
  const int MaxLevel=10;
  unsigned int level=1;
  unsigned int force = 5;
  unsigned int combatPower = force * level;
  unsigned int coins = 10;
  unsigned int currentHP = 100;
  bool isKnockedOut = false;

 };
 PlayerData data;

///do the charecter factory and then add a shwred ptr to it
///keep it private!!

 std::shared_ptr<Job> job;
 std::shared_ptr<Character> character;

public:
 Player()=default;
 /*we also should have a real ctor that takes job and chatechter*/
 //TODO: add the c'tor after writhing the headers!

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

 ///functions to get job
  std::shared_ptr<Job> getJob() const { return job; }


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
    int getCoins() const;

 ///mehtods that we need currently:
 ///1.function to chech if the player is knocked out
 bool isPlayerKnockedOut() const;
 ///2.function to enable the player to gain loot:
 void gainLoot();
 ///3.function to level up the player
 void raisLevel();
};
