
#pragma once

#include "../Players/Player.h"
//todo add virtual functions that other classes will use
class Event {
    protected:
    string result;
public:
   virtual  void applyEvent(Player& player)=0;
    /**
     * Gets the description of the event
     *
     * @return - the description of the event
    */
    virtual string getDescription() const;
    string getResult() const {
        return result;
    }
    virtual ~Event()=default;
};
