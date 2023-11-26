#include "Obiect.h"
#include <iostream>

Obiect::Obiect(const std::string& nume) : Entitate(), nume(nume), folosit(false) {}

Obiect::Obiect(const Obiect& other) : Entitate(other), nume(other.nume), folosit(other.folosit) {}

Obiect& Obiect::operator=(const Obiect& other) {
    if (this == &other) {
        return *this;
    }
    Entitate::operator=(other);
    nume = other.nume;
    folosit = other.folosit;
    return *this;
}

std::unique_ptr<Entitate> Obiect::clone() const {
    return std::make_unique<Obiect>(*this);
}

void Obiect::afiseazaDetalii() const  {
    std::cout << "Detalii despre obiectul '" << nume << "':" <<
              std::endl;
    std::cout << "Nume obiect: " << nume <<
              std::endl;
    std::cout << "Folosit: " << (folosit ? "Da" : "Nu") <<
              std::endl;
}
bool Obiect::aFostFolosit() const {
    return folosit;
}

const std::string& Obiect::getNume() const {
    return nume;
}

void Obiect::obiectFolosit() {
    folosit = true;
}
void Obiect::afiseazaStarea() const {
    std::cout << "Obiectul '" << nume << "' a fost folosit? " << (folosit ? "Da" : "Nu") << std::endl;
}