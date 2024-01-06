#include "Game.h"
#include <iostream>
#include "MyExceptions.h"

Game::Game() {
    objects.push_back(std::make_unique<Object>("Flashlight"));
    objects.push_back(std::make_unique<Object>("Key"));
    objects.push_back(std::make_unique<Object>("First Aid Kit"));
    objects.push_back(std::make_unique<Object>("Rope"));
    objects.push_back(std::make_unique<Object>("Weapon"));
    objects.push_back(std::make_unique<Object>("Precious Stones"));

    characters.push_back(std::make_unique<Character>("Wizard"));
    characters.push_back(std::make_unique<Character>("Explorer"));
    characters.push_back(std::make_unique<Character>("Hunter"));
    characters.push_back(std::make_unique<Character>("Animal"));

    locations.push_back(std::make_unique<Location<0,11>>("Forest", "A mysterious forest with tall trees.",0,28));
    locations.push_back(std::make_unique<Location<0,11>>("Cave", "A dark and scary cave.",0,15));
    locations.push_back(std::make_unique<Location<0,11>>("Mountain", "The peak of a snow-covered mountain.",0,24));
    locations.push_back(std::make_unique<Location<0,11>>("City", "A ruined and deserted city.",0,12));

    charactersInLocations["Forest"] = {*(characters[0]), *(characters[3])};
    charactersInLocations["Cave"] = {*(characters[2])};
    charactersInLocations["Mountain"] = {*(characters[1])};
    charactersInLocations["City"] = {*(characters[0]), *(characters[2])};

    locationIndexes["Forest"] = 0;
    locationIndexes["Cave"] = 1;
    locationIndexes["Mountain"] = 2;
    locationIndexes["City"] = 3;
/*
    locations[0]->addChallenge("Forest Monster");
    locations[1]->addChallenge("Cave Maze");
    */
}
void Game::interactWithLocations() {
    // Setează atributele pentru locațiile specifice
   locations[0]->setAttributes(0, 28); // Exemplu index locație și atribute
    locations[1]->setAttributes(0, 22); // Exemplu index locație și atribute
    locations[2]->setAttributes(0, 12);

    // Execută acțiuni în locații
    locations[0]->performAction(); // Exemplu index locație
    locations[1]->performAction(); // Exemplu index locație

    // Marchează anumite locații ca vizitate
    locations[2]->markVisited(); // Exemplu index locație
    locations[3]->markVisited(); // Exemplu index locație

    // Adaugă provocări la anumite locații
    locations[0]->addChallenge("Provocare A"); // Exemplu index locație și provocare
    locations[3]->addChallenge("Provocare B"); // Exemplu index locație și provocare

    // Afișează detalii despre toate locațiile și starea de vizitare a acestora
    for (const auto &location : locations) {
        location->displayDetails();
        std::cout << "Visited: " << (location->isVisited() ? "Da" : "Nu") << std::endl; // Verificare și afișare starea de vizitare
        std::cout << "Danger level: " << location->getDangerLevel() << std::endl;
    }
}


void Game::writeLocations() {
    std::cout << "Available locations: ";
    for (const auto &location : locations) {
        std::cout << location->getName() << " ";
    }
    std::cout << std::endl;
}

const std::string &Game::getLocationDescription(const std::string &location) {
    for (const auto &loc : locations) {
        if (loc->getName() == location) {
            return loc->getDescription();
        }
    }
    static const std::string empty = "Unknown location.";
    return empty;
}

void Game::writeCharactersInLocation(const std::string &location) {
    std::cout << "Characters in " << location << ": ";
    const auto &charactersInLocation = charactersInLocations[location];
    for (const auto &character : charactersInLocation) {
        std::cout << character.getName() << " ";
    }
    std::cout << std::endl;
}

void Game::writeChallengesInLocation(const std::string &location) {
    std::cout << "Challenges in " << location << ": ";
    const auto &challengesInLocation = challengesInLocations[location];
    for (const auto &challenge : challengesInLocation) {
        std::cout << challenge << " ";
    }
    std::cout << std::endl;
}

std::unique_ptr<Object> Game::takeObject(const std::string &objectName) {
    for (auto it = objects.begin(); it != objects.end(); ++it) {
        if (!(*it)->hasBeenUsed() && (*it)->getName() == objectName) {
            auto obj = std::move(*it);
            objects.erase(it);
            obj->useObject();
            return obj;
        }
    }
    throw ObjectNotFoundException();
}

const std::vector<std::unique_ptr<Object>>& Game::getObjects() const {
    return objects;
}
int Game::lives = 3;
void Game::reduceLife() {
    if (lives > 0) {
        lives--;
        std::cout << "The number of lives has decreased. You have " << lives << " lives left.\n";
    } else {
        std::cout << "You ran out of lives!\n";
    }
}
/*
const std::vector<std::string>& Game::getLocationChallenges(const std::string& location) const {
    auto it = challengesInLocations.find(location);
    if (it != challengesInLocations.end()) {
        return it->second;
    }
    static const std::vector<std::string> emptyChallenges;
    return emptyChallenges;
}*/
/*
void Game::saveGameState() {
    locationHistory.clear();
    for (const auto &location : locations) {
        locationHistory.emplace_back(new Location<0,11>(*location));
    }

    characterHistory.clear();
    for (const auto &character : characters) {
        characterHistory.emplace_back(new Character(*character));
    }

    objectHistory.clear();
    for (const auto &object : objects) {
        if (object->hasBeenUsed()) {
            objectHistory.emplace_back(new Object(*object));
        }
    }

    std::cout << "The game state has been saved.\n";
}
*/
void Game::displayHistory() {
    std::cout << "\n--- Game History ---\n";

    std::cout << "Location History:\n";
    for (const auto &location : locationHistory) {
        location->displayDetails();
    }

    std::cout << "\nCharacter History:\n";
    for (const auto &character : characterHistory) {
        character->displayDetails();
    }

    std::cout << "\nUsed Objects History:\n";
    for (const auto &object : objectHistory) {
        object->displayDetails();
    }
}

int Game::getLocationIndex(const std::string &locationName) {
    auto it = locationIndexes.find(locationName);
    if (it != locationIndexes.end()) {
        return it->second;
    } else {
        return -1;
    }
}

