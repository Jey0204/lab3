#ifndef MNOZNIK_H
#define MNOZNIK_H

#include "Komponent.h"

class Mnoznik : public Komponent {
private:
    double wspolczynnik;

public:
    Mnoznik(double wsp);
    ~Mnoznik() override = default; // Domyślny destruktor

    double symuluj(double wejscie) override;

    // Metody dodaj i usun nie są potrzebne dla Mnoznika,
    // więc używamy domyślnych implementacji z Komponent (które nic nie robią).
};

#endif // MNOZNIK_H
