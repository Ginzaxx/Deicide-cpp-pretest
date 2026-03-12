#pragma once
#include "IScoringRule.h"
#include <iostream>

// Rumus scoring: totalJourney * totalCycle
// MUTABLE — bisa diganti tanpa ubah GameSession
class DeicideScoringRule : public IScoringRule {
public:
    int ComputeScore(const std::vector<std::unique_ptr<ICard>>& cards) override {
        int totalJ = 0, totalC = 0;
        for (const auto& c : cards) {
            totalJ += c->GetJourney();
            totalC += c->GetCycle();
        }
        return totalJ * totalC;
    }

    // DisplayScore memanggil ComputeScore — tidak ada duplikasi kalkulasi
    void DisplayScore(const std::vector<std::unique_ptr<ICard>>& cards) override {
        int totalJ = 0, totalC = 0;
        std::cout << "\n--- CALCULATING SCORE ---\n";
        for (const auto& c : cards) {
            int j = c->GetJourney(), cy = c->GetCycle();
            std::cout << " >> " << c->GetName() << " (J:" << j << " C:" << cy << ")\n";
            totalJ += j;
            totalC += cy;
        }
        std::cout << "-------------------------\n";
        std::cout << "Total Journey  : " << totalJ << "\n";
        std::cout << "Total Cycle    : " << totalC << "\n";
        std::cout << "SCORE          : " << ComputeScore(cards) << "\n";
        std::cout << "-------------------------\n";
    }
};
