#include "RunSession.h"
#include "ScoringSystem.h"
#include "ModifierFactory.h"
#include "ShopSystem.h"
#include <iostream>
#include <string>
#include <cctype>
#include <algorithm>

RunSession::RunSession() 
    : currentRound(1), scoreGoal(6000), isRunning(true) {}

void RunSession::Start() {
    while (isRunning) {
        int maxSelect = 4;
        int currentScore = 0;
        int actionPoints = 3; 
        
        // Ambil hand awal (8 kartu)
        auto hand = deck.DrawHand(8);

        // Loop Aksi (Selama masih ada kesempatan dan skor belum mencapai target)
        while (actionPoints > 0 && currentScore < scoreGoal) {
            std::cout << "\n========================================";
            std::cout << "\n ROUND " << currentRound << " | GOAL: " << scoreGoal;
            std::cout << "\n CURRENT SCORE: " << currentScore;
            std::cout << "\n ACTIONS LEFT: " << actionPoints;
            std::cout << "\n========================================\n";
            
            // Tampilkan Hand
            for (int i = 0; i < (int)hand.size(); ++i) {
                if (hand[i] != nullptr) {
                    std::cout << i + 1 << ". " << hand[i]->GetName() 
                              << " (J: " << hand[i]->GetJourney() << ", C: " << hand[i]->GetCycle() << ")\n";
                }
            }

            std::cout << "\nChoose Action:\n";
            std::cout << "1. Play Cards (Max " << maxSelect << ")\n";
            std::cout << "2. Discard & Draw\n";
            std::cout << "3. View Deck & Bonds (Free Action)\n";
            std::cout << "Choice: ";
            
            int action;
            if (!(std::cin >> action)) { // Proteksi jika input bukan angka
                std::cin.clear();
                std::cin.ignore(1000, '\n');
                continue;
            }
            std::cin.ignore(1000, '\n'); // Bersihkan buffer

            if (action == 1) { // --- LOGIKA PLAY ---
                std::cout << "Input card numbers to PLAY (e.g., 1234): ";
                std::string input;
                std::getline(std::cin, input);

                std::vector<std::unique_ptr<ICard>> selectedCards;
                // Kita kumpulkan index yang valid
                for (char c : input) {
                    if (!isdigit(c)) continue;
                    int idx = c - '0' - 1;
                    if (idx >= 0 && idx < (int)hand.size() && hand[idx] != nullptr && selectedCards.size() < maxSelect) {
                        selectedCards.push_back(std::move(hand[idx]));
                    }
                }

                if (!selectedCards.empty()) {
                    ModifierFactory::ApplyBonds(selectedCards);
                    int handScore = ScoringSystem::CalculateScore(selectedCards);
                    ScoringSystem::DisplayScore(selectedCards);
                    
                    currentScore += handScore;
                    actionPoints--;

                    // Bersihkan nullptr dari hand dan isi ulang
                    hand.erase(std::remove(hand.begin(), hand.end(), nullptr), hand.end());
                    auto newCards = deck.DrawHand(8 - (int)hand.size());
                    for(auto& nc : newCards) hand.push_back(std::move(nc));
                }
            } 
            else if (action == 2) { // --- LOGIKA DISCARD ---
                std::cout << "Input card numbers to DISCARD: ";
                std::string input;
                std::getline(std::cin, input);

                int discardCount = 0;
                for (char c : input) {
                    if (!isdigit(c)) continue;
                    int idx = c - '0' - 1;
                    if (idx >= 0 && idx < (int)hand.size() && hand[idx] != nullptr) {
                        hand[idx].reset(); 
                        discardCount++;
                    }
                }

                if (discardCount > 0) {
                    hand.erase(std::remove(hand.begin(), hand.end(), nullptr), hand.end());
                    auto newCards = deck.DrawHand(discardCount);
                    for(auto& nc : newCards) hand.push_back(std::move(nc));
                    
                    std::cout << ">> Discarded " << discardCount << " cards and drew new ones.\n";
                    actionPoints--;
                }
            } 
            else if (action == 3) { // --- LOGIKA VIEW (FREE) ---
                CardRegistry tempRegistry;
                tempRegistry.ShowAllPrototypes();
                ModifierFactory::ShowBondRegistry(); 
                
                std::cout << "\nPress Enter to return to game...";
                std::cin.get();
                // Tidak mengurangi actionPoints
            }
        }

        // --- CEK HASIL AKHIR RONDE ---
        if (currentScore >= scoreGoal) {
            std::cout << "\n[WIN] Goal reached! Score: " << currentScore << "\n";
            scoreGoal = (int)(scoreGoal * 1.5);
            currentRound++;
            ShopSystem shop(deck.GetRegistry()); 
            shop.OpenShop();
            std::cout << "Press Enter to move to next round...";
            std::cin.get();
        } else {
            std::cout << "\n[GAME OVER] Final Score: " << currentScore << "/" << scoreGoal << "\n";
            isRunning = false;
        }
    }
}