#include "PrimeNumber.h"
#include <stdexcept>

// Default constructor - sets prime to 1 (note: 1 is not technically prime, but per requirements)
PrimeNumber::PrimeNumber() : prime(1) {}

// Constructor with parameter
PrimeNumber::PrimeNumber(int p) {
    if (p < 1) {
        throw std::invalid_argument("Prime number must be positive");
    }
    prime = p;
}

// Getter function
int PrimeNumber::getPrime() const {
    return prime;
}

// Helper function to check if a number is prime
bool PrimeNumber::isPrime(int n) const {
    if (n < 2) return false;
    if (n == 2) return true;
    if (n % 2 == 0) return false;
    
    for (int i = 3; i * i <= n; i += 2) {
        if (n % i == 0) return false;
    }
    return true;
}

// Helper function to find the next prime number
int PrimeNumber::nextPrime(int n) const {
    int candidate = n + 1;
    while (!isPrime(candidate)) {
        candidate++;
    }
    return candidate;
}

// Helper function to find the previous prime number
int PrimeNumber::previousPrime(int n) const {
    if (n <= 2) {
        throw std::runtime_error("No prime number smaller than 2");
    }
    
    int candidate = n - 1;
    while (candidate >= 2 && !isPrime(candidate)) {
        candidate--;
    }
    
    if (candidate < 2) {
        throw std::runtime_error("No prime number found");
    }
    
    return candidate;
}

// Prefix increment operator
PrimeNumber& PrimeNumber::operator++() {
    prime = nextPrime(prime);
    return *this;
}

// Prefix decrement operator
PrimeNumber& PrimeNumber::operator--() {
    prime = previousPrime(prime);
    return *this;
}

// Postfix increment operator
PrimeNumber PrimeNumber::operator++(int) {
    PrimeNumber temp(*this);  // Save current state
    prime = nextPrime(prime); // Increment current object
    return temp;              // Return old state
}

// Postfix decrement operator
PrimeNumber PrimeNumber::operator--(int) {
    PrimeNumber temp(*this);  // Save current state
    prime = previousPrime(prime); // Decrement current object
    return temp;              // Return old state
}
