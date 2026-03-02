#include "ModifierFactory.h"
#include <iostream>

bool ModifierFactory::HasCard(const std::vector<std::unique_ptr<ICard>>& selectedCards, std::string name) {
    for (const auto& card : selectedCards) {
        if (card->GetName() == name) return true;
    }
    return false;
}

void ModifierFactory::ApplyBonds(std::vector<std::unique_ptr<ICard>>& selectedCards) {
    bool hasJanus     = HasCard(selectedCards, "Janus");
    bool hasTalanton  = HasCard(selectedCards, "Talanton");
    bool hasOronyx    = HasCard(selectedCards, "Oronyx");
    bool hasGeorios   = HasCard(selectedCards, "Georios");
    bool hasPhagousa  = HasCard(selectedCards, "Phagousa");
    bool hasAquila    = HasCard(selectedCards, "Aquila");
    bool hasKephale   = HasCard(selectedCards, "Kephale");
    bool hasCerces    = HasCard(selectedCards, "Cerces");
    bool hasMnestia   = HasCard(selectedCards, "Mnestia");
    bool hasNikador   = HasCard(selectedCards, "Nikador");
    bool hasThanatos  = HasCard(selectedCards, "Thanatos");
    bool hasZegreus   = HasCard(selectedCards, "Zegreus");
    bool hasDemiurge  = HasCard(selectedCards, "Demiurge");

    std::cout << "\n--- CHECKING BONDS ---\n";

    // 1. Inisialisasi Counter untuk setiap Faksi
    int countFate = 0;       // Janus, Talanton, Oronyx
    int countFoundation = 0; // Georios, Phagousa, Aquila
    int countCalamity = 0;   // Nikador, Thanatos, Zegreus
    int countCreation = 0;   // Kephale, Cerces, Mnestia

    for (const auto& card : selectedCards) {
        std::string name = card->GetName();
        
        if (name == "Janus" || name == "Talanton" || name == "Oronyx") countFate++;
        else if (name == "Georios" || name == "Phagousa" || name == "Aquila") countFoundation++;
        else if (name == "Nikador" || name == "Thanatos" || name == "Zegreus") countCalamity++;
        else if (name == "Kephale" || name == "Cerces" || name == "Mnestia") countCreation++;
    }

    // Terapkan Buff untuk masing-masing faksi jika minimal ada 2 kartu
    for (const auto& card : selectedCards) {
        std::string name = card->GetName();
        int oldJ = card->GetJourney();
        int oldC = card->GetCycle();
        bool buffed = false;

        // Faksi: TITAN FATE
        if ((name == "Janus" || name == "Talanton" || name == "Oronyx") && countFate >= 2) {
            card->SetCycle(oldC + (countFate * 2));
            std::cout << " * [FATE] " << name << " | J: " << oldJ << "->" << card->GetJourney() << " | C: " << oldC << "->" << card->GetCycle() << "\n";
            buffed = true;
        }
        // Faksi: TITAN FOUNDATION
        else if ((name == "Georios" || name == "Phagousa" || name == "Aquila") && countFoundation >= 2) {
            card->SetJourney(oldJ + (countFoundation * 20));
            std::cout << " * [FOUNDATION] " << name << " | J: " << oldJ << "->" << card->GetJourney() << " | C: " << oldC << "->" << card->GetCycle() << "\n";
            buffed = true;
        }
        // Faksi: TITAN CALAMITY
        else if ((name == "Nikador" || name == "Thanatos" || name == "Zegreus") && countCalamity >= 2) {
            card->SetJourney(oldJ + (countCalamity * 15));
            card->SetCycle(oldC + (countCalamity * 1));
            std::cout << " * [CALAMITY] " << name << " | J: " << oldJ << "->" << card->GetJourney() << " | C: " << oldC << "->" << card->GetCycle() << "\n";
            buffed = true;
        }
        // Faksi: TITAN CREATION
        else if ((name == "Kephale" || name == "Cerces" || name == "Mnestia") && countCreation >= 2) {
            card->SetJourney(oldJ + (countCreation * 10));
            card->SetCycle(oldC + (countCreation * 1));
            std::cout << " * [CREATION] " << name << " | J: " << oldJ << "->" << card->GetJourney() << " | C: " << oldC << "->" << card->GetCycle() << "\n";
            buffed = true;
        }
    }

    std::cout << "---------------------------\n";

    if (hasJanus && hasMnestia) {
        std::cout << ">>> Okhema Elders (+4 Cycle for all cards)\n";
        for (const auto& card : selectedCards) {
            int oldCycle = card->GetCycle();
            card->SetCycle(oldCycle + 4);
            
            std::cout << " * " << card->GetName() 
                      << " | Cycle: " << oldCycle << " -> " << card->GetCycle() << "\n";
        }
    }

    if (hasPhagousa && hasTalanton) {
        std::cout << ">>> Dux Kaisar (+40 Journey for all cards)\n";
        for (const auto& card : selectedCards) {
            int oldJourney = card->GetJourney();
            card->SetJourney(oldJourney + 40);
            
            std::cout << " * " << card->GetName() 
                      << " | Journey: " << oldJourney << " -> " << card->GetJourney() << "\n";
        }
    }

    if (hasMnestia && hasZegreus) {
        std::cout << ">>> Mother And Daughter (+20 Journey and +2 Cycle for all cards)\n";
        for (const auto& card : selectedCards) {
            int oldJourney = card->GetJourney();
            int oldCycle = card->GetCycle();
            card->SetJourney(oldJourney + 20);
            card->SetCycle(oldCycle + 2);
            
            std::cout << " * " << card->GetName() 
                      << " | Journey: " << oldJourney << " -> " << card->GetJourney() 
                      << " | Cycle: " << oldCycle << " -> " << card->GetCycle() << "\n";
        }
    }

    if (hasDemiurge && hasKephale) {
        std::cout << ">>> The cycle beginning (+500 Journey for Kephale)\n";
        for (const auto& card : selectedCards) {
            if (card->GetName() == "Kephale") {
                int oldJourney = card->GetJourney();
                card->SetJourney(oldJourney + 500);
                
                std::cout << " * " << card->GetName() 
                          << " | Journey: " << oldJourney << " -> " << card->GetJourney() << "\n";
            }
        }
    }

    if (hasKephale && hasNikador) {
        std::cout << ">>> BOND ACTIVE: The Heated Rivalry <<<\n";
        for (const auto& card : selectedCards) {
            std::string name = card->GetName();
            if (name == "Kephale" || name == "Nikador") {
                int oldJ = card->GetJourney();
                card->SetJourney(oldJ + 100);
                std::cout << " * " << name << " (Foundation Buff) | Journey: " << oldJ << " -> " << card->GetJourney() << "\n";
            }
        }
    }

    if (hasGeorios && hasOronyx && hasKephale) {
        std::cout << ">>> BOND ACTIVE: The Three Nameless <<<\n";
        for (const auto& card : selectedCards) {
            std::string name = card->GetName();
            if (name == "Georios" || name == "Oronyx" || name == "Kephale") {
                int oldJ = card->GetJourney();
                card->SetJourney(oldJ + 100);
                std::cout << " * " << name << " (Foundation Buff) | Journey: " << oldJ << " -> " << card->GetJourney() << "\n";
            }
        }
    }

    if (hasOronyx && hasGeorios && hasDemiurge && hasKephale) {
        std::cout << ">>> ULTIMATE BOND: Deicide Symphony!!! <<<\n";
        for (const auto& card : selectedCards) {
            std::string name = card->GetName();
            if (name == "Kephale") {
                int oldJ = card->GetJourney();
                card->SetJourney(oldJ * 3);
                std::cout << " * KEPHALE (Ascended) | Journey: " << oldJ << " -> " << card->GetJourney() << "\n";
            } else {
                int oldC = card->GetCycle();
                card->SetCycle(oldC + 3);
                std::cout << " * " << name << " (Symphony Buff) | Cycle: " << oldC << " -> " << card->GetCycle() << "\n";
            }
        }
    }

    std::cout << "----------------------\n";
}