#ifndef ENTITY_H
#define ENTITY_H

#include <iostream>
#include <memory>
#include "MyExceptions.h"

class Entity {
public:
    virtual ~Entity() = default;
    virtual void displayDetails() const = 0;
};

#endif // ENTITY_H
