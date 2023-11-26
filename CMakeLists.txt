cmake_minimum_required(VERSION 3.26)
project(tema_poo)

set(CMAKE_CXX_STANDARD 17)

add_executable(tema_poo main.cpp
        Personaj.cpp
        Personaj.h
        Obiect.cpp
        Obiect.h
        Locatie.cpp
        Locatie.h
        Joc.cpp
        Joc.h
        Entitate.h
        MyExceptions.h)
