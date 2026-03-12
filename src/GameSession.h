#pragma once
#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <cctype>
#include <algorithm>
#include "Deck.h"
#include "IBondRule.h"
#include "IScoringRule.h"
#include "IShopSystem.h"
#include "IWinCondition.h"

// =============================================================
// GameSession — INVARIANT
// Mengelola urutan fase game loop. Tidak boleh berubah.
// Seluruh logika (bond, scoring, shop, win, registry display)
// di-inject dari luar. GameSession tidak include ModifierFactory.
// =============================================================
class GameSession {
private:
    Deck                          deck;
    std::vector<IBondRule*>       bondRules;
    IScoringRule*                 scoringRule;
    IShopSystem*                  shopSystem;
    IWinCondition*                winCondition;
    int                           currentRound;
    int                           scoreGoal;
    bool                          isRunning;

    // ── helper ──────────────────────────────────────────
    void DisplayHand(const std::vector<std::unique_ptr<ICard>>& hand) {
        for (int i = 0; i < (int)hand.size(); i++) {
            if (hand[i])
                std::cout << " " << i+1 << ". " << hand[i]->GetName()
                          << "  (J:" << hand[i]->GetJourney()
                          << " C:" << hand[i]->GetCycle() << ")\n";
        }
    }

    int GetIntInput() {
        int val;
        while (!(std::cin >> val)) {
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            std::cout << "Input tidak valid. Coba lagi: ";
        }
        std::cin.ignore(1000, '\n');
        return val;
    }

    // ── Phase 1: Draw hand ───────────────────────────────
    void Phase_DrawHand(std::vector<std::unique_ptr<ICard>>& hand, int target) {
        auto newCards = deck.DrawHand(target - (int)hand.size());
        for (auto& c : newCards) hand.push_back(std::move(c));
    }

    // ── Phase 2–5: Player Action ─────────────────────────
    bool Phase_PlayerAction(std::vector<std::unique_ptr<ICard>>& hand,
                             int& currentScore, int maxSelect) {
        std::cout << "\nPilih Aksi:\n";
        std::cout << " 1. Play Cards (Maks " << maxSelect << ")\n";
        std::cout << " 2. Discard & Draw\n";
        std::cout << " 3. Lihat Deck & Bond Registry (Free)\n";
        std::cout << "Pilihan: ";
        int action = GetIntInput();

        if (action == 1) {
            std::cout << "Masukkan nomor kartu yang dimainkan (contoh: 1234): ";
            std::string input;
            std::getline(std::cin, input);

            std::vector<std::unique_ptr<ICard>> selected;
            for (char ch : input) {
                if (!isdigit(ch)) continue;
                int idx = ch - '0' - 1;
                if (idx >= 0 && idx < (int)hand.size() && hand[idx] && (int)selected.size() < maxSelect)
                    selected.push_back(std::move(hand[idx]));
            }
            if (selected.empty()) { std::cout << "Tidak ada kartu dipilih.\n"; return false; }

            // Phase 3 — Apply all bond rules
            std::cout << "\n--- CHECKING BONDS ---\n";
            for (auto* bond : bondRules)
                bond->Apply(selected);
            std::cout << "----------------------\n";

            // Phase 4 — Compute & display score
            scoringRule->DisplayScore(selected);
            int gain = scoringRule->ComputeScore(selected);

            // Phase 5 — Update score
            currentScore += gain;
            std::cout << "[SCORE UPDATE] +" << gain << " | Total: " << currentScore << "/" << scoreGoal << "\n";

            hand.erase(std::remove(hand.begin(), hand.end(), nullptr), hand.end());
            Phase_DrawHand(hand, 8);
            return true;

        } else if (action == 2) {
            std::cout << "Masukkan nomor kartu yang di-discard: ";
            std::string input;
            std::getline(std::cin, input);

            int count = 0;
            for (char ch : input) {
                if (!isdigit(ch)) continue;
                int idx = ch - '0' - 1;
                if (idx >= 0 && idx < (int)hand.size() && hand[idx]) {
                    hand[idx].reset();
                    count++;
                }
            }
            if (count > 0) {
                hand.erase(std::remove(hand.begin(), hand.end(), nullptr), hand.end());
                Phase_DrawHand(hand, 8);
                std::cout << ">> Discard " << count << " kartu, draw kartu baru.\n";
                return true;
            }
            return false;

        } else if (action == 3) {
            // View registry — dipanggil via IShopSystem agar GameSession
            // tidak perlu tahu ModifierFactory sama sekali
            deck.GetRegistry().ShowAllPrototypes();
            shopSystem->ShowRegistry();
            std::cout << "\nTekan Enter untuk kembali...";
            std::cin.get();
            return false; // free action
        }
        return false;
    }

    // ── Phase 6: Check Win/Lose ──────────────────────────
    bool Phase_CheckResult(int currentScore) {
        if (winCondition->IsWin(currentScore, scoreGoal)) {
            std::cout << "\n[WIN] Goal tercapai! Score: " << currentScore << "/" << scoreGoal << "\n";
            return true;
        }
        std::cout << "\n[GAME OVER] Score: " << currentScore << "/" << scoreGoal << "\n";
        isRunning = false;
        return false;
    }

    // ── Phase 7: Shop ────────────────────────────────────
    void Phase_Shop() {
        shopSystem->OpenShop(deck.GetRegistry());
    }

    // ── Phase 8: Advance Round ───────────────────────────
    void Phase_AdvanceRound() {
        scoreGoal = winCondition->NextGoal(scoreGoal);
        currentRound++;
        std::cout << "\n=== ROUND " << currentRound << " DIMULAI | GOAL: " << scoreGoal << " ===\n";
        std::cout << "Tekan Enter untuk lanjut...";
        std::cin.get();
    }

public:
    GameSession(std::vector<IBondRule*> bonds,
                IScoringRule*           scoring,
                IShopSystem*            shop,
                IWinCondition*          win)
        : bondRules(bonds), scoringRule(scoring),
          shopSystem(shop), winCondition(win),
          currentRound(1), scoreGoal(6000), isRunning(true) {}

    // ==========================================================
    // INVARIANT PHASE ORDER — urutan ini TIDAK BOLEH berubah
    // ==========================================================
    void Start() {
        while (isRunning) {
            int currentScore = 0;
            int actionPoints = 3;

            // Phase 1 — Draw hand awal
            std::vector<std::unique_ptr<ICard>> hand;
            Phase_DrawHand(hand, 8);

            // Loop aksi dalam satu round
            while (actionPoints > 0 && !winCondition->IsWin(currentScore, scoreGoal)) {
                std::cout << "\n========================================\n";
                std::cout << " ROUND " << currentRound
                          << " | GOAL: "  << scoreGoal
                          << " | SCORE: " << currentScore
                          << " | AKSI: "  << actionPoints << "\n";
                std::cout << "========================================\n";

                DisplayHand(hand);

                // Phase 2–5 — Player action
                bool usedPoint = Phase_PlayerAction(hand, currentScore, 4);
                if (usedPoint) actionPoints--;
            }

            // Phase 6 — Cek hasil akhir round
            bool won = Phase_CheckResult(currentScore);

            if (won) {
                Phase_Shop();        // Phase 7
                Phase_AdvanceRound(); // Phase 8
            }
        }

        std::cout << "\n=== GAME OVER ===\n";
    }
};
