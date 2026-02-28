#include "Deck.h"

std::vector<std::unique_ptr<ICard>> Deck::DrawHand(int amount)
{
    std::vector<std::unique_ptr<ICard>> hand;

    for (int i = 0; i < amount; i++)
    {
        hand.push_back(std::unique_ptr<ICard>(registry.CreateRandomCard()));
    }

    return hand;
}