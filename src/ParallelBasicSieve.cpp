#include "ParallelBasicSieve.hpp"
#include <chrono>
#include <sstream>
#include <iomanip>

ParallelBasicSieve::ParallelBasicSieve(std::size_t n, int threads) 
    : BasicSieve(n), ParallelSieveBase(threads) {
}

void ParallelBasicSieve::markMultiplesParallel(std::size_t prime) {
    if (!useParallel || threadCount <= 1) {
        // Fallback to sequential implementation
        for (std::size_t i = prime * prime; i <= limit; i += prime) {
            sieve[i] = false;
        }
        return;
    }
    
    // Parallel implementation using work-sharing
    std::size_t start = prime * prime;
    std::size_t end = limit;
    
    // Calculate optimal chunk size for load balancing
    std::size_t chunkSize = std::max((end - start) / (threadCount * 4), 
                                     static_cast<std::size_t>(1000));
    
    #pragma omp parallel for schedule(static, chunkSize)
    for (std::size_t i = start; i <= end; i += prime) {
        sieve[i] = false;
    }
}

void ParallelBasicSieve::markMultiplesParallelChunked(std::size_t prime, std::size_t chunkSize) {
    if (!useParallel || threadCount <= 1) {
        // Fallback to sequential implementation
        for (std::size_t i = prime * prime; i <= limit; i += prime) {
            sieve[i] = false;
        }
        return;
    }
    
    // Parallel implementation with explicit chunking for better load balancing
    std::size_t start = prime * prime;
    std::size_t end = limit;
    
    #pragma omp parallel for schedule(static, chunkSize)
    for (std::size_t i = start; i <= end; i += prime) {
        sieve[i] = false;
    }
}

void ParallelBasicSieve::generate() {
    if (generated) return; // Already generated
    
    if (!useParallel || threadCount <= 1) {
        // Use sequential implementation for single thread
        BasicSieve::generate();
        return;
    }
    
    // Parallel sieve of Eratosthenes algorithm
    std::size_t sqrtLimit = static_cast<std::size_t>(std::sqrt(limit));
    
    // Use parallel for loop for finding primes
    #pragma omp parallel for schedule(static)
    for (std::size_t p = 2; p <= sqrtLimit; ++p) {
        // If sieve[p] is true, then p is a prime
        if (sieve[p]) {
            // Mark multiples of p in parallel
            markMultiplesParallel(p);
        }
    }
    
    generated = true;
}

std::string ParallelBasicSieve::getPerformanceStats() const {
    if (!generated) {
        return "Sieve not generated yet";
    }
    
    std::ostringstream oss;
    oss << "Parallel BasicSieve Performance:\n";
    oss << "  Limit: " << limit << "\n";
    oss << "  Threads: " << threadCount << "\n";
    oss << "  Parallel: " << (useParallel ? "Yes" : "No") << "\n";
    oss << "  Memory Usage: " << (sieve.size() * sizeof(bool)) << " bytes\n";
    
    return oss.str();
}