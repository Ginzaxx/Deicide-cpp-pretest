#pragma once
#include <vector>
#include <memory>
#include "ICard.h"

// Interface untuk scoring — MUTABLE: rumus bisa diganti tanpa ubah GameSession
class IScoringRule {
public:
    virtual int  ComputeScore(const std::vector<std::unique_ptr<ICard>>& cards) = 0;
    virtual void DisplayScore(const std::vector<std::unique_ptr<ICard>>& cards) = 0;
    virtual ~IScoringRule() = default;
};
