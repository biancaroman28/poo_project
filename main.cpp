#include <iostream>
#include <ctime> // Pentru srand

#include "Joc.h"

int main() {
    srand(static_cast<unsigned int>(time(nullptr))); // Inițializăm generatorul de numere aleatoare

    Joc joc;

    std::cout << "Bun venit in aventura noastra!\n\n";

    std::cout << "Detalii despre obiecte:" << std::endl;
    for (const auto &obiect: joc.getObiecte()) {
        obiect->afiseazaDetalii();
        std::cout << std::endl;
    }

    std::cout << "Detalii despre personaje:" << std::endl;
    for (const auto &personaj: joc.getPersonaje()) {
        personaj->afiseazaDetalii();
        std::cout << std::endl;
    }

    std::cout << "Detalii despre locatii:" << std::endl;
    for (const auto &locatie: joc.getLocatii()) {
        locatie->afiseazaDetalii();
        std::cout << std::endl;
    }

    while (true) {
        std::cout
                << "\nIntrodu o comanda ('locatii', 'exploreaza', 'iesi', 'stare', 'intoarcere', 'energie', 'sanatate'): ";
        std::string comanda;
        std::cin >> comanda;

        if (comanda == "locatii") {
            joc.scrieLocatii();
        } else if (comanda == "exploreaza") {
            std::cout << "Alege o locatie pentru a explora: ";
            std::string locatie;
            std::cin >> locatie;

            joc.exploreazaLocatie(locatie);
            joc.scrieProvocariInLocatie(locatie);
            joc.scriePersonajeInLocatie(locatie);

            std::cout << "Vrei sa iei un obiect din aceasta locatie? ('da'/'nu'): ";
            std::string raspuns;
            std::cin >> raspuns;

            if (raspuns == "da") {
                std::cout << "Ce obiect vrei sa iei?: ";
                std::string obiect;
                std::cin >> obiect;

                try {
                    std::unique_ptr<Obiect> obiectLuat = joc.iaObiect(obiect);
                    std::cout << "Ai luat " << obiect << ". Sa te distrezi!\n";

                    // Afișează dacă obiectul a fost folosit sau nu
                    std::cout << "Obiectul '" << obiect << "' a fost folosit? "
                              << (obiectLuat->aFostFolosit() ? "Da" : "Nu") << std::endl;
                } catch (const ObiectNegasitException &ex) {
                    std::cout << "Exceptie: " << ex.what() << std::endl;
                }
            }
        } else if (comanda == "stare") {
            std::cout << "Starea obiectelor:\n";
            for (const auto &obiect: joc.getObiecte()) {
                obiect->afiseazaStarea();
            }
        } else if (comanda == "intoarcere") {
            Joc::reducereViata();
            joc.salveazaStareJoc();
            joc.afiseazaIstoric();
        } else if (comanda == "energie") {
            std::cout << "Energia: " << Joc::genereazaEnergie() << std::endl;
        } else if (comanda == "sanatate") {
            std::cout << "Sanatatea: " << Joc::genereazaSanatate() << std::endl;
        } else if (comanda == "iesi") {
            std::cout << "Ai iesit din joc.\n";
            break;
        } else {
            std::cout << "Comanda invalida. Incearca din nou.\n";
        }
    }

    return 0;
}
