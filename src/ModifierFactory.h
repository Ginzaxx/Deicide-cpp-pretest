#pragma once
#include <vector>
#include <memory>
#include <string>
#include "Cards/ICard.h"

class ModifierFactory {
public:
    // Fungsi untuk memeriksa dan menerapkan efek ikatan
    static void ApplyBonds(std::vector<std::unique_ptr<ICard>>& selectedCards);
    
private:
    // Helper untuk mengecek apakah sebuah kartu ada di hand
    static bool HasCard(const std::vector<std::unique_ptr<ICard>>& selectedCards, std::string name);
};