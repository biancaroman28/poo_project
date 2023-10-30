#include <iostream>
#include <utility>
#include <vector>
#include <string>
#include <map>

class Obiect {
private:
    std::string nume;
    bool folosit;

public:
    explicit Obiect(std::string n) : nume(std::move(n)), folosit(false) {}

    Obiect(const Obiect &other) : nume(other.nume), folosit(other.folosit) {}


    Obiect &operator=(const Obiect &other) {
        if (&other == this)
            return *this;
        nume = other.nume;
        folosit = other.folosit;
        return *this;
    }

    ~Obiect() = default;

    friend std::ostream &operator<<(std::ostream &os, const Obiect &obj) {
        os << obj.nume;
        return os;
    }

    void obiectFolosit() {
        if (!folosit) {
            std::cout << "Ai folosit " << nume << std::endl;
            folosit = true;
        } else
            std::cout << nume << " a fost deja folosit." << std::endl;
    }

    [[nodiscard]] bool aFostFolosit() const {
        return folosit;
    }

    [[nodiscard]] const std::string &getnume() const {
        return nume;
    }
};


class Personaj {
private:
    std::string nume;

public:
    explicit Personaj(const std::string &n) : nume(n) {}

    Personaj(const Personaj &other) : nume(other.nume) {}

    Personaj &operator=(const Personaj &other) {
        if (this == &other) {
            return *this;
        }
        nume = other.nume;
        return *this;
    }

    ~Personaj() = default;

    friend std::ostream &operator<<(std::ostream &os, const Personaj &personaj) {
        os << personaj.nume;
        return os;
    }

    [[nodiscard]] const std::string &getNume() const {
        return nume;
    }
};

class Locatie {
private:
    std::string nume;
    std::string descriere;
    std::vector<std::string> provocariLocatie;

public:
    Locatie(const std::string &n, const std::string &desc) : nume(n), descriere(desc) {}

    Locatie(const Locatie &other) : nume(other.nume), descriere(other.descriere) {}

    Locatie &operator=(const Locatie &other) {
        if (this == &other) {
            return *this;
        }
        nume = other.nume;
        descriere = other.descriere;
        return *this;
    }

    ~Locatie() = default;

    friend std::ostream &operator<<(std::ostream &os, const Locatie &locatie) {
        os << locatie.nume;
        return os;
    }

    [[nodiscard]] const std::string &getNume() const {
        return nume;
    }

    [[nodiscard]] const std::string &getDescriere() const {
        return descriere;
    }

    [[nodiscard]] const std::vector<std::string> &getProvocariLocatie() const {
        return provocariLocatie;
    }

    void adaugaProvocare(const std::string &provocare) {
        provocariLocatie.emplace_back(provocare);
    }
};

class Joc {
private:
    std::vector<Obiect> obiecte;
    std::vector<Personaj> personaje;
    std::vector<Locatie> locatii;
    std::map<std::string, std::vector<Personaj>> personajeInLocatii;
    std::map<std::string, std::vector<std::string>> provocariInLocatii;

public:
    Joc() {
        obiecte.emplace_back("Lanterna");
        obiecte.emplace_back("Cheie");
        obiecte.emplace_back("Trusa de prim ajutor");
        obiecte.emplace_back("Franghie");
        obiecte.emplace_back("Arma");
        obiecte.emplace_back("Pietre pretioase");

        personaje.emplace_back("Vrajitor");
        personaje.emplace_back("Explorator");
        personaje.emplace_back("Vanator");
        personaje.emplace_back("Animal");

        locatii.emplace_back("Padure", "O padure misterioasa cu copaci inalti.");
        locatii.emplace_back("Pestera", "O pestera intunecata si inspaimantatoare.");
        locatii.emplace_back("Munte", "Varful unui munte inzapezit.");
        locatii.emplace_back("Oras", "Un oras in ruina si pustiu.");

        personajeInLocatii["Padure"] = {personaje[0], personaje[3]};
        personajeInLocatii["Pestera"] = {personaje[2]};
        personajeInLocatii["Munte"] = {personaje[1]};
        personajeInLocatii["Oras"] = {personaje[0], personaje[2]};

        locatii[0].adaugaProvocare("Monstru din Padure");
        locatii[1].adaugaProvocare("Labirint din Pestera");
    }

    void scrieLocatii() {
        std::cout << "Locatii disponibile: ";
        for (const Locatie &locatie: locatii) {
            std::cout << locatie << " ";
        }
        std::cout << std::endl;
    }

    void exploreazaLocatie(const std::string &locatie) {
        std::cout << "Esti in " << locatie << ". " << getLocatieDescriere(locatie) << std::endl;
        scrieProvocariInLocatie(locatie);
    }

    const std::string &getLocatieDescriere(const std::string &locatie) {
        for (const Locatie &loc: locatii) {
            if (loc.getNume() == locatie) {
                return loc.getDescriere();
            }
        }
        static const std::string empty = "Locatie necunoscuta.";
        return empty;
    }

    void scriePersonajeInLocatie(const std::string &locatie) {
        std::cout << "Personaje in " << locatie << ": ";
        const auto &personajeInLocatie = personajeInLocatii[locatie];
        for (const Personaj &personaj: personajeInLocatie) {
            std::cout << personaj << " ";
        }
        std::cout << std::endl;
    }

    void scrieProvocariInLocatie(const std::string &locatie) {
        std::cout << "Provocari in " << locatie << ": ";
        const auto &provocariInLocatie = locatii[0].getProvocariLocatie();
        for (const std::string &provocare: provocariInLocatie) {
            std::cout << provocare << " ";
        }
        std::cout << std::endl;
    }

    Obiect iaObiect(const std::string &objectnume) {
        for (auto &obj: obiecte) {
            if (!obj.aFostFolosit() && obj.getnume() == objectnume) {
                obj.obiectFolosit();
                return obj;
            }
        }
    }
};

int main() {


    Joc aventura;

    while (true) {
        std::cout
                << "Ce vrei sa faci? (scrie 'locatii' pentru a afisa locatiile, 'exploreaza' pentru a explora o locatie, 'provocari' pentru a vedea provocarile, 'obiect' pentru a folosi un obiect, 'iesi' pentru a iesi din joc): ";
        std::string comanda;
        std::cin >> comanda;

        if (comanda == "locatii") {
            aventura.scrieLocatii();
        } else if (comanda == "exploreaza") {
            std::cout << "Alege o locatie pentru a explora: ";
            std::string locatie;
            std::cin >> locatie;
            aventura.exploreazaLocatie(locatie);
            aventura.scriePersonajeInLocatie(locatie);
        } else if (comanda == "provocari") {
            std::cout << "Alege o locatie pentru a vedea provocarile disponibile: ";
            std::string locatie;
            std::cin >> locatie;
            aventura.scrieProvocariInLocatie(locatie);
        } else if (comanda == "obiect") {
            std::cout << "Ce obiect vrei sa folosesti?: ";
            std::string obiect;
            std::cin >> obiect;
            Obiect obiectLuat = aventura.iaObiect(obiect);
            std::cout << "Ai luat " << obiectLuat << std::endl;
        } else if (comanda == "iesi") {
            std::cout << "Ai iesit din joc." << std::endl;
            break;
        } else {
            std::cout << "Comanda invalida. Incearca din nou." << std::endl;
        }
    }

    return 0;
}