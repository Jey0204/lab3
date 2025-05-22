#include "KompozytSzeregowy.h"

// Implementacja konstruktora i destruktora nie jest konieczna, jeśli są domyślne
// i klasa bazowa Kompozyt ma wirtualny destruktor.

double KompozytSzeregowy::symuluj(double wejscie) {
    double aktualneWyjscie = wejscie; // Początkowe wejście dla pierwszego komponentu

    for (Komponent* dziecko : dzieci) { // Zakładając, że 'dzieci' jest protected w Kompozyt
        if (dziecko) { // Sprawdzenie czy wskaźnik nie jest nullptr
            aktualneWyjscie = dziecko->symuluj(aktualneWyjscie); // Wyjście z dziecka staje się wejściem dla następnego
        }
    }
    return aktualneWyjscie; // Zwraca wyjście ostatniego komponentu
}
