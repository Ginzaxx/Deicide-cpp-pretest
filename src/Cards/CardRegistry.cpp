#include "CardRegistry.h" 
#include "BaseCard.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>
#include <cctype>

CardRegistry::CardRegistry()//factory
{
    prototypes.push_back(std::make_unique<BaseCard>("Janus", 1, 6));
    prototypes.push_back(std::make_unique<BaseCard>("Talanton", 5, 4));
    prototypes.push_back(std::make_unique<BaseCard>("Oronyx", 15, 3));
    prototypes.push_back(std::make_unique<BaseCard>("Georios", 75, 1));
    prototypes.push_back(std::make_unique<BaseCard>("Phagousa", 50, 1));
    prototypes.push_back(std::make_unique<BaseCard>("Aquila", 40, 2));
    prototypes.push_back(std::make_unique<BaseCard>("Kephale", 100, 1));
    prototypes.push_back(std::make_unique<BaseCard>("Cerces", 5, 6));
    prototypes.push_back(std::make_unique<BaseCard>("Mnestia", 40, 3));
    prototypes.push_back(std::make_unique<BaseCard>("Nikador", 80, 1));
    prototypes.push_back(std::make_unique<BaseCard>("Thanatos", 40, 2));
    prototypes.push_back(std::make_unique<BaseCard>("Zegreus", 10, 4));
    prototypes.push_back(std::make_unique<BaseCard>("Demiurge", 100, 6));

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