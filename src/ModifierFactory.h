#pragma once
#include "IBondRule.h"
#include "BondScaling.h"
#include <iostream>
#include <string>

// =============================================
// Helper
// =============================================
inline bool HasCard(const std::vector<std::unique_ptr<ICard>>& cards, const std::string& name) {
    for (const auto& c : cards)
        if (c && c->GetName() == name) return true;
    return false;
}

// =============================================
// Bond: TITAN FATE (Janus, Talanton, Oronyx)
// =============================================
class TitanFateBond : public IBondRule {
public:
    void Apply(std::vector<std::unique_ptr<ICard>>& cards) override {
        int count = 0;
        for (const auto& c : cards) {
            std::string n = c->GetName();
            if (n=="Janus"||n=="Talanton"||n=="Oronyx") count++;
        }
        if (count < 2) return;
        int buff = count * BondScaling::fateMultiplier;
        std::cout << ">>> TITAN FATE ACTIVE (+" << buff << " Cycle for FATE cards)\n";
        for (const auto& c : cards) {
            std::string n = c->GetName();
            if (n=="Janus"||n=="Talanton"||n=="Oronyx") {
                int old = c->GetCycle();
                c->SetCycle(old + buff);
                std::cout << " * " << n << " Cycle: " << old << " -> " << c->GetCycle() << "\n";
            }
        }
    }
};

// =============================================
// Bond: TITAN FOUNDATION (Georios, Phagousa, Aquila)
// =============================================
class TitanFoundationBond : public IBondRule {
public:
    void Apply(std::vector<std::unique_ptr<ICard>>& cards) override {
        int count = 0;
        for (const auto& c : cards) {
            std::string n = c->GetName();
            if (n=="Georios"||n=="Phagousa"||n=="Aquila") count++;
        }
        if (count < 2) return;
        int buff = count * BondScaling::foundationMultiplier;
        std::cout << ">>> TITAN FOUNDATION ACTIVE (+" << buff << " Journey for ALL cards)\n";
        for (const auto& c : cards) {
            int old = c->GetJourney();
            c->SetJourney(old + buff);
            std::cout << " * " << c->GetName() << " Journey: " << old << " -> " << c->GetJourney() << "\n";
        }
    }
};

// =============================================
// Bond: TITAN CALAMITY (Nikador, Thanatos, Zegreus)
// =============================================
class TitanCalamityBond : public IBondRule {
public:
    void Apply(std::vector<std::unique_ptr<ICard>>& cards) override {
        int count = 0;
        for (const auto& c : cards) {
            std::string n = c->GetName();
            if (n=="Nikador"||n=="Thanatos"||n=="Zegreus") count++;
        }
        if (count < 2) return;
        int buffJ = count * BondScaling::calamityJourneyMult;
        int buffC = count * BondScaling::calamityCycleMult;
        std::cout << ">>> TITAN CALAMITY ACTIVE (+" << buffJ << "J +" << buffC << "C for CALAMITY cards)\n";
        for (const auto& c : cards) {
            std::string n = c->GetName();
            if (n=="Nikador"||n=="Thanatos"||n=="Zegreus") {
                int oldJ = c->GetJourney(), oldC = c->GetCycle();
                c->SetJourney(oldJ + buffJ);
                c->SetCycle(oldC + buffC);
                std::cout << " * " << n << " J:" << oldJ << " -> " << c->GetJourney()
                          << " C:" << oldC << " -> " << c->GetCycle() << "\n";
            }
        }
    }
};

// =============================================
// Bond: TITAN CREATION (Kephale, Cerces, Mnestia)
// =============================================
class TitanCreationBond : public IBondRule {
public:
    void Apply(std::vector<std::unique_ptr<ICard>>& cards) override {
        int count = 0;
        for (const auto& c : cards) {
            std::string n = c->GetName();
            if (n=="Kephale"||n=="Cerces"||n=="Mnestia") count++;
        }
        if (count < 2) return;
        int buffJ = count * BondScaling::creationJourneyMult;
        int buffC = count * BondScaling::creationCycleMult;
        std::cout << ">>> TITAN CREATION ACTIVE (+" << buffJ << "J +" << buffC << "C for ALL cards)\n";
        for (const auto& c : cards) {
            int oldJ = c->GetJourney(), oldC = c->GetCycle();
            c->SetJourney(oldJ + buffJ);
            c->SetCycle(oldC + buffC);
            std::cout << " * " << c->GetName() << " J:" << oldJ << " -> " << c->GetJourney()
                      << " C:" << oldC << " -> " << c->GetCycle() << "\n";
        }
    }
};

