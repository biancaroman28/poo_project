#ifndef LOCATION_H
#define LOCATION_H

#include "Entity.h"
#include <string>
#include <vector>

class Location : public Entity {
public:
    Location(const std::string &name, const std::string &description);

    Location(const Location &other);

    Location &operator=(const Location &other);

    ~Location() override;

    [[nodiscard]] const std::string &getName() const;

    [[nodiscard]] const std::string &getDescription() const;

    // [[nodiscard]] const std::vector<std::string>& getLocationChallenges() const;
    void addChallenge(const std::string &challenge);

    void displayDetails() const override;

    // [[nodiscard]] std::unique_ptr<Entity> clone() const override;

private:
    std::string name;
    std::string description;
    std::vector<std::string> locationChallenges;
};

#endif // LOCATION_H
