#ifndef MYEXCEPTIONS_H
#define MYEXCEPTIONS_H

#include <exception>
#include <string>

class MyException : public std::exception {
public:
    [[nodiscard]] const char* what() const noexcept override {
        return "Exceptie generica in joc.";
    }
};
/*
class ObiectFolositException : public MyException {
public:
    [[nodiscard]] const char* what() const noexcept override {
        return "Obiectul a fost deja folosit.";
    }
};
*/
class ObiectNegasitException : public MyException {
public:
    [[nodiscard]] const char* what() const noexcept override {
        return "Obiectul nu a putut fi gasit.";
    }
};

#endif // MYEXCEPTIONS_H
