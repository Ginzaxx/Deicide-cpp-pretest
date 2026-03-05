#include "ModifierFactory.h"
#include <iostream>

bool ModifierFactory::HasCard(const std::vector<std::unique_ptr<ICard>>& selectedCards, std::string name) {
    for (const auto& card : selectedCards) {
        if (card->GetName() == name) return true;
    }
    return false;
}

static int fateMultiplier = 2;
static int foundationMultiplier = 20;
static int calamityJourneyMultiplier = 30;
static int calamityCycleMultiplier = 2;
static int creationJourneyMultiplier = 10;
static int creationCycleMultiplier = 1;
static int groveAcademyCycleBuff = 4;
static int okhemaEldersCycleBuff = 4;
static int duxKaisarJourneyBuff = 40;
static int sideNamelessJourneyBuff = 20;
static int sideNamelessCycleBuff = 2;
static int motherDaughterJourneyBuff = 20;
static int motherDaughterCycleBuff = 2;
static int cycleBeginningBuff = 500;
static int childOfTimeBuff = 10;
static int warGeneralBuff = 100;
static int heatedRivalryBuff = 100;
static int threeNamelessBuff = 100;
static int deicideMultiplier = 3;

void ModifierFactory::UpgradeBondScaling(const std::string& bondName)
{
    std::cout << "\n======= BOND UPGRADE =======\n";

    if (bondName == "FATE")
    {
        int oldValue = fateMultiplier;
        fateMultiplier += 1;

        std::cout << "Bond: FATE\n";
        std::cout << "Old Multiplier : " << oldValue << "\n";
        std::cout << "New Multiplier : " << fateMultiplier << "\n";
        std::cout << "Effect         : +[Faction Count x Multiplier] Cycle\n";
    }
    else if (bondName == "FOUNDATION")
    {
        int oldValue = foundationMultiplier;
        foundationMultiplier += 5;

        std::cout << "Bond: FOUNDATION\n";
        std::cout << "Old Multiplier : " << oldValue << "\n";
        std::cout << "New Multiplier : " << foundationMultiplier << "\n";
        std::cout << "Effect         : +[Faction Count x Multiplier] Journey\n";
    }
    else if (bondName == "CALAMITY")
    {
        int oldJ = calamityJourneyMultiplier;
        int oldC = calamityCycleMultiplier;

        calamityJourneyMultiplier += 10;
        calamityCycleMultiplier += 1;

        std::cout << "Bond: CALAMITY\n";
        std::cout << "Journey Multiplier : " << oldJ << " -> " << calamityJourneyMultiplier << "\n";
        std::cout << "Cycle Multiplier   : " << oldC << " -> " << calamityCycleMultiplier << "\n";
    }
    else if (bondName == "CREATION")
    {
        int oldJ = creationJourneyMultiplier;
        int oldC = creationCycleMultiplier;

        creationJourneyMultiplier += 5;
        creationCycleMultiplier += 1;

        std::cout << "Bond: CREATION\n";
        std::cout << "Journey Multiplier : " << oldJ << " -> " << creationJourneyMultiplier << "\n";
        std::cout << "Cycle Multiplier   : " << oldC << " -> " << creationCycleMultiplier << "\n";
    }
    else if (bondName == "GROVE ACADEMY")
    {
        int old = groveAcademyCycleBuff;
        groveAcademyCycleBuff += 4;

        std::cout << "Bond: GROVE ACADEMY\n";
        std::cout << "Cycle Buff : " << old << " -> " << groveAcademyCycleBuff << "\n";
    }else if (bondName == "OKHEMA ELDERS")
    {
        int old = okhemaEldersCycleBuff;
        okhemaEldersCycleBuff += 4;

        std::cout << "Bond: OKHEMA ELDERS\n";
        std::cout << "Cycle Buff : " << old << " -> " << okhemaEldersCycleBuff << "\n";
    }
    else if (bondName == "DUX KAISAR")
    {
        int old = duxKaisarJourneyBuff;
        duxKaisarJourneyBuff += 50;

        std::cout << "Bond: DUX KAISAR\n";
        std::cout << "Journey Buff : " << old << " -> " << duxKaisarJourneyBuff << "\n";
    }
    else if (bondName == "MOTHER DAUGHTER")
    {
        motherDaughterJourneyBuff += 20;
        motherDaughterCycleBuff += 2;

        std::cout << "Bond: MOTHER & DAUGHTER\n";
        std::cout << "Journey Buff -> " << motherDaughterJourneyBuff << "\n";
        std::cout << "Cycle Buff   -> " << motherDaughterCycleBuff << "\n";
    }
    else if (bondName == "CYCLE BEGINNING")
    {
        int old = cycleBeginningBuff;
        cycleBeginningBuff += 250;

        std::cout << "Bond: CYCLE BEGINNING\n";
        std::cout << "Kephale Journey Buff : " << old << " -> " << cycleBeginningBuff << "\n";
    }
    else if (bondName == "HEATED RIVALRY")
    {
        int old = heatedRivalryBuff;
        heatedRivalryBuff += 100;

        std::cout << "Bond: HEATED RIVALRY\n";
        std::cout << "Journey Buff : " << old << " -> " << heatedRivalryBuff << "\n";
    }
    else if (bondName == "THREE NAMELESS")
    {
        int old = threeNamelessBuff;
        threeNamelessBuff += 100;

        std::cout << "Bond: THREE NAMELESS\n";
        std::cout << "Journey Buff : " << old << " -> " << threeNamelessBuff << "\n";
    }
    else if (bondName == "DEICIDE SYMPHONY")
    {
        int old = deicideMultiplier;
        deicideMultiplier += 1;

        std::cout << "Bond: DEICIDE SYMPHONY\n";
        std::cout << "Stat Multiplier : " << old << "x -> " << deicideMultiplier << "x\n";
    }
    else
    {
        std::cout << "Special Bond Upgraded: " << bondName << "\n";
        std::cout << "This affects combo activation only.\n";
    }

    std::cout << "==============================\n";
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
        if (countFate >= 2)
        {
            int totalBuff = countFate * fateMultiplier;

            std::cout << ">>> TITAN FATE ACTIVE (+"
                    << totalBuff
                    << " Cycle for All Cards)\n";

            for (const auto& card : selectedCards)
            {
                std::string name = card->GetName();
                if (name == "Janus" || name == "Talanton" || name == "Oronyx")
                {
                    int oldC = card->GetCycle();
                    card->SetCycle(oldC + totalBuff);

                    std::cout << " * " << name
                            << " | Cycle: "
                            << oldC << " -> "
                            << card->GetCycle() << "\n";
                }
            }
        }
        if (countFoundation >= 2)
        {
            int totalBuff = countFoundation * foundationMultiplier;

            std::cout << ">>> TITAN FOUNDATION ACTIVE (+"
                    << totalBuff
                    << " Journey for All Cards)\n";

            for (const auto& card : selectedCards)
            {
                std::string name = card->GetName();
                    int oldJ = card->GetJourney();
                    card->SetJourney(oldJ + totalBuff);

                    std::cout << " * " << name
                            << " | Journey: "
                            << oldJ << " -> "
                            << card->GetJourney() << "\n";
            }
        }
        if (countCalamity >= 2)
        {
            int totalJourney = countCalamity * calamityJourneyMultiplier;
            int totalCycle   = countCalamity * calamityCycleMultiplier;

            std::cout << ">>> TITAN CALAMITY ACTIVE (+"
                    << totalJourney << " Journey, +"
                    << totalCycle << " Cycle for CALAMITY cards)\n";

            for (const auto& card : selectedCards)
            {
                std::string name = card->GetName();
                if (name == "Nikador" || name == "Thanatos" || name == "Zegreus")
                {
                    int oldJ = card->GetJourney();
                    int oldC = card->GetCycle();

                    card->SetJourney(oldJ + totalJourney);
                    card->SetCycle(oldC + totalCycle);

                    std::cout << " * " << name
                            << " | Journey: " << oldJ
                            << " -> " << card->GetJourney()
                            << " | Cycle: " << oldC
                            << " -> " << card->GetCycle() << "\n";
                }
            }
        }
        if (countCreation >= 2)
        {
            int totalJourney = countCreation * creationJourneyMultiplier;
            int totalCycle   = countCreation * creationCycleMultiplier;

            std::cout << ">>> TITAN CREATION ACTIVE (+"
                    << totalJourney << " Journey, +"
                    << totalCycle << " Cycle for All Cards)\n";

            for (const auto& card : selectedCards)
            {
                std::string name = card->GetName();
                    int oldJ = card->GetJourney();
                    int oldC = card->GetCycle();

                    card->SetJourney(oldJ + totalJourney);
                    card->SetCycle(oldC + totalCycle);

                    std::cout << " * " << name
                            << " | Journey: " << oldJ
                            << " -> " << card->GetJourney()
                            << " | Cycle: " << oldC
                            << " -> " << card->GetCycle() << "\n";
            }
        }

    std::cout << "---------------------------\n";

// ================= SPECIAL BONDS =================

if (hasJanus && hasMnestia)
{
    std::cout << ">>> OKHEMA ELDERS ACTIVE (+"
              << okhemaEldersCycleBuff
              << " Cycle for ALL cards)\n";

    for (const auto& card : selectedCards)
    {
        int oldCycle = card->GetCycle();
        card->SetCycle(oldCycle + okhemaEldersCycleBuff);

        std::cout << " * " << card->GetName()
                  << " | Cycle: " << oldCycle
                  << " -> " << card->GetCycle() << "\n";
    }
}

if (hasCerces && hasAquila)
{
    std::cout << ">>> Grove Academy (+"
              << groveAcademyCycleBuff
              << " Cycle for ALL cards)\n";

    for (const auto& card : selectedCards)
    {
        int oldCycle = card->GetCycle();
        card->SetCycle(oldCycle + groveAcademyCycleBuff);

        std::cout << " * " << card->GetName()
                  << " | Cycle: " << oldCycle
                  << " -> " << card->GetCycle() << "\n";
    }
}

if (hasPhagousa && hasTalanton)
{
    std::cout << ">>> DUX KAISAR ACTIVE (+"
              << duxKaisarJourneyBuff
              << " Journey for ALL cards)\n";

    for (const auto& card : selectedCards)
    {
        int oldJourney = card->GetJourney();
        card->SetJourney(oldJourney + duxKaisarJourneyBuff);

        std::cout << " * " << card->GetName()
                  << " | Journey: " << oldJourney
                  << " -> " << card->GetJourney() << "\n";
    }
}

if (hasGeorios && hasOronyx)
{
    std::cout << ">>> SIDE NAMELESS (+"
              << sideNamelessJourneyBuff << " Journey, +"
              << sideNamelessCycleBuff << " Cycle for ALL cards)\n";

    for (const auto& card : selectedCards)
    {
        int oldJourney = card->GetJourney();
        int oldCycle = card->GetCycle();

        card->SetJourney(oldJourney + sideNamelessJourneyBuff);
        card->SetCycle(oldCycle + sideNamelessCycleBuff);

        std::cout << " * " << card->GetName()
                  << " | Journey: " << oldJourney
                  << " -> " << card->GetJourney()
                  << " | Cycle: " << oldCycle
                  << " -> " << card->GetCycle() << "\n";
    }
}

if (hasMnestia && hasZegreus)
{
    std::cout << ">>> MOTHER & DAUGHTER ACTIVE (+"
              << motherDaughterJourneyBuff << " Journey, +"
              << motherDaughterCycleBuff << " Cycle for ALL cards)\n";

    for (const auto& card : selectedCards)
    {
        int oldJourney = card->GetJourney();
        int oldCycle = card->GetCycle();

        card->SetJourney(oldJourney + motherDaughterJourneyBuff);
        card->SetCycle(oldCycle + motherDaughterCycleBuff);

        std::cout << " * " << card->GetName()
                  << " | Journey: " << oldJourney
                  << " -> " << card->GetJourney()
                  << " | Cycle: " << oldCycle
                  << " -> " << card->GetCycle() << "\n";
    }
}

if (hasDemiurge && hasKephale)
{
    std::cout << ">>> CYCLE BEGINNING ACTIVE (+"
              << cycleBeginningBuff
              << " Journey for Kephale)\n";

    for (const auto& card : selectedCards)
    {
        if (card->GetName() == "Kephale")
        {
            int oldJourney = card->GetJourney();
            card->SetJourney(oldJourney + cycleBeginningBuff);

            std::cout << " * Kephale | Journey: "
                      << oldJourney << " -> "
                      << card->GetJourney() << "\n";
        }
    }
}

if (hasOronyx && hasDemiurge)
{
    std::cout << ">>> CHILD OF TIME (+"
              << childOfTimeBuff
              << " Journey for Kephale & Nikador)\n";

    for (const auto& card : selectedCards)
    {
        std::string name = card->GetName();
        if (name == "Kephale" || name == "Nikador")
        {
            int oldJ = card->GetJourney();
            card->SetJourney(oldJ + childOfTimeBuff);

            std::cout << " * " << name
                      << " | Journey: "
                      << oldJ << " -> "
                      << card->GetJourney() << "\n";
        }
    }
}

if (hasAquila && hasNikador)
{
    std::cout << ">>> WAR GENERAL (+"
              << warGeneralBuff
              << " Journey for Kephale & Nikador)\n";

    for (const auto& card : selectedCards)
    {
        std::string name = card->GetName();
        if (name == "Kephale" || name == "Nikador")
        {
            int oldJ = card->GetJourney();
            card->SetJourney(oldJ + warGeneralBuff);

            std::cout << " * " << name
                      << " | Journey: "
                      << oldJ << " -> "
                      << card->GetJourney() << "\n";
        }
    }
}

if (hasKephale && hasNikador)
{
    std::cout << ">>> HEATED RIVALRY ACTIVE (+"
              << heatedRivalryBuff
              << " Journey for Kephale & Nikador)\n";

    for (const auto& card : selectedCards)
    {
        std::string name = card->GetName();
        if (name == "Kephale" || name == "Nikador")
        {
            int oldJ = card->GetJourney();
            card->SetJourney(oldJ + heatedRivalryBuff);

            std::cout << " * " << name
                      << " | Journey: "
                      << oldJ << " -> "
                      << card->GetJourney() << "\n";
        }
    }
}

if (hasGeorios && hasOronyx && hasKephale)
{
    std::cout << ">>> THREE NAMELESS ACTIVE (+"
              << threeNamelessBuff
              << " Journey for Georios, Oronyx & Kephale)\n";

    for (const auto& card : selectedCards)
    {
        std::string name = card->GetName();
        if (name == "Georios" || name == "Oronyx" || name == "Kephale")
        {
            int oldJ = card->GetJourney();
            card->SetJourney(oldJ + threeNamelessBuff);

            std::cout << " * " << name
                      << " | Journey: "
                      << oldJ << " -> "
                      << card->GetJourney() << "\n";
        }
    }
}

if (hasOronyx && hasGeorios && hasDemiurge && hasKephale)
{
    std::cout << ">>> ULTIMATE BOND: DEICIDE SYMPHONY (x"
              << deicideMultiplier
              << " ALL STATS!) <<<\n";

    for (const auto& card : selectedCards)
    {
        std::string name = card->GetName();

        int oldJ = card->GetJourney();
        int oldC = card->GetCycle();

        card->SetJourney(oldJ * deicideMultiplier);
        card->SetCycle(oldC * deicideMultiplier);

        std::cout << " * " << name
                  << " | Journey: " << oldJ
                  << " -> " << card->GetJourney()
                  << " | Cycle: " << oldC
                  << " -> " << card->GetCycle() << "\n";
    }
}

    std::cout << "----------------------\n";
}

