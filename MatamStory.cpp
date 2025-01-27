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
bool legalName(const string &name) {
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
    std::unique_ptr<Encounter> newPack = std::move(getPack(eventsStream, elementsInPack));
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
            auto encounter = std::move(getSingleEncounter(word));
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

MatamStory::MatamStory(std::istream &eventsStream, std::istream &playersStream) {
    // string eventName;
    // string nextText;
    // std::string line;
    // eventsStream >> eventName;
    // if (eventName == PACK) {
    //     eventsStream >> nextText;
    //     events.push_back(std::move(autherizePack(eventsStream, nextText)));
    // } else {
    //     events.push_back(std::move(getSingleEvent(eventName)));
    // }
    //
    // if (events.size() < 2)
    //     throw (std::runtime_error("Invalid Events File"));


    /*===== TODO: Open and read events file =====*/

    /*==========================================*/


    /*===== TODO: Open and Read players file =====*/

    /*============================================*/


    this->m_turnIndex = 1;
}


void MatamStory::playTurn(Player &player) {
    /**
     * Steps to implement (there may be more, depending on your design):
     * 1. Get the next event from the events list
     * 2. Print the turn details with "printTurnDetails"
     * 3. Play the event
     * 4. Print the turn outcome with "printTurnOutcome"
    */

    m_turnIndex++;
}

void MatamStory::playRound() {
    printRoundStart();

    /*===== TODO: Play a turn for each player =====*/

    /*=============================================*/

    printRoundEnd();

    printLeaderBoardMessage();

    /*===== TODO: Print leaderboard entry for each player using "printLeaderBoardEntry" =====*/

    /*=======================================================================================*/

    printBarrier();
}

bool MatamStory::isGameOver() const {
    /*===== TODO: Implement the game over condition =====*/
    return false; // Replace this line
    /*===================================================*/
}

void MatamStory::play() {
    printStartMessage();
    /*===== TODO: Print start message entry for each player using "printStartPlayerEntry" =====*/

    /*=========================================================================================*/
    printBarrier();

    while (!isGameOver()) {
        playRound();
    }

    printGameOver();
    /*===== TODO: Print either a "winner" message or "no winner" message =====*/

    /*========================================================================*/
}
