#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <cstdlib>
#include <map>

class Obiect {
private:
    std::string nume;
    bool folosit;

public:
    Obiect(const std::string &n) : nume(n), folosit(false) {}

    Obiect(const Obiect &other) : nume(other.nume), folosit(other.folosit) {}

    Obiect &operator=(const Obiect &other) {
        if (&other == this)
            return *this;
        nume = other.nume;
        folosit = other.folosit;
        return *this;
    }

    ~Obiect() {}

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

    bool aFostFolosit() const {
        return folosit;
    }

    const std::string &getnume() const {
        return nume;
    }
};

class Personaj {
private:
    std::string nume;

public:
    Personaj(const std::string &n) : nume(n) {}

    Personaj(const Personaj &other) : nume(other.nume) {}

    Personaj &operator=(const Personaj &other) {
        if (this == &other) {
            return *this;
        }
        nume = other.nume;
        return *this;
    }

    ~Personaj() {}

    friend std::ostream &operator<<(std::ostream &os, const Personaj &personaj) {
        os << personaj.nume;
        return os;
    }

    const std::string &getNume() const {
        return nume;
    }

    void vorbeste() const {
        std::cout << nume << " iti spune: 'Bine ai venit.' " << std::endl;
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

    ~Locatie() {}

    friend std::ostream &operator<<(std::ostream &os, const Locatie &locatie) {
        os << locatie.nume;
        return os;
    }

    const std::string &getNume() const {
        return nume;
    }

    const std::string &getDescriere() const {
        return descriere;
    }

    const std::vector<std::string> &getProvocariLocatie() const {
        return provocariLocatie;
    }

    void adaugaProvocare(const std::string &provocare) {
        provocariLocatie.push_back(provocare);
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
        obiecte.push_back(Obiect("Lanterna"));
        obiecte.push_back(Obiect("Cheie"));
        obiecte.push_back(Obiect("Trusa de prim ajutor"));
        obiecte.push_back(Obiect("Franghie"));
        obiecte.push_back(Obiect("Arma"));
        obiecte.push_back(Obiect("Pietre pretioase"));

        personaje.push_back(Personaj("Vrajitor"));
        personaje.push_back(Personaj("Explorator"));
        personaje.push_back(Personaj("Vanator"));
        personaje.push_back(Personaj("Animal"));

        locatii.push_back(Locatie("Padure", "O padure misterioasa cu copaci inalti."));
        locatii.push_back(Locatie("Pestera", "O pestera intunecata si inspaimantatoare."));
        locatii.push_back(Locatie("Munte", "Varful unui munte inzapezit."));
        locatii.push_back(Locatie("Oras", "Un oras in ruina si pustiu."));

        personajeInLocatii["Padure"] = {personaje[0], personaje[3]};
        personajeInLocatii["Pestera"] = {personaje[2]};
        personajeInLocatii["Munte"] = {personaje[1]};
        personajeInLocatii["Oras"] = {personaje[0], personaje[2]};

        // Adaugăm provocările în locații
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
        return Obiect("obj");
    }
};

int main() {
    srand(static_cast<unsigned>(time(0)));

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
        } else if (comanda == "") {
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

