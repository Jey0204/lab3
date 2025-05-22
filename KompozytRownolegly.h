#ifndef KOMPOZYTROWNOGLEGLY_H
#define KOMPOZYTROWNOGLEGLY_H

#include "Kompozyt.h"

class KompozytRownolegly : public Kompozyt {
public:
    // Konstruktor i destruktor mogą być domyślne, jeśli Kompozyt ma odpowiedni destruktor wirtualny
    // KompozytRownolegly();
    // ~KompozytRownolegly() override;

    double symuluj(double wejscie) override;
};

#endif // KOMPOZYTROWNOGLEGLY_H
