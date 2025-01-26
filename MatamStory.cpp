
#include "MatamStory.h"

#include <memory>

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
///helper fuctions for encounter

bool legalName(const string &name) {
    for (char letter: name) {
        if ((letter >= 'a' && letter <= 'z') || (letter >= 'A' && letter <= 'Z'))
            continue;
        else
            return true;
    }
    return false;
}
bool isInputNumber(const string &string) {
    for (char letter: string) {
        if (letter >= '0' && letter <= '9')
            continue;
        else
            return false;
    }
    return true;
}
 int srtingToNum(const string &string) {
    int num=0;
    if(isInputNumber(string)){
        for (char digit: string) {
            num = num*10;
            num +=digit-'0';
        }
        return num;

    }
    throw std::bad_cast();
}



MatamStory::MatamStory(std::istream& eventsStream, std::istream& playersStream) {

    /*===== TODO: Open and read events file =====*/

    /*==========================================*/


    /*===== TODO: Open and Read players file =====*/

    /*============================================*/


    this->m_turnIndex = 1;
}

void MatamStory::playTurn(Player& player) {

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
