#ifndef KOMPONENT_H
#define KOMPONENT_H

class Komponent {
public:
    virtual ~Komponent() {} // Wirtualny destruktor dla poprawnego zwalniania pamięci

    virtual double symuluj(double wejscie) = 0; // Czysto wirtualna metoda symuluj

    virtual void dodaj(Komponent* komponent);
    virtual void usun(Komponent* komponent);
};

#endif // KOMPONENT_H
