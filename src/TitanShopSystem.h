#pragma once
#include "IShopSystem.h"
#include "ModifierFactory.h"
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <random>

class TitanShopSystem : public IShopSystem {
private:
    static constexpr int PACK_OPTIONS = 3;

    static std::mt19937& RNG() {
        static std::mt19937 gen(std::random_device{}());
        return gen;
    }

    int GetInput(int min, int max) {
        int val;
        while (true) {
            if (std::cin >> val && val >= min && val <= max) {
                std::cin.ignore(1000, '\n');
                return val;
            }
            std::cout << "Input tidak valid. Coba lagi: ";
            std::cin.clear();
            std::cin.ignore(1000, '\n');
        }
    }

    void KremnosPack(CardRegistry& registry) {
        std::cout << "\nMembuka Kremnos Pack...\n";
        std::vector<std::unique_ptr<ICard>> opts;
        for (int i = 0; i < PACK_OPTIONS; i++)
            opts.emplace_back(registry.CreateRandomCard());

        for (int i = 0; i < PACK_OPTIONS; i++)
            std::cout << " " << i+1 << ". " << opts[i]->GetName()
                      << "  (J:" << opts[i]->GetJourney()
                      << " C:" << opts[i]->GetCycle() << ")\n";

        std::cout << "Pilih kartu yang di-upgrade (1-" << PACK_OPTIONS << "): ";
        int pick = GetInput(1, PACK_OPTIONS);

        std::string name = opts[pick-1]->GetName();
        int jBuff = (name=="Kephale") ? 10 : 20;
        registry.UpgradePrototype(name, jBuff, 1);
        std::cout << ">> " << name << " prototype upgraded!\n";
    }

    void OkhemaPack() {
        std::cout << "\nMembuka Okhema Pack...\n";
        std::vector<std::string> bonds = {
            "FATE","FOUNDATION","CALAMITY","CREATION",
            "GROVE ACADEMY","OKHEMA ELDERS","DUX KAISAR",
            "MOTHER DAUGHTER","CYCLE BEGINNING","HEATED RIVALRY",
            "THREE NAMELESS","DEICIDE SYMPHONY"
        };
        std::shuffle(bonds.begin(), bonds.end(), RNG());

        for (int i = 0; i < PACK_OPTIONS; i++)
            std::cout << " " << i+1 << ". " << bonds[i] << "\n";

        std::cout << "Pilih bond yang di-upgrade (1-" << PACK_OPTIONS << "): ";
        int pick = GetInput(1, PACK_OPTIONS);
        ModifierFactory::UpgradeBondScaling(bonds[pick-1]);
        std::cout << ">> Bond diperkuat!\n";
    }

public:
    void OpenShop(CardRegistry& registry) override {
        std::cout << "\n==============================\n";
        std::cout << "         TITAN SHOP\n";
        std::cout << "==============================\n";
        std::cout << " 1. Kremnos Pack (Card Upgrade)\n";
        std::cout << " 2. Okhema Pack  (Bond Upgrade)\n";
        std::cout << " 3. Skip Shop\n";
        std::cout << "Pilihan: ";
        int choice = GetInput(1, 3);
        if      (choice == 1) KremnosPack(registry);
        else if (choice == 2) OkhemaPack();
        else std::cout << ">> Shop dilewati.\n";
    }

    // GameSession memanggil ini saat player pilih View — tanpa tahu ModifierFactory
    void ShowRegistry() override {
        ModifierFactory::ShowBondRegistry();
    }
};
