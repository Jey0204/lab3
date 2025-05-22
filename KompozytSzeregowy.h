#ifndef KOMPOZYTSZEREGOWY_H
#define KOMPOZYTSZEREGOWY_H

#include "Kompozyt.h"

class KompozytSzeregowy : public Kompozyt {
public:
    // Konstruktor i destruktor mogą być domyślne, jeśli Kompozyt ma odpowiedni destruktor wirtualny
    // KompozytSzeregowy();
    // ~KompozytSzeregowy() override;

    double symuluj(double wejscie) override;
};

#endif // KOMPOZYTSZEREGOWY_H
