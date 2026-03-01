#pragma once
#include <vector>
#include <memory>
#include "Cards/Deck.h"

class RunSession {
private:
    Deck deck;
    int currentRound;
    int scoreGoal;
    bool isRunning;

public:
    RunSession();
    void Start(); // Memulai loop permainan (Ronde)
};