#include "MatamStory.h"
#include <memory>
using namespace std;
#include <string>

#define SNAIL "Snail"
#define SLIME "Slime"
#define BALROG "Balrog"
#define PACK "Pack"
#define SOLARECLIPSE "SolarEclipse"
#define POTIONSMERCHANT "PotionsMerchant"
#define WARRIOR "Warrior"
#define ARCHER "Archer"
#define MAGICIAN "Magician"
#define RESPONSIBLE "Responsible"
#define RISKTAKING "RiskTaking"

///helper fuctions for encounter:
std::unique_ptr<Encounter> collectPack(std::istream &eventsStream, const string &nextText);

std::unique_ptr<Encounter> getPack(std::istream &eventsStream, int &monstersLeft);

std::unique_ptr<Encounter> getSingleEncounter(const string &eventName);

std::unique_ptr<Event> getSingleEvent(const string &eventName);

///checks if the name contains only letters
bool notLegalName(const string &name) {
    for (char letter: name) {
        if ((letter >= 'a' && letter <= 'z') || (letter >= 'A' && letter <= 'Z'))
            continue;
        else
            return true;
    }
    return false;
}

///checks if string has numerical val
bool isInputNumber(const string &str) {
    for (char letter: str) {
        if (letter >= '0' && letter <= '9')
            continue;
        else
            return false;
    }
    return true;
}

///converts string to int
int srtingToNum(const string &str) {
    int num = 0;
    if (isInputNumber(str)) {
        for (char digit: str) {
            num = num * 10;
            num += digit - '0';
        }
        return num;
    }
    throw std::bad_cast();
}

///function that gets a string from the file
string extractWord(const string &str) {
    string word;
    string newWord;
    bool foundSpace = false;
    for (const char &ch: str) {
        if (!foundSpace) {
            if (ch != ' ')
                word += ch;
            else
                foundSpace = true;
        } else
            newWord += ch;
    }
    word = newWord;
    return word;
}

///function to check if the pack is legal
///and then it put the monsters in a pack or throw an error
std::unique_ptr<Encounter> collectPack(std::istream &eventsStream, const string &nextText) {
    if (!isInputNumber(nextText)) {
        throw std::runtime_error("Invalid Events File: nextText is not a number.");
    }
    int elementsInPack = srtingToNum(nextText);
    if (elementsInPack < 2) {
        throw std::runtime_error("Invalid Events File: Pack must contain at least 2 entities.");
    }
    std::unique_ptr<Encounter> newPack = getPack(eventsStream, elementsInPack);

    if (elementsInPack != 0)
        throw (std::runtime_error("Invalid Events File"));
    return newPack;
}

std::unique_ptr<Encounter> getPack(std::istream &eventsStream, int &monstersLeft) {
    std::string word;
    std::vector<std::unique_ptr<Encounter> > packVector;

    while (!eventsStream.eof() && monstersLeft > 0) {
        eventsStream >> word;
        --monstersLeft;
        ///if there is a subpack
        if (word == PACK) {
            std::string nextText;
            eventsStream >> nextText;
            packVector.push_back(std::move(collectPack(eventsStream, nextText)));
        } else {
            ///entering single encounter to the pack
            std::unique_ptr<Encounter> encounter = getSingleEncounter(word);

            if (encounter) {
                packVector.push_back(std::move(encounter));
            } else {
                throw std::runtime_error("Invalid Events File");
            }
        }
    }

    return std::unique_ptr<Encounter>(new Pack(packVector));
}

std::unique_ptr<Encounter> getSingleEncounter(const string &eventName) {
    if (eventName == SNAIL) {
        return std::make_unique<Monster>(Monster::Snail());
    }
    if (eventName == SLIME) {
        return std::make_unique<Monster>(Monster::Slime());
    }
    if (eventName == BALROG) {
        return std::make_unique<Balrog>();
    }
    return nullptr;
}

///this function handle the case if the event is not pack
std::unique_ptr<Event> getSingleEvent(const string &eventName) {
    std::unique_ptr<Event> newEvent = std::move(getSingleEncounter(eventName));
    if (newEvent) {
        return newEvent;
    } else if (eventName == POTIONSMERCHANT) {
        return std::unique_ptr<Event>(new PotionMerchant());
    } else if (eventName == SOLARECLIPSE) {
        return std::unique_ptr<Event>(new SolarEclipse());
    } else throw std::runtime_error("Invalid Events File");
}


