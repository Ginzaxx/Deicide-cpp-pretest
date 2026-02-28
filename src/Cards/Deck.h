#pragma once
#include <vector>
#include <memory>
#include "CardRegistry.h"

class Deck
{
private:
    CardRegistry registry;

public:
    std::vector<std::unique_ptr<ICard>> DrawHand(int amount);
};