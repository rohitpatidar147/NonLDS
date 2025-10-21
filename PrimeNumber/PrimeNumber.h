#ifndef PRIMENUMBER_H
#define PRIMENUMBER_H

class PrimeNumber {
private:
    int prime;
    
    // Helper functions
    bool isPrime(int n) const;
    int nextPrime(int n) const;
    int previousPrime(int n) const;

public:
    // Constructors
    PrimeNumber();                    // Default constructor (sets to 1)
    PrimeNumber(int p);              // Constructor with parameter
    
    // Getter
    int getPrime() const;
    
    // Prefix operators
    PrimeNumber& operator++();       // Prefix ++
    PrimeNumber& operator--();       // Prefix --
    
    // Postfix operators
    PrimeNumber operator++(int);     // Postfix ++
    PrimeNumber operator--(int);     // Postfix --
};

#endif
