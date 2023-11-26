#include "Personaj.h"
#include "Entitate.h"
#include <iostream>


Personaj::Personaj(const std::string& nume) : Entitate(),nume(nume) {}

Personaj::Personaj(const Personaj& other) : Entitate(other), nume(other.nume) {}

Personaj& Personaj::operator=(const Personaj& other) {
    if (this == &other) {
        return *this;
    }
    Entitate::operator=(other);
    nume = other.nume;
    return *this;
}

std::unique_ptr<Entitate> Personaj::clone() const {
    return std::make_unique<Personaj>(*this);
}
void Personaj::afiseazaDetalii() const  {
    std::cout << "Detalii despre personajul '" << nume << "':" << std::endl;
    std::cout << "Nume personaj: " << nume << std::endl;
// Alte detalii specifice pentru personaje
}
const std::string& Personaj::getNume() const {
    return nume;
}
