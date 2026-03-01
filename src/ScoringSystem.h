#pragma once
#include <vector>
#include <memory>
#include "Cards/ICard.h"

class ScoringSystem {
public:
    static int CalculateScore(const std::vector<std::unique_ptr<ICard>>& playedCards) {
        int totalJ = 0;
        int totalC = 0;
        for (const auto& card : playedCards) {
            totalJ += card->GetJourney();
            totalC += card->GetCycle();
        }
        return totalJ * totalC;
    }
    static void DisplayScore(const std::vector<std::unique_ptr<ICard>>& playedCards);
};