#include "ParallelBitSieve.hpp"
#include <chrono>
#include <sstream>
#include <iomanip>

ParallelBitSieve::ParallelBitSieve(std::size_t n, int threads) 
    : BitSieve(n), ParallelSieveBase(threads) {
}

void ParallelBitSieve::clearBitParallel(std::size_t index) {
    if (!useParallel || threadCount <= 1) {
        // Fallback to sequential implementation
        clearBit(index);
        return;
    }
    
    // For bit operations, we need to be careful with thread safety
    // Each thread works on different 64-bit words, so we need
    // to ensure no race conditions when clearing bits
    std::size_t arrayIndex = index / 64;
    std::size_t bitPosition = index % 64;
    
    #pragma omp critical
    {
        bits[arrayIndex] &= ~(1ULL << bitPosition);
    }
}

void ParallelBitSieve::markMultiplesParallel(std::size_t prime) {
    if (!useParallel || threadCount <= 1) {
        // Fallback to sequential implementation
        for (std::size_t i = prime * prime; i <= limit; i += prime) {
            clearBit(i);
        }
        return;
    }
    
    // Parallel implementation using work-sharing
    std::size_t start = prime * prime;
    std::size_t end = limit;
    
    // Calculate optimal chunk size for load balancing
    // Use smaller chunks for bit operations to improve cache efficiency
    std::size_t chunkSize = std::max((end - start) / (threadCount * 8), 
                                     static_cast<std::size_t>(500));
    
    #pragma omp parallel for schedule(static, chunkSize)
    for (std::size_t i = start; i <= end; i += prime) {
        clearBit(i);
    }
}

void ParallelBitSieve::markMultiplesParallelChunked(std::size_t prime, std::size_t chunkSize) {
    if (!useParallel || threadCount <= 1) {
        // Fallback to sequential implementation
        for (std::size_t i = prime * prime; i <= limit; i += prime) {
            clearBit(i);
        }
        return;
    }
    
    // Parallel implementation with explicit chunking for better load balancing
    std::size_t start = prime * prime;
    std::size_t end = limit;
    
    #pragma omp parallel for schedule(static, chunkSize)
    for (std::size_t i = start; i <= end; i += prime) {
        clearBit(i);
    }
}

void ParallelBitSieve::generate() {
    if (generated) return; // Already generated
    
    if (!useParallel || threadCount <= 1) {
        // Use sequential implementation for single thread
        BitSieve::generate();
        return;
    }
    
    // Parallel bit sieve of Eratosthenes algorithm
    std::size_t sqrtLimit = static_cast<std::size_t>(std::sqrt(limit));
    
    // Use parallel for loop for finding primes
    #pragma omp parallel for schedule(static)
    for (std::size_t p = 2; p <= sqrtLimit; ++p) {
        // If p is prime (bit is set)
        if (getBit(p)) {
            // Mark multiples of p in parallel
            markMultiplesParallel(p);
        }
    }
    
    generated = true;
}

std::string ParallelBitSieve::getPerformanceStats() const {
    if (!generated) {
        return "Sieve not generated yet";
    }
    
    std::ostringstream oss;
    oss << "Parallel BitSieve Performance:\n";
    oss << "  Limit: " << limit << "\n";
    oss << "  Threads: " << threadCount << "\n";
    oss << "  Parallel: " << (useParallel ? "Yes" : "No") << "\n";
    oss << "  Memory Usage: " << getMemoryUsage() << " bytes\n";
    
    return oss.str();
}