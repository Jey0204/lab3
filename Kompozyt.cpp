#include "Kompozyt.h"

Kompozyt::~Kompozyt() {
    for (Komponent* dziecko : dzieci) {
        delete dziecko; // Zwolnienie pamięci każdego dziecka
    }
    dzieci.clear(); // Opróżnienie wektora
}

void Kompozyt::dodaj(Komponent* komponent) {
    if (komponent) { // Sprawdzenie czy wskaźnik nie jest nullptr
        dzieci.push_back(komponent);
    }
}

void Kompozyt::usun(Komponent* komponent) {
    // Używamy std::remove do przesunięcia elementu do usunięcia na koniec wektora
    // a następnie erase do faktycznego usunięcia go z wektora.
    // Ważne: to usuwa tylko wskaźnik z wektora, nie zwalnia pamięci obiektu, na który wskazuje.
    // Za zarządzanie pamięcią poszczególnych komponentów odpowiada destruktor Kompozyt
    // lub kod, który tworzył komponenty. W tym przypadku destruktor Kompozyt zwalnia pamięć.
    auto it = std::remove(dzieci.begin(), dzieci.end(), komponent);
    if (it != dzieci.end()) { // Sprawdzenie czy element został znaleziony
        // delete *it; // Jeśli chcemy zwolnić pamięć komponentu przy usuwaniu z listy
                      // Należy to robić ostrożnie, aby uniknąć podwójnego zwolnienia,
                      // jeśli komponent jest zarządzany również gdzie indziej.
                      // Zgodnie z typowym wzorcem Kompozyt, kontener (Kompozyt) jest właścicielem dzieci.
                      // Jednak bezpośrednie `delete *it` tutaj może być ryzykowne, jeśli komponent
                      // został dodany do wielu kompozytów lub jest zarządzany zewnętrznie.
                      // Bezpieczniej jest, gdy destruktor Kompozyt zwalnia wszystkie dzieci.
        dzieci.erase(it, dzieci.end());
    }
}

size_t Kompozyt::getLiczbaDzieci() const {
    return dzieci.size();
}