MatamStory::MatamStory(std::istream &eventsStream, std::istream &playersStream) {
    /*====================Reading events======================*/
    string eventName;
    string theNextText;
    while (!eventsStream.eof()) {
        eventsStream >> eventName;
        if (eventName == PACK) {
            eventsStream >> theNextText;
            events.push_back(std::move(collectPack(eventsStream, theNextText)));
        } else {
            events.push_back(std::move(getSingleEvent(eventName)));
        }
    }
    if (events.size() < 2) {
        throw std::runtime_error("Invalid Events File");
    }


    /*===== creating characters =====*/
    CharachterFactory makeCharacter;
    JobFactory makeJob;
    while (!playersStream.eof()){
        string playerName;
    string jobName;
    string characterName;
    if (!(playersStream >> playerName >> jobName >> characterName)) {
        throw std::runtime_error("Invalid Events File");
    } else {
        std::shared_ptr<Character> character_ptr = makeCharacter.charachterCreator(characterName);
        std::shared_ptr<Job> job_ptr = makeJob.jobCreator(jobName);
        if (character_ptr == nullptr || job_ptr == nullptr) {
            throw (std::runtime_error("Invalid Events File"));
        } else if (notLegalName(playerName)) {
            throw (std::runtime_error("Invalid Events File"));
        } else if (playerName.length() < 3 || playerName.length() > 15) {
            throw std::runtime_error("Invalid Events File");
        }
        Player player(playerName, job_ptr, character_ptr);
        std::shared_ptr<Player> Player_ptr = std::make_shared<Player>(player);
        playersInSortedOrder.push_back(Player_ptr);
        playersInUnsortedOrder.push_back(Player_ptr);
    }
}
        makePlayersSorted();
        if (this->playersInUnsortedOrder.size() > 6 || this->playersInUnsortedOrder.size() < 2) {
            throw (std::runtime_error("Invalid Players File"));
        }


    /*============================================*/


    this->m_turnIndex = 1;
}


void MatamStory::playTurn(Player& player) {

    printTurnDetails(m_turnIndex, player, *events[(m_turnIndex - 1) % events.size()]);
    events[(m_turnIndex - 1) % events.size()]->applyEvent(player);
    printTurnOutcome(events[(m_turnIndex - 1) % events.size()]->getResult());
    m_turnIndex++;
}


void MatamStory::playRound() {
    printRoundStart();

    // Iterate over players in unsorted order (as in the second implementation)
    for (const std::shared_ptr<Player>& player : playersInUnsortedOrder) {
        if (!(player->PlayerKnockOut())) {
            // Play a turn for the player
            playTurn(*player);
        }
    }

    // Sort players at the end of the round
    makePlayersSorted();

    printRoundEnd();

    printLeaderBoardMessage();

    int player_idx = 1;
    for (const std::shared_ptr<Player>& player : playersInSortedOrder) {
        printLeaderBoardEntry(player_idx, *player);
        player_idx++;
    }

    printBarrier();
}

bool MatamStory::isGameOver() const {
    for (const std::shared_ptr<Player>& player : playersInSortedOrder) {
        if(player->getPlayerData().level>=10)
            return true;
    }
    for (const std::shared_ptr<Player>& player : playersInSortedOrder) {
        if (!player->getPlayerData().isKnockedOut) {
            return false;
        }
    }
    return true;
}


void MatamStory::play() {
    printStartMessage();

    /*=========================================================================================*/

    int player_idx = 1;
    for (const std::shared_ptr<Player>& player : playersInSortedOrder) {
        printStartPlayerEntry(player_idx, *player);
        player_idx++;
    }
    printBarrier();

    while (!isGameOver()) {
        playRound();
    }

    printGameOver();

    for (const std::shared_ptr<Player> &player: playersInSortedOrder) {
        if (player->getPlayerData().level == 10) {
            printWinner(*player);
            return;
        }
    }
    printNoWinners();
}



////////////////////////helper function///////////////////////////
std::shared_ptr<const Player> MatamStory::getWinner() const {
    // Initially, assume there's no winner
    std::shared_ptr<const Player> winner = nullptr;

    // Check the winning condition
    for (const auto& player : playersInUnsortedOrder) {
        if (player->getLevel() == 10) {
            return player; // Return the shared pointer to the winning player
        }
    }

    return nullptr; // Return nullptr if no player has won
}
//////////////////////////////////////////////////////////////////