// =============================================
// Bond: GROVE ACADEMY (Cerces + Aquila)
// =============================================
class GroveAcademyBond : public IBondRule {
public:
    void Apply(std::vector<std::unique_ptr<ICard>>& cards) override {
        if (!HasCard(cards,"Cerces") || !HasCard(cards,"Aquila")) return;
        int buff = BondScaling::groveAcademyCycleBuff;
        std::cout << ">>> GROVE ACADEMY (+" << buff << " Cycle ALL)\n";
        for (const auto& c : cards) {
            int old = c->GetCycle();
            c->SetCycle(old + buff);
            std::cout << " * " << c->GetName() << " Cycle: " << old << " -> " << c->GetCycle() << "\n";
        }
    }
};

// =============================================
// Bond: OKHEMA ELDERS (Janus + Mnestia)
// =============================================
class OkhemaEldersBond : public IBondRule {
public:
    void Apply(std::vector<std::unique_ptr<ICard>>& cards) override {
        if (!HasCard(cards,"Janus") || !HasCard(cards,"Mnestia")) return;
        int buff = BondScaling::okhemaEldersCycleBuff;
        std::cout << ">>> OKHEMA ELDERS (+" << buff << " Cycle ALL)\n";
        for (const auto& c : cards) {
            int old = c->GetCycle();
            c->SetCycle(old + buff);
            std::cout << " * " << c->GetName() << " Cycle: " << old << " -> " << c->GetCycle() << "\n";
        }
    }
};

// =============================================
// Bond: DUX KAISAR (Phagousa + Talanton)
// =============================================
class DuxKaisarBond : public IBondRule {
public:
    void Apply(std::vector<std::unique_ptr<ICard>>& cards) override {
        if (!HasCard(cards,"Phagousa") || !HasCard(cards,"Talanton")) return;
        int buff = BondScaling::duxKaisarJourneyBuff;
        std::cout << ">>> DUX KAISAR (+" << buff << " Journey ALL)\n";
        for (const auto& c : cards) {
            int old = c->GetJourney();
            c->SetJourney(old + buff);
            std::cout << " * " << c->GetName() << " Journey: " << old << " -> " << c->GetJourney() << "\n";
        }
    }
};

// =============================================
// Bond: SIDE NAMELESS (Oronyx + Georios)
// =============================================
class SideNamelessBond : public IBondRule {
public:
    void Apply(std::vector<std::unique_ptr<ICard>>& cards) override {
        if (!HasCard(cards,"Oronyx") || !HasCard(cards,"Georios")) return;
        int buffJ = BondScaling::sideNamelessJourneyBuff;
        int buffC = BondScaling::sideNamelessCycleBuff;
        std::cout << ">>> SIDE NAMELESS (+" << buffJ << "J +" << buffC << "C ALL)\n";
        for (const auto& c : cards) {
            int oldJ = c->GetJourney(), oldC = c->GetCycle();
            c->SetJourney(oldJ + buffJ);
            c->SetCycle(oldC + buffC);
            std::cout << " * " << c->GetName() << " J:" << oldJ << " -> " << c->GetJourney()
                      << " C:" << oldC << " -> " << c->GetCycle() << "\n";
        }
    }
};

// =============================================
// Bond: MOTHER & DAUGHTER (Mnestia + Zegreus)
// =============================================
class MotherDaughterBond : public IBondRule {
public:
    void Apply(std::vector<std::unique_ptr<ICard>>& cards) override {
        if (!HasCard(cards,"Mnestia") || !HasCard(cards,"Zegreus")) return;
        int buffJ = BondScaling::motherDaughterJourneyBuff;
        int buffC = BondScaling::motherDaughterCycleBuff;
        std::cout << ">>> MOTHER & DAUGHTER (+" << buffJ << "J +" << buffC << "C ALL)\n";
        for (const auto& c : cards) {
            int oldJ = c->GetJourney(), oldC = c->GetCycle();
            c->SetJourney(oldJ + buffJ);
            c->SetCycle(oldC + buffC);
            std::cout << " * " << c->GetName() << " J:" << oldJ << " -> " << c->GetJourney()
                      << " C:" << oldC << " -> " << c->GetCycle() << "\n";
        }
    }
};

