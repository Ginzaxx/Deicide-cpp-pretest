#pragma once

// Interface untuk win/lose condition — MUTABLE: kondisi menang bisa diganti
class IWinCondition {
public:
    virtual bool IsWin(int currentScore, int scoreGoal)  = 0;
    virtual int  NextGoal(int currentGoal)               = 0;
    virtual ~IWinCondition() = default;
};
