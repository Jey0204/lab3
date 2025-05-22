#include "Komponent.h"
#include <stdexcept> // Dla std::runtime_error

void Komponent::dodaj(Komponent* komponent) {
    // Domyślna implementacja: nic nie rób lub zgłoś błąd,
    // ponieważ nie wszystkie komponenty są kontenerami.
    // Na przykład, można zgłosić wyjątek:
    // throw std::runtime_error("Operacja dodaj nie jest wspierana dla tego komponentu.");
}

void Komponent::usun(Komponent* komponent) {
    // Domyślna implementacja: nic nie rób lub zgłoś błąd.
    // Na przykład, można zgłosić wyjątek:
    // throw std::runtime_error("Operacja usun nie jest wspierana dla tego komponentu.");
}
