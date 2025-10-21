#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cctype>

bool containsOneVowel(const std::string& text) {
    const std::string VOWELS = "aeiou";
    return std::count_if(text.begin(), text.end(), 
        [&VOWELS](char c) { 
            return VOWELS.find(std::tolower(c)) != std::string::npos; 
        }) == 1;
}

std::string getLongestWordWithSingleVowel(const std::vector<std::string>& dictionary) {
    std::string result;
    for (const auto& entry : dictionary) {
        if (containsOneVowel(entry) && entry.length() > result.length()) {
            result = entry;
        }
    }
    return result;
}

int main() {
    // Read dictionary from file
    std::vector<std::string> dictionary;
    std::ifstream inputFile("words.txt");
    
    if (!inputFile) {
        std::cerr << "Failed to open words.txt" << std::endl;
        return 1;
    }

    std::string entry;
    while (inputFile >> entry) {
        dictionary.push_back(entry);
    }
    inputFile.close();

    // Find and display longest single-vowel word
    auto result = getLongestWordWithSingleVowel(dictionary);
    std::cout << "The longest word with one vowel is " << result << std::endl;

    // Search functionality
    std::cout << "Enter the word to search for: ";
    std::string query;
    std::cin >> query;

    auto found = std::find(dictionary.begin(), dictionary.end(), query);
    std::cout << (found != dictionary.end() 
        ? "Found " 
        : "Could not find ") << query << std::endl;

    return 0;
}