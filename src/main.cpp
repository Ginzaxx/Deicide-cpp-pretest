#include <iostream>
#include "Cards/Deck.h"

int main()
{
    Deck deck;

    auto hand = deck.DrawHand(8);

    int totalJourney = 0;
    int totalCycle = 0;

    std::cout << "=== HAND ===\n";

    for (const auto& card : hand)
    {
        std::cout << card->GetName()
                  << " | Journey: " << card->GetJourney()
                  << " | Cycle: " << card->GetCycle()
                  << "\n";

        totalJourney += card->GetJourney();
        totalCycle += card->GetCycle();
    }

    int finalScore = totalJourney * totalCycle;

    std::cout << "\nTotal Journey: " << totalJourney << "\n";
    std::cout << "Total Cycle: " << totalCycle << "\n";
    std::cout << "Final Score: " << finalScore << "\n";

    return 0;
}