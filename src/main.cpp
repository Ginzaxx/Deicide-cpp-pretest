#include <iostream>
#include "RunSession.h"

int main() {
    int choice = 0;

    while (choice != 3) {
        std::cout << "\n=== DEICIDE GAME ===\n"
                  << "1. Play Game\n"
                  << "2. View Deck Registry\n"
                  << "3. Quit\n"
                  << "Choice: ";
        std::cin >> choice;

        if (choice == 1) {
            RunSession session;
            session.Start(); // Keluar dari sini otomatis kembali ke menu
        } else if (choice == 2) {
            // Tampilkan semua kartu di registry
            CardRegistry tempRegistry; 
            tempRegistry.ShowAllPrototypes();
            
            std::cout << "\nPress Enter to return to menu...";
            std::cin.ignore(1000, '\n');
            std::cin.get(); 
        }
    }
    return 0;
}