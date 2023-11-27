#ifndef LOCATIE_H
#define LOCATIE_H

#include "Entitate.h"
#include <string>
#include <vector>

class Locatie : public Entitate {
public:
    Locatie(const std::string &n, const std::string &desc);

    Locatie(const Locatie &other);

    Locatie &operator=(const Locatie &other);

    ~Locatie() override;

    [[nodiscard]] const std::string &getNume() const;

    [[nodiscard]] const std::string &getDescriere() const;

    /// [[nodiscard]] const std::vector<std::string>& getProvocariLocatie() const;
    void adaugaProvocare(const std::string &provocare);

    void afiseazaDetalii() const override;

    [[nodiscard]] std::unique_ptr<Entitate> clone() const override;

private:
    std::string nume;
    std::string descriere;
    std::vector<std::string> provocariLocatie;
};

#endif // LOCATIE_H
