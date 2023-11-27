#ifndef PERSONAJ_H
#define PERSONAJ_H

#include "Entitate.h" // Include Entitate.h aici, după forward declaration
#include <string>
#include <memory>

class Personaj : public Entitate {
public:
    explicit Personaj(const std::string &nume);

    Personaj(const Personaj &other);

    Personaj &operator=(const Personaj &other);

    ~Personaj() override = default;

    [[nodiscard]] const std::string &getNume() const;

    [[nodiscard]] std::unique_ptr<Entitate> clone() const override;

    void afiseazaDetalii() const override;


private:
    std::string nume;
};

#endif // PERSONAJ_H