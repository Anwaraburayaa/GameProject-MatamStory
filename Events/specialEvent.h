#ifndef SPECIALEVENT_H
#define SPECIALEVENT_H

#include <string>
#include "Event.h"


class SpecialEvent : public Event {
public:
    SpecialEvent() = default;
};


class SolarEclips : public SpecialEvent {
    void applyEvent(Player& player) override;
    string getDescription() const override;
};


class PotionsMerchant : public SpecialEvent {
    void applyEvent(Player& player) override;
    string getDescription() const override;
};

#endif
