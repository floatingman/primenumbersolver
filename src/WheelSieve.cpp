#include "WheelSieve.hpp"
#include <iostream>
#include <fstream>
#include <cmath>
#include <algorithm>

WheelSieve::WheelSieve(std::size_t n) : limit(n), generated(false) {
    // Initialize sieve vector with all values set to true
    sieve.resize(limit + 1, true);
    
    // 0 and 1 are not prime numbers
    if (limit >= 0) sieve[0] = false;
    if (limit >= 1) sieve[1] = false;
    
    // Mark multiples of 2, 3, and 5 as non-prime
    for (std::size_t i = 2; i <= limit; i += 2) sieve[i] = false;
    for (std::size_t i = 3; i <= limit; i += 3) sieve[i] = false;
    for (std::size_t i = 5; i <= limit; i += 5) sieve[i] = false;
    
    // Mark 2, 3, and 5 as prime (they were marked as non-prime above)
    if (limit >= 2) sieve[2] = true;
    if (limit >= 3) sieve[3] = true;
    if (limit >= 5) sieve[5] = true;
}

std::size_t WheelSieve::numToWheelIndex(std::size_t num) const {
    if (num < 7) return 0;
    
    // Find the position in the wheel
    std::size_t remainder = (num - 7) % WHEEL_SIZE;
    std::size_t quotient = (num - 7) / WHEEL_SIZE;
    
    return quotient * WHEEL_PRIMES_COUNT + remainder;
}

std::size_t WheelSieve::wheelIndexToNum(std::size_t index) const {
    if (index < WHEEL_PRIMES_COUNT) {
        return WHEEL_PRIMES[index];
    }
    
    std::size_t quotient = index / WHEEL_PRIMES_COUNT;
    std::size_t remainder = index % WHEEL_PRIMES_COUNT;
    
    return 7 + quotient * WHEEL_SIZE + (WHEEL_PRIMES[remainder] - 7);
}

std::size_t WheelSieve::getNextWheelNumber(std::size_t current) const {
    if (current < 7) {
        // Handle small numbers
        if (current < 2) return 2;
        if (current == 2) return 3;
        if (current == 3) return 5;
        if (current == 5) return 7;
    }
    
    // Find position in wheel
    std::size_t remainder = (current - 7) % WHEEL_SIZE;
    return current + WHEEL_SKIP[remainder];
}

void WheelSieve::generate() {
    if (generated) return; // Already generated
    
    // Start with the first prime in the wheel (7)
    std::size_t p = 7;
    
    while (p * p <= limit) {
        // If p is prime
        if (sieve[p]) {
            // Mark all multiples of p as non-prime
            // Start from p*p as smaller multiples have already been marked
            std::size_t multiple = p * p;
            
            while (multiple <= limit) {
                sieve[multiple] = false;
                // Get the next multiple using wheel factorization
                multiple = getNextWheelNumber(multiple);
                if (multiple % p != 0) {
                    // Ensure we're actually marking a multiple of p
                    multiple += p;
                }
            }
        }
        
        // Move to the next potential prime using the wheel
        p = getNextWheelNumber(p);
    }
    
    generated = true;
}

std::vector<std::size_t> WheelSieve::getPrimes() {
    if (!generated) {
        generate();
    }
    
    std::vector<std::size_t> primes;
    primes.reserve(limit / 10); // Estimate: approximately 1/10 of numbers are prime
    
    // Always include 2, 3, and 5
    if (limit >= 2) primes.push_back(2);
    if (limit >= 3) primes.push_back(3);
    if (limit >= 5) primes.push_back(5);
    
    // Add primes from the wheel
    for (std::size_t i = 7; i <= limit; i = getNextWheelNumber(i)) {
        if (sieve[i]) {
            primes.push_back(i);
        }
    }
    
    return primes;
}

bool WheelSieve::isPrime(std::size_t num) {
    if (num > limit) {
        throw std::invalid_argument("Number exceeds sieve limit");
    }
    
    if (!generated) {
        generate();
    }
    
    return sieve[num];
}

std::size_t WheelSieve::getPrimeCount() {
    if (!generated) {
        generate();
    }
    
    std::size_t count = 0;
    
    // Count 2, 3, and 5 if within limit
    if (limit >= 2) ++count;
    if (limit >= 3) ++count;
    if (limit >= 5) ++count;
    
    // Count primes from the wheel
    for (std::size_t i = 7; i <= limit; i = getNextWheelNumber(i)) {
        if (sieve[i]) {
            ++count;
        }
    }
    
    return count;
}

std::size_t WheelSieve::getMemoryUsage() const {
    return sieve.size() * sizeof(bool);
}

void WheelSieve::printPrimes(std::size_t perLine) const {
    if (!generated) {
        throw std::runtime_error("Sieve has not been generated yet");
    }
    
    std::size_t count = 0;
    
    // Print 2, 3, and 5 if within limit
    if (limit >= 2) {
        std::cout << 2;
        if (++count % perLine == 0) std::cout << std::endl;
        else std::cout << " ";
    }
    if (limit >= 3) {
        std::cout << 3;
        if (++count % perLine == 0) std::cout << std::endl;
        else std::cout << " ";
    }
    if (limit >= 5) {
        std::cout << 5;
        if (++count % perLine == 0) std::cout << std::endl;
        else std::cout << " ";
    }
    
    // Print primes from the wheel
    for (std::size_t i = 7; i <= limit; i = getNextWheelNumber(i)) {
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

bool WheelSieve::savePrimesToFile(const std::string& filename) const {
    if (!generated) {
        throw std::runtime_error("Sieve has not been generated yet");
    }
    
    std::ofstream outFile(filename);
    if (!outFile) {
        return false;
    }
    
    // Save 2, 3, and 5 if within limit
    if (limit >= 2) outFile << 2 << "\n";
    if (limit >= 3) outFile << 3 << "\n";
    if (limit >= 5) outFile << 5 << "\n";
    
    // Save primes from the wheel
    for (std::size_t i = 7; i <= limit; i = getNextWheelNumber(i)) {
        if (sieve[i]) {
            outFile << i << "\n";
        }
    }
    
    outFile.close();
    return true;
}