#include "Location.h"

// LocationState subclass implementations
void NonDangerousLocationState::performAction()  {
    std::cout << "You are in a non-dangerous location." << std::endl;
}

void MildlyDangerousLocationState::performAction() {
    std::cout << "You are in a mildly dangerous location." << std::endl;
}

void VeryDangerousLocationState::performAction() {
    std::cout << "You are in a very dangerous location!" << std::endl;
}

void LocationVisitedObserver::update(const Location<0, 11>* location) {
    if (location->isVisited()) {
        std::cout << "Location '" << location->getName() << "' has been visited!" << std::endl;
    }
}

// Location template class member function implementations
template<int Attr1, int Attr2>
Location<Attr1, Attr2>::Location(const std::string& name, const std::string& description, int attr1Value, int attr2Value)
        : Entity(), name(name), description(description), attr1(attr1Value), attr2(attr2Value) {}

template<int Attr1, int Attr2>
void Location<Attr1, Attr2>::setAttributes(int attr1Value, int attr2Value) {
    static_assert(Attr1 == 0 || Attr1 == 1, "Attr1 must be 0 or 1");
    static_assert(Attr2 >= 10 && Attr2 <= 30, "Attr2 must be between 10 and 30");

    attr1 = attr1Value;
    attr2 = attr2Value;

    if constexpr (Attr2 >= 10 && Attr2 <= 19) {
        currentState=std::make_unique<NonDangerousLocationState>();
    } else if constexpr (Attr2 >= 20 && Attr2 <= 25) {
        currentState = std::make_unique<MildlyDangerousLocationState>();
    } else if constexpr (Attr2 >= 26 && Attr2 <= 30) {
        currentState = std::make_unique<VeryDangerousLocationState>();
    }
}

template<int Attr1, int Attr2>
int Location<Attr1, Attr2>::getDangerLevel() const {
    return Attr2;
}

template<int Attr1, int Attr2>
void Location<Attr1, Attr2>::performAction() {
    if (currentState) {
        currentState->performAction();
    } else {
        // Handle case where currentState is not set
        std::cout << "No state set for this location!" << std::endl;
    }
}

template<int Attr1, int Attr2>
void Location<Attr1, Attr2>::markVisited() {
   /// visited = true;
    notifyObservers();
}

template<int Attr1, int Attr2>
bool Location<Attr1, Attr2>::isVisited() const {
    return visited;
}


template<int Attr1, int Attr2>
const std::string& Location<Attr1, Attr2>::getName() const {
    return name;
}
/*
template<int Attr1, int Attr2>
const std::string& Location<Attr1, Attr2>::getDescription() const {
    return description;
}
*/
template<int Attr1, int Attr2>
void Location<Attr1, Attr2>::addChallenge(const std::string &challenge) {
    locationChallenges.push_back(challenge);
}

template<int Attr1, int Attr2>
void Location<Attr1, Attr2>::displayDetails() const {
    std::cout << "Details about the location '" << name << "':" << std::endl;
    std::cout << "Location name: " << name << std::endl;
    std::cout << "Description: " << description << std::endl;
    std::cout << "Attributes: " << attr1 << ", " << attr2 << std::endl;
    std::cout << "Available challenges:";
    for (const auto &challenge : locationChallenges) {
        std::cout << " " << challenge;
    }
    std::cout << std::endl;
}

template<int Attr1, int Attr2>
void Location<Attr1, Attr2>::attachObserver(LocationVisitedObserver* obs) {
    observers.push_back(obs);
}

template<int Attr1, int Attr2>
void Location<Attr1, Attr2>::notifyObservers() {
    for (auto observer : observers) {
        observer->update(this);
    }
}

// Explicit instantiation for specific template arguments
template class Location<0, 11>;
// Add more explicit instantiations for other template arguments if needed
