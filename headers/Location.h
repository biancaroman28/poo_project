#ifndef LOCATION_H
#define LOCATION_H

#include "Entity.h"
#include <iostream>
#include <string>
#include <vector>
#include <memory>

class LocationState {
public:
    virtual void performAction() = 0;
    virtual ~LocationState() = default;
};

class NonDangerousLocationState : public LocationState {
public:
    void performAction() override;
};

class MildlyDangerousLocationState : public LocationState {
public:
    void  performAction() override;
};

class VeryDangerousLocationState : public LocationState {
public:
    void  performAction() override;
};

// Forward declaration of LocationVisitedObserver
class LocationVisitedObserver;

template<int Attr1, int Attr2>
class Location : public Entity {
public:
    Location(const std::string& name, const std::string& description, int attr1Value, int attr2Value);
    void setAttributes(int attr1Value, int attr2Value);
    void performAction();
    void markVisited();
    [[nodiscard]] bool isVisited() const;
    [[nodiscard]] const std::string &getName() const;
    [[nodiscard]] const std::string &getDescription() const;
    void addChallenge(const std::string &challenge);
    void displayDetails() const override;
    [[nodiscard]] int getDangerLevel() const;
    void attachObserver(LocationVisitedObserver* obs);
    void notifyObservers();

private:
    std::string name;
    std::string description;
    int attr1 = 0;
    int attr2 = 0;
    bool visited = false;
    std::unique_ptr<LocationState> currentState;
    std::vector<LocationVisitedObserver*> observers;
    std::vector<std::string> locationChallenges;
};

class LocationVisitedObserver {
public:
    // Declaration for update function
    void update(const Location<0, 11>* location);
};

#endif // LOCATION_H
