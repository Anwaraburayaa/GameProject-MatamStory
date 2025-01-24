#ifndef SPECIALEVENT_H
#define SPECIALEVENT_H

#include <string>
#include "Event.h"

class SpecialEvent : public Event {
public:
    SpecialEvent() = default;
    virtual ~SpecialEvent() = default;
    virtual void applyEvent(Player& player) = 0;
    virtual std::string getDescription() const = 0;
};

class SolarEclips : public SpecialEvent {
public:
    void applyEvent(Player& player) override;
    std::string getDescription() const override {
        return "SolarEclipse";
    }
};

class PotionsMerchant : public SpecialEvent {
public:
    void applyEvent(Player& player) override;
    std::string getDescription() const override {
        return "PotionsMerchant";
    }
};


#endif
