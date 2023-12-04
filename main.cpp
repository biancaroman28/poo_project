#include <iostream>
#include <memory>
#include <random>
#include "headers/Game.h"

// Hash function implementation (replace with your hash function)
constexpr unsigned int hash(const char* str) {
    unsigned int hash = 0;
    while (*str) {
        hash += static_cast<unsigned int>(*str);
        ++str;
    }
    return hash;
}

int main() {
    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_int_distribution<int> distribution(1, 100);

    Game game;

    std::cout << "Welcome to our adventure!\n\n";

    bool ok = true;
    const int maxAttempts = 3; // Limit attempts for invalid input
    int attempts = 0;

    do {
        std::cout << "\nEnter a command ('locations', 'explore', 'exit', 'status', 'return', 'energy', 'health'): ";
        std::string command;
        std::cin >> command;

        switch(hash(command.c_str())) {
            case hash("locations"): {
                game.writeLocations();
                break;
            }
            case hash("explore"): {
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
                break;
            }
            case hash("status"): {
                std::cout << "Object status:\n";
                for (const auto &object : game.getObjects()) {
                    object->displayState();
                }
                break;
            }
            case hash("return"): {
                Game::reduceLife();
                game.saveGameState();
                game.displayHistory();
                break;
            }
            case hash("energy"): {
                std::cout << "Energy: " << distribution(rng) << std::endl;
                break;
            }
            case hash("health"): {
                std::cout << "Health: " << distribution(rng) << std::endl;
                break;
            }

            case hash("exit"): {
                std::cout << "You have exited the game.\n";
                ok = false;
                break;
            }
            default: {
                std::cout << "Invalid command. Please try again.\n";
                ++attempts;
                if (attempts >= maxAttempts) {
                    std::cout << "Too many invalid attempts. Exiting the game.\n";
                    ok = false;
                }
                break;
            }
        }
    } while (ok);

    return 0;
}
