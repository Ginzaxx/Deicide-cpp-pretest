#pragma once
#include <vector>
#include <memory>
#include <string>
#include "Cards/ICard.h"

class ModifierFactory {
public:
    static void ApplyBonds(std::vector<std::unique_ptr<ICard>>& selectedCards);
    static void UpgradeBondScaling(const std::string& bondName);
    static void ShowBondRegistry(); // Fungsi baru
private:
    static bool HasCard(const std::vector<std::unique_ptr<ICard>>& selectedCards, std::string name);
};