// =============================================
// Bond: CYCLE BEGINNING (Demiurge + Kephale)
// =============================================
class CycleBeginningBond : public IBondRule {
public:
    void Apply(std::vector<std::unique_ptr<ICard>>& cards) override {
        if (!HasCard(cards,"Demiurge") || !HasCard(cards,"Kephale")) return;
        int buff = BondScaling::cycleBeginningBuff;
        std::cout << ">>> CYCLE BEGINNING (+" << buff << " Journey for Kephale)\n";
        for (const auto& c : cards) {
            if (c->GetName() == "Kephale") {
                int old = c->GetJourney();
                c->SetJourney(old + buff);
                std::cout << " * Kephale Journey: " << old << " -> " << c->GetJourney() << "\n";
            }
        }
    }
};

// =============================================
// Bond: CHILD OF TIME (Oronyx + Demiurge)
// =============================================
class ChildOfTimeBond : public IBondRule {
public:
    void Apply(std::vector<std::unique_ptr<ICard>>& cards) override {
        if (!HasCard(cards,"Oronyx") || !HasCard(cards,"Demiurge")) return;
        int buff = BondScaling::childOfTimeBuff;
        std::cout << ">>> CHILD OF TIME (+" << buff << " Journey Kephale & Nikador)\n";
        for (const auto& c : cards) {
            if (c->GetName()=="Kephale" || c->GetName()=="Nikador") {
                int old = c->GetJourney();
                c->SetJourney(old + buff);
                std::cout << " * " << c->GetName() << " Journey: " << old << " -> " << c->GetJourney() << "\n";
            }
        }
    }
};

// =============================================
// Bond: WAR GENERAL (Aquila + Nikador)
// =============================================
class WarGeneralBond : public IBondRule {
public:
    void Apply(std::vector<std::unique_ptr<ICard>>& cards) override {
        if (!HasCard(cards,"Aquila") || !HasCard(cards,"Nikador")) return;
        int buff = BondScaling::warGeneralBuff;
        std::cout << ">>> WAR GENERAL (+" << buff << " Journey Kephale & Nikador)\n";
        for (const auto& c : cards) {
            if (c->GetName()=="Kephale" || c->GetName()=="Nikador") {
                int old = c->GetJourney();
                c->SetJourney(old + buff);
                std::cout << " * " << c->GetName() << " Journey: " << old << " -> " << c->GetJourney() << "\n";
            }
        }
    }
};

// =============================================
// Bond: HEATED RIVALRY (Kephale + Nikador)
// =============================================
class HeatedRivalryBond : public IBondRule {
public:
    void Apply(std::vector<std::unique_ptr<ICard>>& cards) override {
        if (!HasCard(cards,"Kephale") || !HasCard(cards,"Nikador")) return;
        int buff = BondScaling::heatedRivalryBuff;
        std::cout << ">>> HEATED RIVALRY (+" << buff << " Journey Kephale & Nikador)\n";
        for (const auto& c : cards) {
            if (c->GetName()=="Kephale" || c->GetName()=="Nikador") {
                int old = c->GetJourney();
                c->SetJourney(old + buff);
                std::cout << " * " << c->GetName() << " Journey: " << old << " -> " << c->GetJourney() << "\n";
            }
        }
    }
};

// =============================================
// Bond: THREE NAMELESS (Georios + Oronyx + Kephale)
// =============================================
class ThreeNamelessBond : public IBondRule {
public:
    void Apply(std::vector<std::unique_ptr<ICard>>& cards) override {
        if (!HasCard(cards,"Georios")||!HasCard(cards,"Oronyx")||!HasCard(cards,"Kephale")) return;
        int buff = BondScaling::threeNamelessBuff;
        std::cout << ">>> THREE NAMELESS (+" << buff << " Journey Georios/Oronyx/Kephale)\n";
        for (const auto& c : cards) {
            std::string n = c->GetName();
            if (n=="Georios"||n=="Oronyx"||n=="Kephale") {
                int old = c->GetJourney();
                c->SetJourney(old + buff);
                std::cout << " * " << n << " Journey: " << old << " -> " << c->GetJourney() << "\n";
            }
        }
    }
};

// =============================================
// Bond: DEICIDE SYMPHONY — ULTIMATE
// =============================================
class DeicideSymphonyBond : public IBondRule {
public:
    void Apply(std::vector<std::unique_ptr<ICard>>& cards) override {
        if (!HasCard(cards,"Oronyx")||!HasCard(cards,"Georios")||
            !HasCard(cards,"Demiurge")||!HasCard(cards,"Kephale")) return;
        int mult = BondScaling::deicideMultiplier;
        std::cout << ">>> !! DEICIDE SYMPHONY x" << mult << " ALL STATS !!\n";
        for (const auto& c : cards) {
            int oldJ = c->GetJourney(), oldC = c->GetCycle();
            c->SetJourney(oldJ * mult);
            c->SetCycle(oldC * mult);
            std::cout << " * " << c->GetName()
                      << " J:" << oldJ << " -> " << c->GetJourney()
                      << " C:" << oldC << " -> " << c->GetCycle() << "\n";
        }
    }
};

