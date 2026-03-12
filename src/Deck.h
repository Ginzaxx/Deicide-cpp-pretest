#pragma once
#include <vector>
#include <memory>
#include "CardRegistry.h"

class Deck {
private:
    CardRegistry registry;

public:
    std::vector<std::unique_ptr<ICard>> DrawHand(int amount) {
        std::vector<std::unique_ptr<ICard>> hand;
        for (int i = 0; i < amount; i++)
            hand.push_back(std::unique_ptr<ICard>(registry.CreateRandomCard()));
        return hand;
    }

    CardRegistry& GetRegistry() { return registry; }
};
