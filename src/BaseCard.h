#pragma once
#include "ICard.h"

class BaseCard : public ICard {
private:
    std::string name;
    int journey;
    int cycle;
public:
    BaseCard(std::string name, int journey, int cycle)
        : name(name), journey(journey), cycle(cycle) {}

    ICard*      Clone()      const override { return new BaseCard(*this); }
    int         GetJourney() const override { return journey; }
    int         GetCycle()   const override { return cycle; }
    std::string GetName()    const override { return name; }
    void        SetJourney(int j) override  { journey = j; }
    void        SetCycle(int c)   override  { cycle = c; }
};