// =============================================
// ModifierFactory — upgrade scaling & registry
// Dipanggil oleh TitanShopSystem dan main()
// TIDAK dikenal oleh GameSession
// =============================================
class ModifierFactory {
public:
    static void UpgradeBondScaling(const std::string& bondName) {
        std::cout << "\n======= BOND UPGRADE =======\n";
        std::cout << "Bond     : " << bondName << "\n";

        if (bondName == "FATE") {
            int old = BondScaling::fateMultiplier;
            BondScaling::fateMultiplier += 1;
            std::cout << "Effect          : +[Faction Count x Multiplier] Cycle\n";
            std::cout << "Multiplier      : " << old << " -> " << BondScaling::fateMultiplier << "\n";
        }
        else if (bondName == "FOUNDATION") {
            int old = BondScaling::foundationMultiplier;
            BondScaling::foundationMultiplier += 5;
            std::cout << "Effect          : +[Faction Count x Multiplier] Journey for ALL\n";
            std::cout << "Multiplier      : " << old << " -> " << BondScaling::foundationMultiplier << "\n";
        }
        else if (bondName == "CALAMITY") {
            int oldJ = BondScaling::calamityJourneyMult;
            int oldC = BondScaling::calamityCycleMult;
            BondScaling::calamityJourneyMult += 10;
            BondScaling::calamityCycleMult   += 1;
            std::cout << "Effect          : +Journey & +Cycle for CALAMITY cards\n";
            std::cout << "Journey Mult    : " << oldJ << " -> " << BondScaling::calamityJourneyMult << "\n";
            std::cout << "Cycle Mult      : " << oldC << " -> " << BondScaling::calamityCycleMult   << "\n";
        }
        else if (bondName == "CREATION") {
            int oldJ = BondScaling::creationJourneyMult;
            int oldC = BondScaling::creationCycleMult;
            BondScaling::creationJourneyMult += 5;
            BondScaling::creationCycleMult   += 1;
            std::cout << "Effect          : +Journey & +Cycle for ALL cards\n";
            std::cout << "Journey Mult    : " << oldJ << " -> " << BondScaling::creationJourneyMult << "\n";
            std::cout << "Cycle Mult      : " << oldC << " -> " << BondScaling::creationCycleMult   << "\n";
        }
        else if (bondName == "GROVE ACADEMY") {
            int old = BondScaling::groveAcademyCycleBuff;
            BondScaling::groveAcademyCycleBuff += 4;
            std::cout << "Effect          : +Cycle for ALL cards\n";
            std::cout << "Cycle Buff      : " << old << " -> " << BondScaling::groveAcademyCycleBuff << "\n";
        }
        else if (bondName == "OKHEMA ELDERS") {
            int old = BondScaling::okhemaEldersCycleBuff;
            BondScaling::okhemaEldersCycleBuff += 4;
            std::cout << "Effect          : +Cycle for ALL cards\n";
            std::cout << "Cycle Buff      : " << old << " -> " << BondScaling::okhemaEldersCycleBuff << "\n";
        }
        else if (bondName == "DUX KAISAR") {
            int old = BondScaling::duxKaisarJourneyBuff;
            BondScaling::duxKaisarJourneyBuff += 50;
            std::cout << "Effect          : +Journey for ALL cards\n";
            std::cout << "Journey Buff    : " << old << " -> " << BondScaling::duxKaisarJourneyBuff << "\n";
        }
        else if (bondName == "MOTHER DAUGHTER") {
            int oldJ = BondScaling::motherDaughterJourneyBuff;
            int oldC = BondScaling::motherDaughterCycleBuff;
            BondScaling::motherDaughterJourneyBuff += 20;
            BondScaling::motherDaughterCycleBuff   += 2;
            std::cout << "Effect          : +Journey & +Cycle for ALL cards\n";
            std::cout << "Journey Buff    : " << oldJ << " -> " << BondScaling::motherDaughterJourneyBuff << "\n";
            std::cout << "Cycle Buff      : " << oldC << " -> " << BondScaling::motherDaughterCycleBuff   << "\n";
        }
        else if (bondName == "CYCLE BEGINNING") {
            int old = BondScaling::cycleBeginningBuff;
            BondScaling::cycleBeginningBuff += 250;
            std::cout << "Effect          : +Journey for Kephale\n";
            std::cout << "Journey Buff    : " << old << " -> " << BondScaling::cycleBeginningBuff << "\n";
        }
        else if (bondName == "HEATED RIVALRY") {
            int old = BondScaling::heatedRivalryBuff;
            BondScaling::heatedRivalryBuff += 100;
            std::cout << "Effect          : +Journey for Kephale & Nikador\n";
            std::cout << "Journey Buff    : " << old << " -> " << BondScaling::heatedRivalryBuff << "\n";
        }
        else if (bondName == "THREE NAMELESS") {
            int old = BondScaling::threeNamelessBuff;
            BondScaling::threeNamelessBuff += 100;
            std::cout << "Effect          : +Journey for Georios, Oronyx & Kephale\n";
            std::cout << "Journey Buff    : " << old << " -> " << BondScaling::threeNamelessBuff << "\n";
        }
        else if (bondName == "DEICIDE SYMPHONY") {
            int old = BondScaling::deicideMultiplier;
            BondScaling::deicideMultiplier += 1;
            std::cout << "Effect          : x All Stats for all cards\n";
            std::cout << "Stat Multiplier : " << old << "x -> " << BondScaling::deicideMultiplier << "x\n";
        }
        else {
            std::cout << "Effect          : Special bond upgraded\n";
        }
        std::cout << "============================\n";
    }

