#ifndef MYEXCEPTIONS_H
#define MYEXCEPTIONS_H

#include <exception>
#include <string>

class MyException : public std::exception {
public:
    [[nodiscard]] const char *what() const noexcept override {
        return "Generic exception in the game.";
    }
};

/*
class ObjectUsedException : public MyException {
public:
    [[nodiscard]] const char* what() const noexcept override {
        return "The object has already been used.";
    }
};
*/
class ObjectNotFoundException : public MyException {
public:
    [[nodiscard]] const char *what() const noexcept override {
        return "The object could not be found.";
    }
};

#endif // MYEXCEPTIONS_H
