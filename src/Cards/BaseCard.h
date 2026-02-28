#pragma once
#include "ICard.h"

class BaseCard : public ICard
{
private:
    std::string name;
    int journey;
    int cycle;

public:
    BaseCard(std::string name, int journey, int cycle);

    ICard* Clone() const override;

    int GetJourney() const override;
    int GetCycle() const override;
    std::string GetName() const override;
};