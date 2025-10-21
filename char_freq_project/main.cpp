// main.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include "CharacterFrequencies.h"
using namespace std;

int main()
{
    string line = "The quick brown fox jumps over the lazy dog. The quick brown fox jumps over the lazy dog.";
    CharacterFrequencies lineCharFreq;
    lineCharFreq.printFrequencies();

    cout << line << endl;
    lineCharFreq.readString(line);
    lineCharFreq.printFrequencies();

    lineCharFreq.reset();
    lineCharFreq.printFrequencies();

    string line2 = "Twinkle twinkle little star, how I wonder what you are.";
    cout << line2 << endl;
    CharacterFrequencies line2CharFreq(line2);
    line2CharFreq.printFrequencies();
    line2CharFreq.readString(line2);
    line2CharFreq.printFrequencies();

    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
