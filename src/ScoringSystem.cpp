#include "ScoringSystem.h"
#include <iostream>

void ScoringSystem::DisplayScore(const std::vector<std::unique_ptr<ICard>>& playedCards)
{
    int totalJourney = 0;
    int totalCycle = 0;

    std::cout << "\n--- CALCULATING SCORE ---\n";

    for (const auto& card : playedCards)
    {
        // Mengambil data dari interface ICard
        int j = card->GetJourney();
        int c = card->GetCycle();

        std::cout << ">> " << card->GetName() << " (J: " << j << ", C: " << c << ")\n";

        totalJourney += j;
        totalCycle += c;
    }

    // Rumus utama permainan
    int finalScore = totalJourney * totalCycle;

    std::cout << "------------------------\n";
    std::cout << "Total Journey : " << totalJourney << "\n";
    std::cout << "Total Multiplier (Cycle) : " << totalCycle << "\n";
    std::cout << "FINAL SCORE   : " << finalScore << "\n";
    std::cout << "------------------------\n";
}