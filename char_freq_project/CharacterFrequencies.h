#ifndef CHARACTERFREQUENCIES_H
#define CHARACTERFREQUENCIES_H

#include <iostream>
#include <string>
#include <utility>
#include <vector>
using namespace std;

class CharacterFrequencies
{
public:
    // Creates an empty object without any character data
    CharacterFrequencies();
    // Creates an object and processes the provided text string
    CharacterFrequencies(string text);
    // Processes text and accumulates character counts with existing data
    void readString(string text);
    // Clears all character counts back to zero
    void reset();
    // Returns count of occurrences for a specific character
    int getFrequency(char character);
    // Utility method to locate position of character in storage array
    int getCharacterIndex(char character);
    // Displays all characters that have positive counts in format:
    // r: 4
    // o: 8
    // w: 2
    // n: 2
    // Characters with zero counts are not displayed!
    void printFrequencies();

private:
    // Storage for character-count data pairs
    vector<pair<char, int>> charCountList;
};

#endif // !CHARACTERFREQUENCIES_H
