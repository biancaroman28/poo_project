#include "../headers/Location.h"

Location::Location(const std::string &name, const std::string &description)
        : Entity(), name(name), description(description) {}

Location::Location(const Location &other)
        : Entity(other), name(other.name), description(other.description), locationChallenges(other.locationChallenges) {}

Location &Location::operator=(const Location &other) {
    if (this == &other) {
        return *this;
    }
    Entity::operator=(other);
    name = other.name;
    description = other.description;
    locationChallenges = other.locationChallenges;
    return *this;
}

Location::~Location() = default;

const std::string &Location::getName() const {
    return name;
}

const std::string &Location::getDescription() const {
    return description;
}

/*
const std::vector<std::string>& Location::getLocationChallenges() const {
    return locationChallenges;
}
*/

void Location::addChallenge(const std::string &challenge) {
    locationChallenges.push_back(challenge);
}

void Location::displayDetails() const {
    std::cout << "Details about the location '" << name << "':" << std::endl;
    std::cout << "Location name: " << name << std::endl;
    std::cout << "Description: " << description << std::endl;
    std::cout << "Available challenges:";
    for (const auto &challenge : locationChallenges) {
        std::cout << " " << challenge;
    }
    std::cout << std::endl;
}
/*
std::unique_ptr<Entity> Location::clone() const {
    return std::make_unique<Location>(*this);
}
*/
