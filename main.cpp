#include <memory>
#include <random>
#include "headers/Game.h"

enum Command {
    LOCATIONS,
    EXPLORE,
    STATUS,
    RETURN,
    ENERGY,
    HEALTH,
    EXIT,
    INVALID
};

Command getCommand(const std::string& command) {
    if (command == "locations") return LOCATIONS;
    if (command == "explore") return EXPLORE;
    if (command == "status") return STATUS;
    if (command == "return") return RETURN;
    if (command == "energy") return ENERGY;
    if (command == "health") return HEALTH;
    if (command == "exit") return EXIT;
    return INVALID;
}

int main() {
    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_int_distribution<int> distribution(1, 100);

    Game game;

    std::cout << "Welcome to our adventure!\n\n";

    bool ok = true;
    const int maxAttempts = 3;
    int attempts = 0;
    game.interactWithLocations();
    do {
        std::cout << "\nEnter a command ('locations', 'explore', 'exit', 'status', 'return', 'energy', 'health'): ";
        std::string input;
        std::cin >> input;
        Command command = getCommand(input);
        switch(command) {
            case LOCATIONS: {
                game.writeLocations();
                break;
            }
            case EXPLORE: {
                std::cout << "Choose a location to explore: ";
                std::string location;
                std::cin >> location;
               /// game.exploreLocation(location);
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
            case STATUS: {
                std::cout << "Object status:\n";
                for (const auto &object : game.getObjects()) {
                    object->displayState();
                }
                break;
            }
            case RETURN: {
                Game::reduceLife();
                ///game.saveGameState();
                ///game.displayHistory();
                break;
            }
            case ENERGY: {
                std::cout << "Energy: " << distribution(rng) << std::endl;
                break;
            }
            case HEALTH: {
                std::cout << "Health: " << distribution(rng) << std::endl;
                break;
            }
///
            case EXIT: {
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
    game.saveGameState();
    game.displayHistory();
    return 0;
}