#include "Locatie.h"
/////
Locatie::Locatie(const std::string &n, const std::string &desc) : Entitate(), nume(n), descriere(desc) {}

Locatie::Locatie(const Locatie &other)
        : Entitate(other), nume(other.nume), descriere(other.descriere), provocariLocatie(other.provocariLocatie) {}

Locatie &Locatie::operator=(const Locatie &other) {
    if (this == &other) {
        return *this;
    }
    Entitate::operator=(other);
    nume = other.nume;
    descriere = other.descriere;
    provocariLocatie = other.provocariLocatie;
    return *this;
}


Locatie::~Locatie() = default;


const std::string &Locatie::getNume() const {
    return nume;
}

const std::string &Locatie::getDescriere() const {
    return descriere;
}

/*
const std::vector<std::string>& Locatie::getProvocariLocatie() const {
    return provocariLocatie;
}
*/
void Locatie::adaugaProvocare(const std::string &provocare) {
    provocariLocatie.push_back(provocare);
}

void Locatie::afiseazaDetalii() const {
    std::cout << "Detalii despre locatia '" << nume << "':" << std::endl;
    std::cout << "Nume locatie: " << nume << std::endl;
    std::cout << "Descriere: " << descriere << std::endl;
    std::cout << "Provocari disponibile:";
    for (const auto &provocare: provocariLocatie) {
        std::cout << " " << provocare;
    }
    std::cout << std::endl;
}
/*
// Implementare a metodei clone pentru a evita eroarea
std::unique_ptr<Entitate> Locatie::clone() const {
    return std::make_unique<Locatie>(*this);
}
*/
