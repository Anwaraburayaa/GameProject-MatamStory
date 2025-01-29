
#pragma once
#include <iostream>
#include <vector>
#include <algorithm>

#include "Players/Player.h"
#include "Events/Event.h"
#include "Utilities.h"
#include "Events/Encounter.h"
#include "specialEvent.h"
#include "Players/CharachterFactory.h"
#include "Players/JobFactory.h"

using std::vector;

class MatamStory {
private:
 unsigned int m_turnIndex;
 vector<std::shared_ptr<Player>> sortedPlayersVec;
 vector<std::shared_ptr<Player>> unsortedPlayersVec;
 vector<std::unique_ptr<Event>> events;
 void sortPlayers() {
  std::sort(sortedPlayersVec.begin(), sortedPlayersVec.end(),
            [](const std::shared_ptr<Player> &a, const std::shared_ptr<Player> &b) {
                return *b < *a;
            });
 }
    /**
     * Playes a single turn for a player
     *
     * @param player - the player to play the turn for
     *
     * @return - void
    */
    void playTurn(Player& player);

    /**
     * Plays a single round of the game
     *
     * @return - void
    */
    void playRound();

    /**
     * Checks if the game is over
     *
     * @return - true if the game is over, false otherwise
    */
    bool isGameOver() const;

public:
    /**
     * Constructor of MatamStory class
     *
     * @param eventsStream - events input stream (file)
     * @param playersStream - players input stream (file)
     *
     * @return - MatamStory object with the given events and players
     *
    */
    MatamStory(std::istream& eventsStream, std::istream& playersStream);





    /**
     * Plays the entire game
     *
     * @return - void
    */
    void play();

 std::shared_ptr<const Player> getWinner() const;


};
