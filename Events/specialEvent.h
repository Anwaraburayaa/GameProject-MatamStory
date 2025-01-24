#ifndef SPECIALEVENT_H
#define SPECIALEVENT_H

#include <string>
#include "Event.h"

class SpecialEvent : public Event {
public:
    SpecialEvent() = default;
};

class SolarEclipse : public SpecialEvent {
public:
    void applyEvent(Player &player) override;
    std::string getDescription() const override;
};

class PotionMerchant : public SpecialEvent {
public:
    void applyEvent(Player &player) override;
    std::string getDescription() const override;
};


#endif
