#ifndef SPECIALEVENT_H
#define SPECIALEVENT_H

#include <string>
#include "Character.h"

enum class EventType {
    SolarEclips,
    PotionsMerchant
};

class SpecialEvent {
public:
    virtual ~SpecialEvent() = default;
    virtual void applyEvent(Character& character) = 0;
    virtual std::string getEventInfo() const = 0;
    EventType getType() const { return type; }

protected:
    EventType type;
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