    // Menampilkan nilai AKTUAL dari BondScaling — bukan hardcode
    static void ShowBondRegistry() {
        std::cout << "\n======= TITAN FACTIONS (Nilai Saat Ini) =======\n";
        std::cout << "Aktif jika minimal ada 2 kartu dari faksi yang sama.\n";
        std::cout << "Bonus = [Jumlah Kartu Faksi] x [Nilai Buff saat ini].\n\n";

        std::cout << "1. TITAN FATE      : Janus, Talanton, Oronyx\n";
        std::cout << "   Cycle Buff/kartu : " << BondScaling::fateMultiplier << "\n";
        std::cout << "2. TITAN FOUNDATION: Georios, Phagousa, Aquila\n";
        std::cout << "   Journey Buff/kartu: " << BondScaling::foundationMultiplier << "\n";
        std::cout << "3. TITAN CALAMITY  : Nikador, Thanatos, Zegreus\n";
        std::cout << "   Journey Buff/kartu: " << BondScaling::calamityJourneyMult
                  << " | Cycle Buff/kartu: "   << BondScaling::calamityCycleMult << "\n";
        std::cout << "4. TITAN CREATION  : Kephale, Cerces, Mnestia\n";
        std::cout << "   Journey Buff/kartu: " << BondScaling::creationJourneyMult
                  << " | Cycle Buff/kartu: "   << BondScaling::creationCycleMult << "\n";

        std::cout << "\n======= SPECIAL COMBO BONDS =======\n";
        std::cout << " Grove Academy    : Cerces+Aquila          -> +" << BondScaling::groveAcademyCycleBuff     << " Cycle ALL\n";
        std::cout << " Okhema Elders    : Janus+Mnestia          -> +" << BondScaling::okhemaEldersCycleBuff     << " Cycle ALL\n";
        std::cout << " Dux Kaisar       : Phagousa+Talanton      -> +" << BondScaling::duxKaisarJourneyBuff      << " Journey ALL\n";
        std::cout << " Side Nameless    : Oronyx+Georios         -> +" << BondScaling::sideNamelessJourneyBuff   << "J +" << BondScaling::sideNamelessCycleBuff << "C ALL\n";
        std::cout << " Mother&Daughter  : Mnestia+Zegreus        -> +" << BondScaling::motherDaughterJourneyBuff << "J +" << BondScaling::motherDaughterCycleBuff << "C ALL\n";
        std::cout << " Cycle Beginning  : Demiurge+Kephale       -> +" << BondScaling::cycleBeginningBuff        << " Journey Kephale\n";
        std::cout << " Child of Time    : Oronyx+Demiurge        -> +" << BondScaling::childOfTimeBuff           << " Journey Kephale/Nikador\n";
        std::cout << " War General      : Aquila+Nikador         -> +" << BondScaling::warGeneralBuff            << " Journey Kephale/Nikador\n";
        std::cout << " Heated Rivalry   : Kephale+Nikador        -> +" << BondScaling::heatedRivalryBuff         << " Journey both\n";
        std::cout << " Three Nameless   : Georios+Oronyx+Kephale -> +" << BondScaling::threeNamelessBuff         << " Journey three\n";
        std::cout << " DEICIDE SYMPHONY : Oronyx+Georios+Demiurge+Kephale -> x" << BondScaling::deicideMultiplier << " ALL STATS\n";
        std::cout << "===================================\n";
    }
};
