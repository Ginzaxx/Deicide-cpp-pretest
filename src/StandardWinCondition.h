#pragma once
#include "IWinCondition.h"

// Win jika score >= goal; goal naik 1.5x setiap round
// Ini MUTABLE — scaling bisa diubah tanpa ubah GameSession
class StandardWinCondition : public IWinCondition {
public:
    bool IsWin(int currentScore, int scoreGoal) override {
        return currentScore >= scoreGoal;
    }
    int NextGoal(int currentGoal) override {
        return (int)(currentGoal * 1.5);
    }
};
