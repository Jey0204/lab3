#include <iostream>
#include <cassert>
#include <cmath> // Dla std::fabs do porównywania liczb zmiennoprzecinkowych

#include "Komponent.h"
#include "Mnoznik.h"
#include "Kompozyt.h" // Zawiera getLiczbaDzieci
#include "KompozytRownolegly.h"
#include "KompozytSzeregowy.h"

// Definicja małej wartości epsilon do porównywania liczb zmiennoprzecinkowych
const double EPSILON = 1e-9;

// --- Prototypy funkcji testujących ---
void test_Mnoznik();
void test_Kompozyt_dodaj_usun();
void test_KompozytRownolegly_symuluj();
void test_KompozytSzeregowy_symuluj();
void test_ZagniezdzonychKompozytow();

int main() {
    std::cout << "Rozpoczynam testy komponentow..." << std::endl;

    test_Mnoznik();
    std::cout << "Testy Mnoznik zakonczone." << std::endl;

    test_Kompozyt_dodaj_usun();
    std::cout << "Testy Kompozyt (dodaj/usun) zakonczone." << std::endl;

    test_KompozytRownolegly_symuluj();
    std::cout << "Testy KompozytRownolegly (symuluj) zakonczone." << std::endl;

    test_KompozytSzeregowy_symuluj();
    std::cout << "Testy KompozytSzeregowy (symuluj) zakonczone." << std::endl;

    test_ZagniezdzonychKompozytow();
    std::cout << "Testy zagniezdzonych kompozytow zakonczone." << std::endl;

    std::cout << "Wszystkie testy komponentow zakonczone sukcesem!" << std::endl;
    return 0;
}

// --- Implementacje funkcji testujących ---

void test_Mnoznik() {
    std::cout << "  Testowanie Mnoznik::symuluj..." << std::endl;
    Mnoznik m1(2.5);
    assert(std::fabs(m1.symuluj(10.0) - 25.0) < EPSILON);
    assert(std::fabs(m1.symuluj(0.0) - 0.0) < EPSILON);
    assert(std::fabs(m1.symuluj(-4.0) - (-10.0)) < EPSILON);

    Mnoznik m2(0.0);
    assert(std::fabs(m2.symuluj(100.0) - 0.0) < EPSILON);
}

// Klasa pomocnicza dziedzicząca z Kompozyt, aby móc go bezpośrednio przetestować
// (Kompozyt ma czysto wirtualną metodę symuluj)
class TestKompozyt : public Kompozyt {
public:
    double symuluj(double wejscie) override {
        // Prosta implementacja, nieistotna dla testów dodaj/usun
        return wejscie; 
    }
};

void test_Kompozyt_dodaj_usun() {
    std::cout << "  Testowanie Kompozyt::dodaj i Kompozyt::usun..." << std::endl;
    TestKompozyt kompozyt;
    Mnoznik* m1 = new Mnoznik(1.0);
    Mnoznik* m2 = new Mnoznik(2.0);

    assert(kompozyt.getLiczbaDzieci() == 0);

    kompozyt.dodaj(m1);
    assert(kompozyt.getLiczbaDzieci() == 1);

    kompozyt.dodaj(m2);
    assert(kompozyt.getLiczbaDzieci() == 2);

    kompozyt.usun(m1); // Usuwamy m1
    assert(kompozyt.getLiczbaDzieci() == 1);
    
    // Sprawdzenie, czy pozostał właściwy komponent (m2)
    // To wymagałoby sposobu na identyfikację komponentów, np. przez symulację lub ID
    // Na razie zakładamy, że usunięcie działa poprawnie na podstawie liczby dzieci.
    // Destruktor TestKompozyt (a dokładniej Kompozyt) powinien zająć się usunięciem m2.

    kompozyt.usun(m2);
    assert(kompozyt.getLiczbaDzieci() == 0);

    // Test usuwania nieistniejącego komponentu
    Mnoznik* m3 = new Mnoznik(3.0); // m3 nie jest dodany
    kompozyt.usun(m3);
    assert(kompozyt.getLiczbaDzieci() == 0);
    delete m3; // m3 nie był własnością kompozytu, trzeba go usunąć ręcznie

    // Test dodawania nullptr
    kompozyt.dodaj(nullptr);
    assert(kompozyt.getLiczbaDzieci() == 0);

    // Test usuwania nullptr
    kompozyt.usun(nullptr);
    assert(kompozyt.getLiczbaDzieci() == 0);
}

void test_KompozytRownolegly_symuluj() {
    std::cout << "  Testowanie KompozytRownolegly::symuluj..." << std::endl;
    KompozytRownolegly rownolegly;
    double wejscie = 10.0;

    // Test z pustym kompozytem
    std::cout << "    Test z pustym kompozytem..." << std::endl;
    assert(std::fabs(rownolegly.symuluj(wejscie) - 0.0) < EPSILON); // Oczekiwane 0.0 dla pustego

    // Test z jednym komponentem
    std::cout << "    Test z jednym komponentem..." << std::endl;
    Mnoznik* m1 = new Mnoznik(2.0);
    rownolegly.dodaj(m1);
    assert(std::fabs(rownolegly.symuluj(wejscie) - (wejscie * 2.0)) < EPSILON);

    // Test z wieloma komponentami
    std::cout << "    Test z wieloma komponentami..." << std::endl;
    Mnoznik* m2 = new Mnoznik(3.0);
    Mnoznik* m3 = new Mnoznik(0.5);
    rownolegly.dodaj(m2);
    rownolegly.dodaj(m3);
    // Oczekiwany wynik: (10*2) + (10*3) + (10*0.5) = 20 + 30 + 5 = 55
    assert(std::fabs(rownolegly.symuluj(wejscie) - 55.0) < EPSILON);
    
    // Destruktor KompozytRownolegly automatycznie zwolni m1, m2, m3
}

