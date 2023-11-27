#ifndef ENTITATE_H
#define ENTITATE_H

#include <iostream>
#include <memory>
#include "MyExceptions.h"

class Entitate {
public:
    virtual ~Entitate() = default;

///    [[nodiscard]] virtual std::unique_ptr<Entitate> clone() const = 0;

    virtual void afiseazaDetalii() const = 0;

};

#endif // ENTITATE_H
