#include "../headers/Object.h"
#include <iostream>

Object::Object(const std::string &name) : Entity(), name(name), used(false) {}

Object::Object(const Object &other) : Entity(other), name(other.name), used(other.used) {}

Object &Object::operator=(const Object &other) {
    if (this == &other) {
        return *this;
    }
    Entity::operator=(other);
    name = other.name;
    used = other.used;
    return *this;
}

/*
std::unique_ptr<Entity> Object::clone() const {
    return std::make_unique<Object>(*this);
}
*/

void Object::displayDetails() const {
    std::cout << "Details about the object '" << name << "':" << std::endl;
    std::cout << "Object name: " << name << std::endl;
    std::cout << "Used: " << (used ? "Yes" : "No") << std::endl;
}

bool Object::hasBeenUsed() const {
    return used;
}

const std::string &Object::getName() const {
    return name;
}

void Object::useObject() {
    used = true;
}

void Object::displayState() const {
    std::cout << "Has the object '" << name << "' been used? " << (used ? "Yes" : "No") << std::endl;
}
