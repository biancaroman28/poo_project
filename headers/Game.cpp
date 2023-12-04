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

    locations.push_back(std::make_unique<Location>("Forest", "A mysterious forest with tall trees."));
    locations.push_back(std::make_unique<Location>("Cave", "A dark and scary cave."));
    locations.push_back(std::make_unique<Location>("Mountain", "The peak of a snow-covered mountain."));
    locations.push_back(std::make_unique<Location>("City", "A ruined and deserted city."));

    charactersInLocations["Forest"] = {*(characters[0]), *(characters[3])};
    charactersInLocations["Cave"] = {*(characters[2])};
    charactersInLocations["Mountain"] = {*(characters[1])};
    charactersInLocations["City"] = {*(characters[0]), *(characters[2])};

    locations[0]->addChallenge("Forest Monster");
    locations[1]->addChallenge("Cave Maze");
}

void Game::writeLocations() {
    std::cout << "Available locations: ";
    for (const auto &location : locations) {
        std::cout << location->getName() << " ";
    }
    std::cout << std::endl;
}

void Game::exploreLocation(const std::string &location) {
    std::cout << "You are in " << location << ". " << getLocationDescription(location) << std::endl;
    writeChallengesInLocation(location);
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
/*
const std::vector<std::unique_ptr<Location>>& Game::getLocations() const {
    return locations;
}

const std::vector<std::unique_ptr<Character>>& Game::getCharacters() const {
    return characters;
}
*/
int Game::lives = 3;
/*
int Game::generateHealth(std::mt19937& rng) {
    std::uniform_int_distribution<int> distribution(0, 100);
    return distribution(rng);
}

int Game::generateEnergy(std::mt19937& rng) {
    std::uniform_int_distribution<int> distribution(0, 100);
    return distribution(rng);
}
*/
void Game::reduceLife() {
    if (lives > 0) {
        lives--;
        std::cout << "The number of lives has decreased. You have " << lives << " lives left.\n";
    } else {
        std::cout << "You ran out of lives!\n";
    }
}

void Game::saveGameState() {
    locationHistory.clear();
    for (const auto &location : locations) {
        locationHistory.emplace_back(new Location(*location));
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
