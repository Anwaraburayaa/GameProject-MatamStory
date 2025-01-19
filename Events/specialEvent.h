#ifndef SPECIALEVENT_H
#define SPECIALEVENT_H

#include <string>
#include "Event.h"


class SpecialEvent : public Event {
public:
    SpecialEvent() = default;
};


class SolarEclips : public SpecialEvent {
public:
    SolarEclips();
    void applyEvent(Character& character) override;
    std::string getEventInfon() const override;
};


class PotionsMerchant : public SpecialEvent {
public:
    PotionsMerchant();
    void applyEvent(Character& character) override;
    std::string getEventInfon() const override;
};

#endif
