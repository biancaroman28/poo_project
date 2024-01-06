#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <random>
#include "Object.h"
#include "Character.h"
#include "Location.h"

class Game {
private:
    std::vector<std::unique_ptr<Object>> objects;
    std::vector<std::unique_ptr<Character>> characters;
    std::vector<std::unique_ptr<Location<0, 11>>> locations;
    std::map<std::string, std::vector<Character>> charactersInLocations;
    std::map<std::string, std::vector<std::string>> challengesInLocations;
    static int lives;
    std::vector<std::unique_ptr<Location<0,11>>> locationHistory;
    std::vector<std::unique_ptr<Character>> characterHistory;
    std::vector<std::unique_ptr<Object>> objectHistory;
    std::map<std::string, int> locationIndexes;
public:
    Game();
    [[nodiscard]] const std::vector<std::unique_ptr<Object>>& getObjects() const;
    void interactWithLocations();
    void writeLocations();
    void exploreLocation(const std::string &location);
    const std::string &getLocationDescription(const std::string &location);
    ///[[nodiscard]] const std::vector<std::string>& getLocationChallenges(const std::string& location) const;
    void writeCharactersInLocation(const std::string &location);
    void writeChallengesInLocation(const std::string &location);
    std::unique_ptr<Object> takeObject(const std::string &objectName);
    static void reduceLife();
    void saveGameState();
    void displayHistory();
    [[nodiscard]] const std::vector<std::unique_ptr<Location<0, 11>>>& getLocations() const; // Getter for locations
    int getLocationIndex(const std::string &locationName);
};

#endif // GAME_H
