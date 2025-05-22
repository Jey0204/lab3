#ifndef KOMPOZYT_H
#define KOMPOZYT_H

#include "Komponent.h"
#include <vector>
#include <algorithm> // Dla std::remove

class Kompozyt : public Komponent {
protected: // Używamy protected, aby klasy pochodne miały dostęp
    std::vector<Komponent*> dzieci;

public:
    ~Kompozyt() override; // Destruktor do zwolnienia pamięci dzieci

    void dodaj(Komponent* komponent) override;
    void usun(Komponent* komponent) override;

    // Metoda symuluj pozostaje czysto wirtualna lub wirtualna, 
    // w zależności od tego, czy Kompozyt sam w sobie ma mieć domyślne zachowanie.
    // Zgodnie z poleceniem, jej konkretna implementacja zależeć będzie od typu kompozytu.
    // Jeśli Kompozyt nie jest przeznaczony do bezpośredniego użycia, może pozostać czysto wirtualna.
    // Jeśli jednak przewidujemy, że Kompozyt może mieć jakieś domyślne zachowanie symulacji,
    // można ją zdefiniować jako wirtualną z domyślną implementacją.
    // W tym przypadku, zakładając, że Kompozyt jest abstrakcyjną bazą dla Szeregowego/Rownoleglego,
    // zostawiamy ją jako czysto wirtualną.
    virtual double symuluj(double wejscie) = 0;

    // Metoda pomocnicza do testowania
    size_t getLiczbaDzieci() const;
};

#endif // KOMPOZYT_H
