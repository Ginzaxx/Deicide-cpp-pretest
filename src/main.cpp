#include <iostream>
#include <vector>
#include "GameSession.h"
#include "ModifierFactory.h"
#include "DeicideScoringRule.h"
#include "TitanShopSystem.h"
#include "StandardWinCondition.h"

// ============================================================
// main() hanya bertugas merakit komponen dan menjalankan game.
// Tidak ada logika gameplay di sini.
// ============================================================
int main() {
    int choice = 0;

    while (choice != 3) {
        std::cout << "\n=== DEICIDE GAME ===\n";
        std::cout << " 1. Play Game\n";
        std::cout << " 2. View Card & Bond Registry\n";
        std::cout << " 3. Quit\n";
        std::cout << "Pilihan: ";
        std::cin >> choice;
        std::cin.ignore(1000, '\n');

        if (choice == 1) {
            // Semua bond rules (mutable — bisa tambah/hapus tanpa ubah GameSession)
            TitanFateBond       fate;
            TitanFoundationBond foundation;
            TitanCalamityBond   calamity;
            TitanCreationBond   creation;
            GroveAcademyBond    grove;
            OkhemaEldersBond    okhema;
            DuxKaisarBond       duxKaisar;
            SideNamelessBond    sideNameless;
            MotherDaughterBond  motherDaughter;
            CycleBeginningBond  cycleBeginning;
            ChildOfTimeBond     childOfTime;
            WarGeneralBond      warGeneral;
            HeatedRivalryBond   heatedRivalry;
            ThreeNamelessBond   threeNameless;
            DeicideSymphonyBond deicide;

            std::vector<IBondRule*> bonds = {
                &fate, &foundation, &calamity, &creation,
                &grove, &okhema, &duxKaisar, &sideNameless,
                &motherDaughter, &cycleBeginning, &childOfTime,
                &warGeneral, &heatedRivalry, &threeNameless, &deicide
            };

            // Mutable: ganti class ini untuk ubah scoring/shop/win
            DeicideScoringRule  scoring;
            TitanShopSystem     shop;
            StandardWinCondition win;

            // GameSession tidak berubah apapun yang di-inject
            GameSession session(bonds, &scoring, &shop, &win);
            session.Start();

        } else if (choice == 2) {
            CardRegistry reg;
            reg.ShowAllPrototypes();
            ModifierFactory::ShowBondRegistry();
            std::cout << "\nTekan Enter untuk kembali...";
            std::cin.get();
        }
    }

    std::cout << "Sampai jumpa!\n";
    return 0;
}