void test_KompozytSzeregowy_symuluj() {
    std::cout << "  Testowanie KompozytSzeregowy::symuluj..." << std::endl;
    KompozytSzeregowy szeregowy;
    double wejscie = 10.0;

    // Test z pustym kompozytem
    std::cout << "    Test z pustym kompozytem..." << std::endl;
    assert(std::fabs(szeregowy.symuluj(wejscie) - wejscie) < EPSILON); // Oczekiwane wejście bez zmian

    // Test z jednym komponentem
    std::cout << "    Test z jednym komponentem..." << std::endl;
    Mnoznik* m1_szeregowy = new Mnoznik(2.0); // Zmieniono nazwę, aby uniknąć konfliktu z m1 w test_KompozytRownolegly
    szeregowy.dodaj(m1_szeregowy);
    assert(std::fabs(szeregowy.symuluj(wejscie) - (wejscie * 2.0)) < EPSILON);
    // Po tym teście, m1_szeregowy jest własnością 'szeregowy' i zostanie przez nią zwolniony.
    // Nie trzeba robić delete m1_szeregowy; ani szeregowy.usun(m1_szeregowy); jeśli 'szeregowy' jest niszczony na końcu funkcji
    // lub jeśli 'szeregowy' jest czyszczony przed ponownym użyciem.
    // W tym przypadku 'szeregowy' jest obiektem lokalnym i jego destruktor zadba o m1_szeregowy.

    // Test z wieloma komponentami
    std::cout << "    Test z wieloma komponentami..." << std::endl;
    // Tworzymy nowy, czysty obiekt dla testu z wieloma komponentami, aby uniknąć interferencji.
    KompozytSzeregowy szeregowyWiele;
    szeregowyWiele.dodaj(new Mnoznik(2.0)); // wejscie * 2
    szeregowyWiele.dodaj(new Mnoznik(3.0)); // (wejscie * 2) * 3
    szeregowyWiele.dodaj(new Mnoznik(0.5)); // ((wejscie * 2) * 3) * 0.5
    // Oczekiwany wynik: ((10*2)*3)*0.5 = (20*3)*0.5 = 60*0.5 = 30
    assert(std::fabs(szeregowyWiele.symuluj(wejscie) - 30.0) < EPSILON);
    
    // Destruktory KompozytSzeregowy (szeregowy i szeregowyWiele) automatycznie zwolnią dodane mnożniki.
}

void test_ZagniezdzonychKompozytow() {
    std::cout << "  Testowanie zagniezdzonych kompozytow..." << std::endl;
    double wejscie = 10.0;

    // Test: Szeregowy w Równoległym
    std::cout << "    Test: Szeregowy w Rownoleglym..." << std::endl;
    KompozytRownolegly* rownolegly = new KompozytRownolegly();
    rownolegly->dodaj(new Mnoznik(4.0)); // Gałąź 1: 10.0 * 4.0 = 40.0

    KompozytSzeregowy* galazSzeregowa = new KompozytSzeregowy();
    galazSzeregowa->dodaj(new Mnoznik(2.0)); // 10.0 * 2.0 = 20.0
    galazSzeregowa->dodaj(new Mnoznik(1.5)); // 20.0 * 1.5 = 30.0
    rownolegly->dodaj(galazSzeregowa);       // Gałąź 2 (szeregowa)

    // Oczekiwany wynik: (10.0 * 4.0) + ((10.0 * 2.0) * 1.5) = 40.0 + (20.0 * 1.5) = 40.0 + 30.0 = 70.0
    assert(std::fabs(rownolegly->symuluj(wejscie) - 70.0) < EPSILON);
    delete rownolegly; // To zwolni Mnoznik(4.0) oraz galazSzeregowa (która zwolni swoje Mnozniki)

    // Test: Równoległy w Szeregowym
    std::cout << "    Test: Rownolegly w Szeregowym..." << std::endl;
    KompozytSzeregowy* szeregowy = new KompozytSzeregowy();
    szeregowy->dodaj(new Mnoznik(0.5)); // Krok 1: 10.0 * 0.5 = 5.0

    KompozytRownolegly* blokRownolegly = new KompozytRownolegly();
    blokRownolegly->dodaj(new Mnoznik(2.0)); // 5.0 * 2.0 = 10.0
    blokRownolegly->dodaj(new Mnoznik(3.0)); // 5.0 * 3.0 = 15.0
    szeregowy->dodaj(blokRownolegly);        // Krok 2 (równoległy): suma wyników = 10.0 + 15.0 = 25.0

    szeregowy->dodaj(new Mnoznik(2.0));      // Krok 3: 25.0 * 2.0 = 50.0

    // Oczekiwany wynik: (( (10.0 * 0.5) | równolegle: (*2) + (*3) ) * 2.0)
    // Krok 1 (Mnoznik(0.5)): 10.0 * 0.5 = 5.0
    // Krok 2 (blokRownolegly na wyniku 5.0): (5.0 * 2.0) + (5.0 * 3.0) = 10.0 + 15.0 = 25.0
    // Krok 3 (Mnoznik(2.0) na wyniku 25.0): 25.0 * 2.0 = 50.0
    assert(std::fabs(szeregowy->symuluj(wejscie) - 50.0) < EPSILON);
    delete szeregowy; // To zwolni Mnoznik(0.5), blokRownolegly (i jego dzieci) oraz Mnoznik(2.0)
}
