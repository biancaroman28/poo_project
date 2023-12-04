#ifndef OBJECT_H
#define OBJECT_H

#include "Entity.h"
#include <string>

class Object : public Entity {
public:
    explicit Object(const std::string &name);

    ~Object() override = default;

    [[nodiscard]] const std::string &getName() const;

    void useObject();

    [[nodiscard]] bool hasBeenUsed() const;

    Object(const Object &other);

    Object &operator=(const Object &other);

    void displayDetails() const override;

    void displayState() const;

private:
    std::string name;
    bool used;
};

#endif // OBJECT_H
