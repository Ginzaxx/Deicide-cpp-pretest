#pragma once
#include <vector>
#include <memory>
#include "ICard.h"

class CardRegistry
{
private:
    std::vector<std::unique_ptr<ICard>> prototypes;

public:
    CardRegistry();

    ICard* CreateRandomCard() const;
};