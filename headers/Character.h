#ifndef CHARACTER_H
#define CHARACTER_H

#include "Entity.h"
#include <string>
#include <memory>

class Character : public Entity {
public:
    explicit Character(const std::string &name);

    Character(const Character &other);

    Character &operator=(const Character &other);

    ~Character() override = default;

    [[nodiscard]] const std::string &getName() const;


    void displayDetails() const override;

private:
    std::string name;
};

#endif // CHARACTER_H
