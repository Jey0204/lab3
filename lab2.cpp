#include <iostream>
#include "KompozytRownolegly.h"
#include "KompozytSzeregowy.h"
#include "Mnoznik.h"
#include "Komponent.h" // Dodany dla porządku, chociaż może być pośrednio dołączony

int main() {
    // --- Testowanie Kompozytu Równoległego ---
    std::cout << "--- Test Kompozytu Rownoleglego ---" << std::endl;
    KompozytRownolegly* systemRownolegly = new KompozytRownolegly();
    systemRownolegly->dodaj(new Mnoznik(2.0)); // Mnoży wejście przez 2
    systemRownolegly->dodaj(new Mnoznik(3.0)); // Mnoży wejście przez 3
    // Dodajemy trzeci mnożnik dla bardziej złożonego testu
    systemRownolegly->dodaj(new Mnoznik(0.5)); // Mnoży wejście przez 0.5

    double wejscieRownolegle = 10.0;
    double wynikRownolegly = systemRownolegly->symuluj(wejscieRownolegle);
    // Oczekiwany wynik: (10.0 * 2.0) + (10.0 * 3.0) + (10.0 * 0.5) = 20.0 + 30.0 + 5.0 = 55.0
    std::cout << "Wejscie: " << wejscieRownolegle << std::endl;
    std::cout << "Wynik symulacji rownoleglej: " << wynikRownolegly << std::endl;
    std::cout << "Oczekiwano: 55.0" << std::endl;
    std::cout << "------------------------------------" << std::endl;

    // --- Testowanie Kompozytu Szeregowego ---
    std::cout << "--- Test Kompozytu Szeregowego ---" << std::endl;
    KompozytSzeregowy* systemSzeregowy = new KompozytSzeregowy();
    systemSzeregowy->dodaj(new Mnoznik(2.0)); // Pierwszy komponent: wejście * 2
    systemSzeregowy->dodaj(new Mnoznik(3.0)); // Drugi komponent: (wynik poprzedniego) * 3
    // Dodajemy trzeci mnożnik
    systemSzeregowy->dodaj(new Mnoznik(0.5)); // Trzeci komponent: (wynik poprzedniego) * 0.5


    double wejscieSzeregowe = 10.0;
    double wynikSzeregowy = systemSzeregowy->symuluj(wejscieSzeregowe);
    // Oczekiwany wynik: ((10.0 * 2.0) * 3.0) * 0.5 = (20.0 * 3.0) * 0.5 = 60.0 * 0.5 = 30.0
    std::cout << "Wejscie: " << wejscieSzeregowe << std::endl;
    std::cout << "Wynik symulacji szeregowej: " << wynikSzeregowy << std::endl;
    std::cout << "Oczekiwano: 30.0" << std::endl;
    std::cout << "------------------------------------" << std::endl;

    // --- Testowanie zagnieżdżonego kompozytu (szeregowy w równoległym) ---
    std::cout << "--- Test Zagniezdzony (Szeregowy w Rownoleglym) ---" << std::endl;
    KompozytRownolegly* systemZagniezdzony = new KompozytRownolegly();
    systemZagniezdzony->dodaj(new Mnoznik(4.0)); // Gałąź 1: 10.0 * 4.0 = 40.0

    KompozytSzeregowy* galazSzeregowa = new KompozytSzeregowy();
    galazSzeregowa->dodaj(new Mnoznik(2.0)); // 10.0 * 2.0 = 20.0
    galazSzeregowa->dodaj(new Mnoznik(1.5)); // 20.0 * 1.5 = 30.0
    systemZagniezdzony->dodaj(galazSzeregowa); // Gałąź 2 (szeregowa)

    double wejscieZagniezdzony = 10.0;
    double wynikZagniezdzony = systemZagniezdzony->symuluj(wejscieZagniezdzony);
    // Oczekiwany wynik: (10.0 * 4.0) + ((10.0 * 2.0) * 1.5) = 40.0 + (20.0 * 1.5) = 40.0 + 30.0 = 70.0
    std::cout << "Wejscie: " << wejscieZagniezdzony << std::endl;
    std::cout << "Wynik symulacji zagnizdzonej: " << wynikZagniezdzony << std::endl;
    std::cout << "Oczekiwano: 70.0" << std::endl;
    std::cout << "------------------------------------" << std::endl;

    // --- Sprzątanie pamięci ---
    // Komponenty (Mnoznik, KompozytSzeregowy) dodane do Kompozytów (systemRownolegly, systemSzeregowy, systemZagniezdzony)
    // są zarządzane i zwalniane przez destruktory tych Kompozytów.
    // Należy zwolnić pamięć tylko dla głównych kompozytów.
    delete systemRownolegly;
    delete systemSzeregowy;
    delete systemZagniezdzony; 
    // galazSzeregowa jest dzieckiem systemZagniezdzony, więc zostanie usunięta przez jego destruktor.

    return 0;
}
