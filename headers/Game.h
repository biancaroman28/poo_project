#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include "Object.h"
#include "Character.h"
#include "Location.h"

class Game {
private:
    std::vector<std::unique_ptr<Object>> objects;
    std::vector<std::unique_ptr<Character>> characters;
    std::vector<std::unique_ptr<Location>> locations;
    std::map<std::string, std::vector<Character>> charactersInLocations;
    std::map<std::string, std::vector<std::string>> challengesInLocations;
    static int lives;
    std::vector<std::unique_ptr<Location>> locationHistory;
    std::vector<std::unique_ptr<Character>> characterHistory;
    std::vector<std::unique_ptr<Object>> objectHistory;
    // static std::unique_ptr<Character> convertToCharacter(std::unique_ptr<Entity>& entity);

public:
    Game();
    [[nodiscard]] const std::vector<std::unique_ptr<Object>>& getObjects() const;
    [[nodiscard]] const std::vector<std::unique_ptr<Character>>& getCharacters() const;
    [[nodiscard]] const std::vector<std::unique_ptr<Location>>& getLocations() const;
    void writeLocations();
    void exploreLocation(const std::string &location);
    const std::string &getLocationDescription(const std::string &location);
    void writeCharactersInLocation(const std::string &location);
    void writeChallengesInLocation(const std::string &location);
    std::unique_ptr<Object> takeObject(const std::string &objectName);
    static int generateHealth();
    static int generateEnergy();
    static void reduceLife();
    void saveGameState();
    void displayHistory();
};

#endif // GAME_H
