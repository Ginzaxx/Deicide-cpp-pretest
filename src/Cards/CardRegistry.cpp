#include "CardRegistry.h" 
#include "BaseCard.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>
#include <cctype>

CardRegistry::CardRegistry()//factory
{
    prototypes.push_back(std::make_unique<BaseCard>("Janus", 10, 1));
    prototypes.push_back(std::make_unique<BaseCard>("Talanton", 15, 2));
    prototypes.push_back(std::make_unique<BaseCard>("Oronyx", 8, 3));
    prototypes.push_back(std::make_unique<BaseCard>("Georios", 12, 1));
    prototypes.push_back(std::make_unique<BaseCard>("Phagousa", 20, 2));
    prototypes.push_back(std::make_unique<BaseCard>("Aquila", 5, 4));
    prototypes.push_back(std::make_unique<BaseCard>("Kephale", 7, 3));
    prototypes.push_back(std::make_unique<BaseCard>("Cerces", 9, 2));
    prototypes.push_back(std::make_unique<BaseCard>("Mnestia", 14, 1));
    prototypes.push_back(std::make_unique<BaseCard>("Nikador", 6, 5));
    prototypes.push_back(std::make_unique<BaseCard>("Thanatos", 18, 2));
    prototypes.push_back(std::make_unique<BaseCard>("Zegreus", 11, 3));
    prototypes.push_back(std::make_unique<BaseCard>("Demiurge", 13, 2));

    std::srand((unsigned)std::time(nullptr));
}

ICard* CardRegistry::CreateRandomCard() const
{
    int index = rand() % prototypes.size();
    return prototypes[index]->Clone();
}

void CardRegistry::ShowAllPrototypes() const
{
    std::cout << "\n--- MASTER CARD REGISTRY ---\n";
    for (size_t i = 0; i < prototypes.size(); ++i)
    {
        std::cout << i + 1 << ". " << prototypes[i]->GetName() 
                  << " [Journey: " << prototypes[i]->GetJourney() 
                  << " | Cycle: " << prototypes[i]->GetCycle() << "]\n";
    }
    std::cout << "---------------------------\n";
}