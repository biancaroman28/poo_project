#ifndef OBIECT_H
#define OBIECT_H

#include "Entitate.h"
#include <string>

class Obiect : public Entitate {
public:
    explicit Obiect(const std::string &nume);

    ~Obiect() override = default;

    [[nodiscard]] const std::string &getNume() const;

    void obiectFolosit();

    [[nodiscard]] bool aFostFolosit() const;

    Obiect(const Obiect &other);

    Obiect &operator=(const Obiect &other);
/*
    [[nodiscard]] std::unique_ptr<Entitate> clone() const override;
*/
    void afiseazaDetalii() const override;

    void afiseazaStarea() const;

private:
    std::string nume;
    bool folosit;
};

#endif // OBIECT_H
