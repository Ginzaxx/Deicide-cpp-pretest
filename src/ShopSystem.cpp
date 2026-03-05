#include "ShopSystem.h"
#include "ModifierFactory.h"
#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <random>

// =============================
// STATIC RNG (Production Ready)
// =============================
static std::mt19937& GetRNG()
{
    static std::mt19937 gen(std::random_device{}());
    return gen;
}

ShopSystem::ShopSystem(CardRegistry& registry)
    : cardRegistry(registry)
{
}

// =============================
// SHOP ENTRY
// =============================
void ShopSystem::OpenShop()
{
    std::cout << "\n==============================";
    std::cout << "\n        TITAN SHOP";
    std::cout << "\n==============================\n";
    std::cout << "1. Kremnos Pack (Card Upgrade)\n";
    std::cout << "2. Okhema Pack (Bond Upgrade)\n";
    std::cout << "Choice: ";

    int choice = GetValidatedInput(1, 2);

    if (choice == 1)
        OpenKremnosPack();
    else
        OpenOkhemaPack();
}

// =============================
// INPUT VALIDATION
// =============================
int ShopSystem::GetValidatedInput(int min, int max)
{
    int value;

    while (true)
    {
        if (std::cin >> value && value >= min && value <= max)
        {
            std::cin.ignore(1000, '\n');
            return value;
        }

        std::cout << "Invalid input. Try again: ";
        std::cin.clear();
        std::cin.ignore(1000, '\n');
    }
}

// =============================
// KREMNOS PACK (CARD UPGRADE)
// =============================
void ShopSystem::OpenKremnosPack()
{
    std::cout << "\nOpening Kremnos Pack...\n";

    std::vector<std::unique_ptr<ICard>> options;

    for (int i = 0; i < PACK_OPTIONS; ++i)
        options.emplace_back(cardRegistry.CreateRandomCard());

    for (int i = 0; i < PACK_OPTIONS; ++i)
    {
        std::cout << i + 1 << ". "
                  << options[i]->GetName()
                  << " (J: " << options[i]->GetJourney()
                  << ", C: " << options[i]->GetCycle() << ")\n";
    }

    std::cout << "Choose card to upgrade: ";
    int pick = GetValidatedInput(1, PACK_OPTIONS);

    UpgradeCardPrototype(options[pick - 1]->GetName());

    std::cout << ">> Card upgraded permanently!\n";
}

// =============================
// OKHEMA PACK (BOND UPGRADE)
// =============================
void ShopSystem::OpenOkhemaPack()
{
    std::cout << "\nOpening Okhema Pack...\n";

    std::vector<std::string> bondOptions = {
        "FATE",
        "FOUNDATION",
        "CALAMITY",
        "CREATION",
        "OKHEMA ELDERS",
        "DUX KAISAR",
        "MOTHER DAUGHTER",
        "CYCLE BEGINNING",
        "HEATED RIVALRY",
        "THREE NAMELESS",
        "DEICIDE SYMPHONY"
    };

    std::shuffle(bondOptions.begin(), bondOptions.end(), GetRNG());

    for (int i = 0; i < PACK_OPTIONS; ++i)
    {
        std::cout << i + 1 << ". " << bondOptions[i] << "\n";
    }

    std::cout << "Choose bond to upgrade: ";
    int pick = GetValidatedInput(1, PACK_OPTIONS);

    UpgradeBond(bondOptions[pick - 1]);

    std::cout << ">> Bond upgraded permanently!\n";
}

// =============================
// CARD UPGRADE SYSTEM
// =============================
void ShopSystem::UpgradeCardPrototype(const std::string& cardName)
{
    int journeyBuff = 20;
    int cycleBuff = 1;

    // Future flexibility per-card
    if (cardName == "Kephale")
        journeyBuff = 10;

    cardRegistry.UpgradePrototype(cardName, journeyBuff, cycleBuff);
}

// =============================
// BOND UPGRADE SYSTEM
// =============================
void ShopSystem::UpgradeBond(const std::string& bondName)
{
    ModifierFactory::UpgradeBondScaling(bondName);

    std::cout << "Bond " << bondName << " has grown stronger!\n";
}