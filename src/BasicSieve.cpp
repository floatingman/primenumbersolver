#include "BasicSieve.hpp"
#include <iostream>
#include <fstream>
#include <cmath>
#include <algorithm>

BasicSieve::BasicSieve(std::size_t n) : limit(n), generated(false) {
    // Initialize sieve vector with all values set to true
    sieve.resize(limit + 1, true);
    
    // 0 and 1 are not prime numbers
    if (limit >= 0) sieve[0] = false;
    if (limit >= 1) sieve[1] = false;
}

void BasicSieve::generate() {
    if (generated) return; // Already generated
    
    // Sieve of Eratosthenes algorithm
    for (std::size_t p = 2; p * p <= limit; ++p) {
        // If sieve[p] is true, then p is a prime
        if (sieve[p]) {
            // Mark all multiples of p as non-prime
            // Start from p*p as smaller multiples have already been marked
            for (std::size_t i = p * p; i <= limit; i += p) {
                sieve[i] = false;
            }
        }
    }
    
    generated = true;
}

std::vector<std::size_t> BasicSieve::getPrimes() {
    if (!generated) {
        generate();
    }
    
    std::vector<std::size_t> primes;
    primes.reserve(limit / 10); // Estimate: approximately 1/10 of numbers are prime
    
    for (std::size_t i = 2; i <= limit; ++i) {
        if (sieve[i]) {
            primes.push_back(i);
        }
    }
    
    return primes;
}

bool BasicSieve::isPrime(std::size_t num) {
    if (num > limit) {
        throw std::invalid_argument("Number exceeds sieve limit");
    }
    
    if (!generated) {
        generate();
    }
    
    return sieve[num];
}

std::size_t BasicSieve::getPrimeCount() {
    if (!generated) {
        generate();
    }
    
    std::size_t count = 0;
    for (std::size_t i = 2; i <= limit; ++i) {
        if (sieve[i]) {
            ++count;
        }
    }
    
    return count;
}

void BasicSieve::printPrimes(std::size_t perLine) const {
    if (!generated) {
        throw std::runtime_error("Sieve has not been generated yet");
    }
    
    std::size_t count = 0;
    for (std::size_t i = 2; i <= limit; ++i) {
        if (sieve[i]) {
            std::cout << i;
            if (++count % perLine == 0) {
                std::cout << std::endl;
            } else {
                std::cout << " ";
            }
        }
    }
    
    // Add newline if the last line wasn't complete
    if (count % perLine != 0) {
        std::cout << std::endl;
    }
}

bool BasicSieve::savePrimesToFile(const std::string& filename) const {
    if (!generated) {
        throw std::runtime_error("Sieve has not been generated yet");
    }
    
    std::ofstream outFile(filename);
    if (!outFile) {
        return false;
    }
    
    for (std::size_t i = 2; i <= limit; ++i) {
        if (sieve[i]) {
            outFile << i << "\n";
        }
    }
    
    outFile.close();
    return true;
}