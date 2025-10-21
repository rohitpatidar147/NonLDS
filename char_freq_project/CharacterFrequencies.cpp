#include "CharacterFrequencies.h"

// Empty constructor implementation
CharacterFrequencies::CharacterFrequencies()
{
    charCountList.clear();
}

// Constructor that processes initial text input
CharacterFrequencies::CharacterFrequencies(string text)
{
    charCountList.clear();
    readString(text);
}

// Searches for character position in data structure, returns -1 if absent
int CharacterFrequencies::getCharacterIndex(char character)
{
    for (size_t position = 0; position < charCountList.size(); ++position)
    {
        if (charCountList[position].first == character)
            return static_cast<int>(position);
    }
    return -1;
}

// Processes input text and accumulates character occurrence counts
void CharacterFrequencies::readString(string text)
{
    for (char currentChar : text)
    {
        int foundPosition = getCharacterIndex(currentChar);
        if (foundPosition == -1)
        {
            charCountList.push_back(make_pair(currentChar, 1));
        }
        else
        {
            charCountList[foundPosition].second += 1;
        }
    }
}

// Zeroes out all character occurrence counts
void CharacterFrequencies::reset()
{
    for (auto &entry : charCountList)
        entry.second = 0;
}

// Retrieves occurrence count for specified character
int CharacterFrequencies::getFrequency(char character)
{
    int foundPosition = getCharacterIndex(character);
    if (foundPosition == -1)
        return 0;
    return charCountList[foundPosition].second;
}

// Outputs all characters with positive occurrence counts
void CharacterFrequencies::printFrequencies()
{
    for (auto &entry : charCountList)
    {
        if (entry.second > 0)
        {
            cout << entry.first << ": " << entry.second << endl;
        }
    }
}
