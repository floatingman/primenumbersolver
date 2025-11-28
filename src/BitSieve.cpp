#include "BitSieve.hpp"
#include <iostream>
#include <fstream>
#include <cmath>
#include <algorithm>

BitSieve::BitSieve(std::size_t n) : limit(n), generated(false) {
    // Calculate the number of uint64_t values needed
    bitCount = limit + 1;
    std::size_t arraySize = (bitCount + 63) / 64;  // Each uint64_t holds 64 bits
    
    // Initialize bit vector with all bits set to 1 (true)
    bits.resize(arraySize, ~0ULL);
    
    // Mark 0 and 1 as non-prime (set their bits to 0)
    if (limit >= 0) clearBit(0);
    if (limit >= 1) clearBit(1);
}

void BitSieve::generate() {
    if (generated) return; // Already generated
    
    // Sieve of Eratosthenes algorithm using bit manipulation
    for (std::size_t p = 2; p * p <= limit; ++p) {
        // If p is prime (bit is set)
        if (getBit(p)) {
            // Mark all multiples of p as non-prime
            // Start from p*p as smaller multiples have already been marked
            for (std::size_t i = p * p; i <= limit; i += p) {
                clearBit(i);
            }
        }
    }
    
    generated = true;
}

std::vector<std::size_t> BitSieve::getPrimes() {
    if (!generated) {
        generate();
    }
    
    std::vector<std::size_t> primes;
    primes.reserve(limit / 10); // Estimate: approximately 1/10 of numbers are prime
    
    for (std::size_t i = 2; i <= limit; ++i) {
        if (getBit(i)) {
            primes.push_back(i);
        }
    }
    
    return primes;
}

bool BitSieve::isPrime(std::size_t num) {
    if (num > limit) {
        throw std::invalid_argument("Number exceeds sieve limit");
    }
    
    if (!generated) {
        generate();
    }
    
    return getBit(num);
}

std::size_t BitSieve::getPrimeCount() {
    if (!generated) {
        generate();
    }
    
    std::size_t count = 0;
    for (std::size_t i = 2; i <= limit; ++i) {
        if (getBit(i)) {
            ++count;
        }
    }
    
    return count;
}

std::size_t BitSieve::getMemoryUsage() const {
    return bits.size() * sizeof(uint64_t);
}

void BitSieve::printPrimes(std::size_t perLine) const {
    if (!generated) {
        throw std::runtime_error("Sieve has not been generated yet");
    }
    
    std::size_t count = 0;
    for (std::size_t i = 2; i <= limit; ++i) {
        if (getBit(i)) {
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

bool BitSieve::savePrimesToFile(const std::string& filename) const {
    if (!generated) {
        throw std::runtime_error("Sieve has not been generated yet");
    }
    
    std::ofstream outFile(filename);
    if (!outFile) {
        return false;
    }
    
    for (std::size_t i = 2; i <= limit; ++i) {
        if (getBit(i)) {
            outFile << i << "\n";
        }
    }
    
    outFile.close();
    return true;
}