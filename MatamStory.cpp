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

std::unique_ptr<Encounter> collectPack(std::istream &eventsStream, const string &nextText) {
    if (!isInputNumber(nextText)) {
        throw std::runtime_error("Invalid Events File");
    }
    int elementsInPack = srtingToNum(nextText);
    if (elementsInPack < 2) {
        throw std::runtime_error("Invalid Events File");
    }
    std::unique_ptr<Encounter> newPack = getPack(eventsStream, elementsInPack);
    if (elementsInPack != 0) {
        throw std::runtime_error("Invalid Events File");}
    return newPack;
}

std::unique_ptr<Encounter> getPack(std::istream &eventsStream, int &monstersLeft) {
    std::string word;
    std::vector<std::unique_ptr<Encounter> > packVector;

    while (!eventsStream.eof() && monstersLeft > 0) {
        eventsStream >> word;
        monstersLeft--;

        if (word == PACK) {
            std::string nextText;
            eventsStream >> nextText;
            packVector.push_back(std::move(collectPack(eventsStream, nextText)));
        } else {
            std::unique_ptr<Encounter> encounter = getSingleEncounter(word);
            if (encounter) {
                packVector.push_back(std::move(encounter));
            } else {
                throw std::runtime_error("Invalid Events File");
            }
        }
    }

    return std::make_unique<Pack>(packVector);
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
    while (!playersStream.eof()) {
        string playerName;
        string jobName;
        string characterName;
        if (!(playersStream >> playerName >> jobName >> characterName)) {
            throw std::runtime_error("Invalid Players File");
        } else {
            std::shared_ptr<Character> character_ptr = makeCharacter.charachterCreator(characterName);
            std::shared_ptr<Job> job_ptr = makeJob.jobCreator(jobName);
            if (character_ptr == nullptr || job_ptr == nullptr) {
                throw (std::runtime_error("Invalid Players File"));
            } else if (notLegalName(playerName)) {
                throw (std::runtime_error("Invalid Players File"));
            } else if (playerName.length() < 3 || playerName.length() > 15) {
                throw std::runtime_error("Invalid Players File");
            }
            Player player(playerName, job_ptr, character_ptr);
            std::shared_ptr<Player> Player_ptr = std::make_shared<Player>(player);
            sortedPlayersVec.push_back(Player_ptr);
            unsortedPlayersVec.push_back(Player_ptr);
        }
    }
    sortPlayers();
    if (this->unsortedPlayersVec.size() > 6 || this->unsortedPlayersVec.size() < 2) {
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
        if (!player->getPlayerData().isKnockedOut) {
            // Play a turn for the player
            playTurn(*player);
        }else{
            for (auto it = playersInUnsortedOrder.begin(); it != playersInUnsortedOrder.end(); ++it) {
                 if (*it == player) {
                        playersInUnsortedOrder.erase(it);
                        return; 
        }
        }
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
    /*===== Check if there is a winner =====*/
    if (getWinner() != nullptr) {
        return true;
    }

    /*===== Check if all players are knocked out =====*/
    for (const auto& player : playersInSortedOrder) {
        if (!player->PlayerKnockOut()) {
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

    std::shared_ptr< const Player> winner = getWinner(playersInUnsortedOrder);
    if (winner) {
        printWinner(*winner);
    } else {
        printNoWinners();
    }
}



