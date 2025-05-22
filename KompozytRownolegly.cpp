#include "KompozytRownolegly.h"

// Implementacja konstruktora i destruktora nie jest konieczna, jeśli są domyślne
// i klasa bazowa Kompozyt ma wirtualny destruktor.

double KompozytRownolegly::symuluj(double wejscie) {
    double sumaWyjsc = 0.0;
    for (Komponent* dziecko : dzieci) { // Zakładając, że 'dzieci' jest protected w Kompozyt
        if (dziecko) { // Sprawdzenie czy wskaźnik nie jest nullptr
            sumaWyjsc += dziecko->symuluj(wejscie);
        }
    }
    return sumaWyjsc;
}
