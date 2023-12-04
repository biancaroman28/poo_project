#include "../headers/Character.h"
#include "../headers/Entity.h"
#include <iostream>

Character::Character(const std::string &name) : Entity(), name(name) {}

Character::Character(const Character &other) : Entity(other), name(other.name) {}

Character &Character::operator=(const Character &other) {
    if (this == &other) {
        return *this;
    }
    Entity::operator=(other);
    name = other.name;
    return *this;
}

/*
std::unique_ptr<Entity> Character::clone() const {
    return std::make_unique<Character>(*this);
}
*/

void Character::displayDetails() const {
    std::cout << "Details about the character '" << name << "':" << std::endl;
    std::cout << "Character name: " << name << std::endl;

}

const std::string &Character::getName() const {
    return name;
}
