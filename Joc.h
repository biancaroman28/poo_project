#ifndef JOC_H
#define JOC_H

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include "Obiect.h"
#include "Personaj.h"
#include "Locatie.h"

class Joc {
private:
    std::vector<std::unique_ptr<Obiect>> obiecte;
    std::vector<std::unique_ptr<Personaj>> personaje;
    std::vector<std::unique_ptr<Locatie>> locatii;
    std::map<std::string, std::vector<Personaj>> personajeInLocatii;
    std::map<std::string, std::vector<std::string>> provocariInLocatii;
    static int numarVieti;
    std::vector<std::unique_ptr<Locatie>> istoricLocatii;
    std::vector<std::unique_ptr<Personaj>> istoricPersonaje;
    std::vector<std::unique_ptr<Obiect>> istoricObiecte;
    ///static static std::unique_ptr<Personaj> convertToPersonaj(std::unique_ptr<Entitate>& entitate);


public:
    Joc();

    [[nodiscard]] const std::vector<std::unique_ptr<Obiect>> &getObiecte() const;

    [[nodiscard]] const std::vector<std::unique_ptr<Personaj>> &getPersonaje() const;

    [[nodiscard]] const std::vector<std::unique_ptr<Locatie>> &getLocatii() const;

    void scrieLocatii();

    void exploreazaLocatie(const std::string &locatie);

    const std::string &getLocatieDescriere(const std::string &locatie);

    void scriePersonajeInLocatie(const std::string &locatie);

    void scrieProvocariInLocatie(const std::string &locatie);

    std::unique_ptr<Obiect> iaObiect(const std::string &objectnume);

    static int genereazaSanatate();

    static int genereazaEnergie();

    static void reducereViata();

    void salveazaStareJoc();

    void afiseazaIstoric();

};

#endif // JOC_H
