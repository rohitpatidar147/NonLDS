#include <iostream>
#include <stdexcept>
#include "PrimeNumber.h"

using namespace std;

void testConstructors() {
    cout << "=== Testing Constructors ===" << endl;
    
    // Test default constructor
    PrimeNumber p1;
    cout << "Default constructor: " << p1.getPrime() << endl;
    
    // Test parameterized constructor
    PrimeNumber p2(13);
    cout << "Parameterized constructor (13): " << p2.getPrime() << endl;
    
    PrimeNumber p3(2);
    cout << "Parameterized constructor (2): " << p3.getPrime() << endl;
    
    cout << endl;
}

void testPrefixOperators() {
    cout << "=== Testing Prefix Operators ===" << endl;
    
    PrimeNumber p(13);
    cout << "Initial value: " << p.getPrime() << endl;
    
    // Test prefix increment
    ++p;
    cout << "After ++p: " << p.getPrime() << endl;
    
    ++p;
    cout << "After another ++p: " << p.getPrime() << endl;
    
    // Test prefix decrement
    --p;
    cout << "After --p: " << p.getPrime() << endl;
    
    --p;
    cout << "After another --p: " << p.getPrime() << endl;
    
    cout << endl;
}

void testPostfixOperators() {
    cout << "=== Testing Postfix Operators ===" << endl;
    
    PrimeNumber p(11);
    cout << "Initial value: " << p.getPrime() << endl;
    
    // Test postfix increment
    PrimeNumber old = p++;
    cout << "After p++, old value: " << old.getPrime() << ", new value: " << p.getPrime() << endl;
    
    old = p++;
    cout << "After another p++, old value: " << old.getPrime() << ", new value: " << p.getPrime() << endl;
    
    // Test postfix decrement
    old = p--;
    cout << "After p--, old value: " << old.getPrime() << ", new value: " << p.getPrime() << endl;
    
    old = p--;
    cout << "After another p--, old value: " << old.getPrime() << ", new value: " << p.getPrime() << endl;
    
    cout << endl;
}

void testSequenceOfPrimes() {
    cout << "=== Testing Sequence of Primes ===" << endl;
    
    PrimeNumber p(2);
    cout << "Starting from 2, next 10 primes:" << endl;
    
    for (int i = 0; i < 10; i++) {
        cout << p.getPrime() << " ";
        ++p;
    }
    cout << endl;
    
    cout << "Going backwards from " << p.getPrime() << ":" << endl;
    for (int i = 0; i < 5; i++) {
        --p;
        cout << p.getPrime() << " ";
    }
    cout << endl << endl;
}

void testEdgeCases() {
    cout << "=== Testing Edge Cases ===" << endl;
    
    // Test with small primes
    PrimeNumber p(2);
    cout << "Starting with 2: " << p.getPrime() << endl;
    ++p;
    cout << "Next prime after 2: " << p.getPrime() << endl;
    
    // Test decrementing from 3
    PrimeNumber p2(3);
    cout << "Starting with 3: " << p2.getPrime() << endl;
    --p2;
    cout << "Previous prime before 3: " << p2.getPrime() << endl;
    
    // Test error handling for decrementing from 2
    PrimeNumber p3(2);
    cout << "Attempting to decrement from 2..." << endl;
    try {
        --p3;
        cout << "Result: " << p3.getPrime() << endl;
    } catch (const exception& e) {
        cout << "Exception caught: " << e.what() << endl;
    }
    
    cout << endl;
}

void testSpecificExample() {
    cout << "=== Testing Specific Example from Requirements ===" << endl;
    
    PrimeNumber p(13);
    cout << "Starting with 13: " << p.getPrime() << endl;
    
    ++p;
    cout << "After ++: " << p.getPrime() << " (should be 17)" << endl;
    
    --p;
    cout << "After --: " << p.getPrime() << " (should be back to 13)" << endl;
    
    --p;
    cout << "After another --: " << p.getPrime() << " (should be 11)" << endl;
    
    cout << endl;
}

int main() {
    cout << "PrimeNumber Class Test Program" << endl;
    cout << "==============================" << endl << endl;
    
    try {
        testConstructors();
        testPrefixOperators();
        testPostfixOperators();
        testSequenceOfPrimes();
        testEdgeCases();
        testSpecificExample();
        
        cout << "All tests completed successfully!" << endl;
        
    } catch (const exception& e) {
        cout << "Error during testing: " << e.what() << endl;
        return 1;
    }
    
    return 0;
}