void ModifierFactory::ShowBondRegistry() {
    std::cout << "\n======= TITAN FACTIONS (Scaling Buffs) =======\n";
    std::cout << "Aktif jika minimal ada 2 kartu dari faksi yang sama (termasuk duplikat).\n";
    std::cout << "Bonus dihitung dari [Jumlah Kartu Faksi] x [Nilai Buff].\n\n";

    std::cout << "1. TITAN FATE      : Janus, Talanton, Oronyx\n";
    std::cout << "   - Buff: +2 Cycle untuk semua kartu per kartu faksi.\n";
    std::cout << "2. TITAN FOUNDATION: Georios, Phagousa, Aquila\n";
    std::cout << "   - Buff: +20 Journey untuk semua kartu per kartu faksi.\n";
    std::cout << "3. TITAN CALAMITY  : Nikador, Thanatos, Zegreus\n";
    std::cout << "   - Buff: +30 Journey & +2 Cycle hanya untuk kartu faksi per kartu faksi.\n";
    std::cout << "4. TITAN CREATION  : Kephale, Cerces, Mnestia\n";
    std::cout << "   - Buff: +10 Journey & +1 Cycle untuk semua kartu per kartu faksi.\n";

    std::cout << "\n======= SPECIAL COMBO BONDS =======\n";
    std::cout << " - Grove Academy      : Cerces + Aquila      -> +4 Cycle All\n";
    std::cout << " - Okhema Elders      : Janus + Mnestia       -> +4 Cycle All\n";
    std::cout << " - Child Of Time      : Oronyx + Demiurge     -> +10 Cycle All\n";
    std::cout << " - Dux Kaisar         : Phagousa + Talanton   -> +40 Journey All\n";
    std::cout << " - Mother & Daughter  : Mnestia + Zegreus     -> +20J & +2C All\n";
    std::cout << " - Side Nameless      : Oronyx + Georios     -> +20J & +2C All\n";
    std::cout << " - Cycle Beginning    : Demiurge + Kephale    -> +500J for Kephale\n";
    std::cout << " - Heated Rivalry     : Kephale + Nikador     -> +100J for both\n";
    std::cout << " - Three Nameless     : Georios + Oronyx + Kephale -> +100J for those three\n";
    std::cout << " - DEICIDE SYMPHONY   : Oronyx + Georios + Demiurge + Kephale -> X3 Stats!\n";
    std::cout << "==============================================\n";
}