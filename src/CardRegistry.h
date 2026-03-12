#pragma once
#include <vector>
#include <memory>
#include <string>
#include <iostream>
#include <random>
#include "BaseCard.h"

class CardRegistry {
private:
    std::vector<std::unique_ptr<ICard>> prototypes;

public:
    CardRegistry() {
        // TITAN FATE
        prototypes.push_back(std::make_unique<BaseCard>("Janus",    1,   6));
        prototypes.push_back(std::make_unique<BaseCard>("Talanton", 5,   4));
        prototypes.push_back(std::make_unique<BaseCard>("Oronyx",   15,  3));
        // TITAN FOUNDATION
        prototypes.push_back(std::make_unique<BaseCard>("Georios",  75,  1));
        prototypes.push_back(std::make_unique<BaseCard>("Phagousa", 50,  1));
        prototypes.push_back(std::make_unique<BaseCard>("Aquila",   40,  2));
        // TITAN CREATION
        prototypes.push_back(std::make_unique<BaseCard>("Kephale",  100, 1));
        prototypes.push_back(std::make_unique<BaseCard>("Cerces",   5,   6));
        prototypes.push_back(std::make_unique<BaseCard>("Mnestia",  40,  3));
        // TITAN CALAMITY
        prototypes.push_back(std::make_unique<BaseCard>("Nikador",  80,  1));
        prototypes.push_back(std::make_unique<BaseCard>("Thanatos", 40,  2));
        prototypes.push_back(std::make_unique<BaseCard>("Zegreus",  10,  4));
        // SPECIAL
        prototypes.push_back(std::make_unique<BaseCard>("Demiurge", 100, 6));
    }

    ICard* CreateRandomCard() const {
        static std::mt19937 gen(std::random_device{}());
        std::uniform_int_distribution<> dist(0, (int)prototypes.size() - 1);
        return prototypes[dist(gen)]->Clone();
    }

    void UpgradePrototype(const std::string& name, int journeyBuff, int cycleBuff) {
        for (auto& proto : prototypes) {
            if (proto->GetName() == name) {
                int oldJ = proto->GetJourney();
                int oldC = proto->GetCycle();
                proto->SetJourney(oldJ + journeyBuff);
                proto->SetCycle(oldC + cycleBuff);
                std::cout << "\n[UPGRADE] " << name
                          << " | Journey: " << oldJ << " -> " << proto->GetJourney()
                          << " | Cycle: "   << oldC << " -> " << proto->GetCycle() << "\n";
                return;
            }
        }
        std::cout << "Card not found: " << name << "\n";
    }

    void ShowAllPrototypes() const {
        std::cout << "\n--- MASTER CARD REGISTRY ---\n";
        for (size_t i = 0; i < prototypes.size(); ++i) {
            std::cout << " " << i+1 << ". " << prototypes[i]->GetName()
                      << "  [J: " << prototypes[i]->GetJourney()
                      << " | C: " << prototypes[i]->GetCycle() << "]\n";
        }
        std::cout << "----------------------------\n";
    }
};
