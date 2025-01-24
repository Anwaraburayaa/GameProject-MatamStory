
#pragma once
#include <string>
using std::string;

#include "../Players/Player.h"
class Player;
class Event {
    protected:
     std::string result;
public:
   virtual  void applyEvent(Player& player)=0;
    /**
     * Gets the description of the event
     *
     * @return - the description of the event
    */
    virtual string getDescription() const=0;
    string getResult() const {
        return result;
    }
    virtual ~Event()=default;
};
