#include <iostream>
#include <memory>
#include <random>
#include "headers/Game.h"

int main() {
    std::random_device rd;
    std::mt19937 rng(rd()); // Mersenne Twister PRNG
    std::uniform_int_distribution<int> distribution(1, 100); // Random numbers between 1 and 100

    Game game;

    std::cout << "Welcome to our adventure!\n\n";

    std::cout << "Details about objects:" << std::endl;
    for (const auto &object : game.getObjects()) {
        object->displayDetails();
        std::cout << std::endl;
    }

    std::cout << "Details about characters:" << std::endl;
    for (const auto &character : game.getCharacters()) {
        character->displayDetails();
        std::cout << std::endl;
    }

    std::cout << "Details about locations:" << std::endl;
    for (const auto &location : game.getLocations()) {
        location->displayDetails();
        std::cout << std::endl;
    }

    bool ok = true;
    do {
        std::cout << "\nEnter a command ('locations', 'explore', 'exit', 'status', 'return', 'energy', 'health'): ";
        std::string command;
        std::cin >> command;

        if (command == "locations") {
            game.writeLocations();
        } else if (command == "explore") {
            std::cout << "Choose a location to explore: ";
            std::string location;
            std::cin >> location;

            game.exploreLocation(location);
            game.writeChallengesInLocation(location);
            game.writeCharactersInLocation(location);

            std::cout << "Do you want to take an object from this location? ('yes'/'no'): ";
            std::string response;
            std::cin >> response;

            if (response == "yes") {
                std::cout << "Which object do you want to take?: ";
                std::string objectName;
                std::cin >> objectName;

                try {
                    std::shared_ptr<Object> takenObject = game.takeObject(objectName);
                    std::cout << "You took " << objectName << ". Have fun!\n";

                    std::cout << "Was the object '" << objectName << "' used? "
                              << (takenObject->hasBeenUsed() ? "Yes" : "No") << std::endl;
                } catch (const ObjectNotFoundException &ex) {
                    std::cout << "Exception: " << ex.what() << std::endl;
                }
            }
        } else if (command == "status") {
            std::cout << "Object status:\n";
            for (const auto &object : game.getObjects()) {
                object->displayState();
            }
        } else if (command == "return") {
            Game::reduceLife();
            game.saveGameState();
            game.displayHistory();
        } else if (command == "energy") {
            std::cout << "Energy: " << Game::generateEnergy() << std::endl;
        } else if (command == "health") {
            std::cout << "Health: " << Game::generateHealth() << std::endl;
        } else if (command == "exit") {
            std::cout << "You have exited the game.\n";
            ok = false;
        } else {
            std::cout << "Invalid command. Please try again.\n";
        }
    } while (ok);

    return 0;
}
