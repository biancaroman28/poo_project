#include "Joc.h"
#include <iostream>
#include "MyExceptions.h"

Joc::Joc() {
    obiecte.push_back(std::make_unique<Obiect>("Lanterna"));
    obiecte.push_back(std::make_unique<Obiect>("Cheie"));
    obiecte.push_back(std::make_unique<Obiect>("Trusa de prim ajutor"));
    obiecte.push_back(std::make_unique<Obiect>("Franghie"));
    obiecte.push_back(std::make_unique<Obiect>("Arma"));
    obiecte.push_back(std::make_unique<Obiect>("Pietre pretioase"));

    personaje.push_back(std::make_unique<Personaj>("Vrajitor"));
    personaje.push_back(std::make_unique<Personaj>("Explorator"));
    personaje.push_back(std::make_unique<Personaj>("Vanator"));
    personaje.push_back(std::make_unique<Personaj>("Animal"));

    locatii.push_back(std::make_unique<Locatie>("Padure", "O padure misterioasa cu copaci inalti."));
    locatii.push_back(std::make_unique<Locatie>("Pestera", "O pestera intunecata si inspaimantatoare."));
    locatii.push_back(std::make_unique<Locatie>("Munte", "Varful unui munte inzapezit."));
    locatii.push_back(std::make_unique<Locatie>("Oras", "Un oras in ruina si pustiu."));

    personajeInLocatii["Padure"] = {*(personaje[0]), *(personaje[3])};
    personajeInLocatii["Pestera"] = {*(personaje[2])};
    personajeInLocatii["Munte"] = {*(personaje[1])};
    personajeInLocatii["Oras"] = {*(personaje[0]), *(personaje[2])};

    locatii[0]->adaugaProvocare("Monstru din Padure");
    locatii[1]->adaugaProvocare("Labirint din Pestera");
}

void Joc::scrieLocatii() {
    std::cout << "Locatii disponibile: ";
    for (const auto &locatie: locatii) {
        std::cout << locatie->getNume() << " ";
    }
    std::cout << std::endl;
}

/*
void Joc::scrieObiecte() {
    std::cout<<"Obiecte disponibile: ";
    for (const auto&obiect:obiecte){
        std::cout <<obiect->getNume() << " ";
    }
}
*/
void Joc::exploreazaLocatie(const std::string &locatie) {
    std::cout << "Esti in " << locatie << ". " << getLocatieDescriere(locatie) << std::endl;
    scrieProvocariInLocatie(locatie);
}

const std::string &Joc::getLocatieDescriere(const std::string &locatie) {
    for (const auto &loc: locatii) {
        if (loc->getNume() == locatie) {
            return loc->getDescriere();
        }
    }
    static const std::string empty = "Locatie necunoscuta.";
    return empty;
}

void Joc::scriePersonajeInLocatie(const std::string &locatie) {
    std::cout << "Personaje in " << locatie << ": ";
    const auto &personajeInLocatie = personajeInLocatii[locatie];
    for (const auto &personaj: personajeInLocatie) {
        std::cout << personaj.getNume() << " ";
    }
    std::cout << std::endl;
}

void Joc::scrieProvocariInLocatie(const std::string &locatie) {
    std::cout << "Provocari in " << locatie << ": ";
    const auto &provocariInLocatie = provocariInLocatii[locatie];
    for (const auto &provocare: provocariInLocatie) {
        std::cout << provocare << " ";
    }
    std::cout << std::endl;
}


std::unique_ptr<Obiect> Joc::iaObiect(const std::string &objectnume) {
    for (auto &obj: obiecte) {
        if (!obj->aFostFolosit() && obj->getNume() == objectnume) {
            obj->obiectFolosit();
            return std::move(obj);
        }
    }
    throw ObiectNegasitException();
}

const std::vector<std::unique_ptr<Obiect>> &Joc::getObiecte() const {
    return obiecte;
}

const std::vector<std::unique_ptr<Locatie>> &Joc::getLocatii() const {
    return locatii;
}

const std::vector<std::unique_ptr<Personaj>> &Joc::getPersonaje() const {
    return personaje;
}

int Joc::numarVieti = 3; // Inițializarea numărului de vieți

int Joc::genereazaSanatate() {
    return rand() % 101; // Generează un număr aleator între 0 și 100 pentru sănătate
}

int Joc::genereazaEnergie() {
    return rand() % 101; // Generează un număr aleator între 0 și 100 pentru energie
}

void Joc::reducereViata() {
    if (numarVieti > 0) {
        numarVieti--;
        std::cout << "Numarul de vieti a scazut. Mai ai " << numarVieti << " vieti.\n";
    } else {
        std::cout << "Ai ramas fara vieti!\n";
    }
}

void Joc::salveazaStareJoc() {
    istoricLocatii.clear();
    for (const auto &locatie: locatii) {
        istoricLocatii.emplace_back(new Locatie(*locatie));
    }

    istoricPersonaje.clear();
    for (const auto &personaj: personaje) {
        istoricPersonaje.emplace_back(new Personaj(*personaj));
    }

    istoricObiecte.clear();
    for (const auto &obiect: obiecte) {
        if (obiect->aFostFolosit()) {
            istoricObiecte.emplace_back(new Obiect(*obiect));
        }
    }

    std::cout << "Starea jocului a fost salvata.\n";
}

void Joc::afiseazaIstoric() {
    std::cout << "\n--- Istoricul Jocului ---\n";

    std::cout << "Istoric Locatii:\n";
    for (const auto &locatie: istoricLocatii) {
        locatie->afiseazaDetalii();
    }

    std::cout << "\nIstoric Personaje:\n";
    for (const auto &personaj: istoricPersonaje) {
        personaj->afiseazaDetalii();
    }

    std::cout << "\nIstoric Obiecte Folosite:\n";
    for (const auto &obiect: istoricObiecte) {
        obiect->afiseazaDetalii();
    }
}

/*
std::unique_ptr<Personaj> Joc::convertToPersonaj(std::unique_ptr<Entitate>& entitate) {
    if (auto* personaj = dynamic_cast<Personaj*>(entitate.get())) {
        return std::unique_ptr<Personaj>(dynamic_cast<Personaj*>(entitate.release()));
    }
    return nullptr;
}

*/