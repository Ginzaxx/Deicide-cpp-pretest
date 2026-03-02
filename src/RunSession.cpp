#include "RunSession.h"
#include "ScoringSystem.h"
#include "ModifierFactory.h"
#include <iostream>
#include <string>
#include <cctype>

RunSession::RunSession() 
    : currentRound(1), scoreGoal(300), isRunning(true) {}

void RunSession::Start() {
    while (isRunning) {
        int maxSelect = 4;
        int maxDraw = 8;
        auto hand = deck.DrawHand(maxDraw);

        std::cout << "\n--- ROUND " << currentRound << " ---";
        std::cout << "\nSCORE GOAL: " << scoreGoal << "\n";
        
        std::cout << "\n--- YOUR HAND ---\n";
        for (int i = 0; i < hand.size(); ++i) {
            std::cout << i + 1 << ". " << hand[i]->GetName() 
                    << " (J: " << hand[i]->GetJourney() 
                    << ", C: " << hand[i]->GetCycle() << ")\n";
        }

        std::cout << "\nInput card numbers (Max " << maxSelect << "): ";
        std::string input;
        std::getline(std::cin >> std::ws, input); // Mengambil input dengan membersihkan whitespace

        std::vector<std::unique_ptr<ICard>> selectedCards;
        for (int i = 0; i < input.length() && selectedCards.size() < maxSelect; i++) {
            if (!isdigit(input[i])) continue;

            int cardIdx = input[i] - '0';
            if (cardIdx > 0 && cardIdx <= (int)hand.size()) {
                if (hand[cardIdx - 1] != nullptr) {
                    selectedCards.push_back(std::move(hand[cardIdx - 1]));
                }
            }
        }

        ModifierFactory::ApplyBonds(selectedCards);

        // --- TAHAP PERHITUNGAN SKOR ---
        int playerChoicesScore = ScoringSystem::CalculateScore(selectedCards);
        ScoringSystem::DisplayScore(selectedCards);

        // Cek Kondisi Menang/Kalah
        if (playerChoicesScore >= scoreGoal) {
            std::cout << "\nWIN! Goal reached.\n";
            scoreGoal = (int)(scoreGoal * 1.5); // Naikkan goal x1.5
            currentRound++;
            std::cout << "Moving to Round " << currentRound << "...\n";
        } else {
            std::cout << "\nGAME OVER! Your score was too low.\n";
            isRunning = false; // Kembali ke menu utama
        }
    }
}