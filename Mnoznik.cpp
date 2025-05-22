#include "Mnoznik.h"

Mnoznik::Mnoznik(double wsp) : wspolczynnik(wsp) {}

double Mnoznik::symuluj(double wejscie) {
    return wejscie * wspolczynnik;
}
