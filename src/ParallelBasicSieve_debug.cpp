#include "ParallelBasicSieve.hpp"
#include <chrono>
#include <sstream>
#include <iomanip>
#include <iostream>  // Added for debug logging

// Debug logging macro
#define DEBUG_LOG(msg) std::cout << "[DEBUG] " << msg << std::endl

ParallelBasicSieve::ParallelBasicSieve(std::size_t n, int threads) 
    : BasicSieve(n), ParallelSieveBase(threads) {
    DEBUG_LOG("ParallelBasicSieve constructor called with n=" << n << ", threads=" << threads);
}

void ParallelBasicSieve::markMultiplesParallel(std::size_t prime) {
    DEBUG_LOG("markMultiplesParallel called with prime=" << prime);
    
    if (!useParallel || threadCount <= 1) {
        DEBUG_LOG("Using sequential fallback");
        // Fallback to sequential implementation
        // This will fail due to private access - LOGGING TO VALIDATE
        DEBUG_LOG("Attempting to access private member 'limit'");
        // for (std::size_t i = prime * prime; i <= limit; i += prime) {
        //     sieve[i] = false;
        // }
        return;
    }
    
    DEBUG_LOG("Using parallel implementation");
    // Parallel implementation using work-sharing
    // This will also fail due to private access
    DEBUG_LOG("Attempting to access private members 'limit' and 'sieve'");
    // std::size_t start = prime * prime;
    // std::size_t end = limit;
    
    // Calculate optimal chunk size for load balancing
    // std::size_t chunkSize = std::max((end - start) / (threadCount * 4), 
    //                                  static_cast<std::size_t>(1000));
    
    // #pragma omp parallel for schedule(static, chunkSize)
    // for (std::size_t i = start; i <= end; i += prime) {
    //     sieve[i] = false;
    // }
}

void ParallelBasicSieve::markMultiplesParallelChunked(std::size_t prime, std::size_t chunkSize) {
    DEBUG_LOG("markMultiplesParallelChunked called with prime=" << prime << ", chunkSize=" << chunkSize);
    
    if (!useParallel || threadCount <= 1) {
        DEBUG_LOG("Using sequential fallback");
        // Fallback to sequential implementation
        // This will fail due to private access - LOGGING TO VALIDATE
        DEBUG_LOG("Attempting to access private member 'limit'");
        // for (std::size_t i = prime * prime; i <= limit; i += prime) {
        //     sieve[i] = false;
        // }
        return;
    }
    
    DEBUG_LOG("Using parallel implementation with chunking");
    // This will also fail due to private access
    DEBUG_LOG("Attempting to access private members 'limit' and 'sieve'");
    // std::size_t start = prime * prime;
    // std::size_t end = limit;
    
    // #pragma omp parallel for schedule(static, chunkSize)
    // for (std::size_t i = start; i <= end; i += prime) {
    //     sieve[i] = false;
    // }
}

void ParallelBasicSieve::generate() {
    DEBUG_LOG("ParallelBasicSieve::generate() called");
    
    // This will fail due to private access - LOGGING TO VALIDATE
    DEBUG_LOG("Attempting to access private member 'generated'");
    // if (generated) return; // Already generated
    
    if (!useParallel || threadCount <= 1) {
        DEBUG_LOG("Using sequential BasicSieve::generate()");
        // Use sequential implementation for single thread
        BasicSieve::generate();
        return;
    }
    
    DEBUG_LOG("Using parallel sieve implementation");
    // This will fail due to private access and missing cmath - LOGGING TO VALIDATE
    DEBUG_LOG("Attempting to access private member 'limit' and use std::sqrt");
    // std::size_t sqrtLimit = static_cast<std::size_t>(std::sqrt(limit));
    
    // Use parallel for loop for finding primes
    // This will fail due to private access - LOGGING TO VALIDATE
    DEBUG_LOG("Attempting to access private member 'sieve'");
    // #pragma omp parallel for schedule(static)
    // for (std::size_t p = 2; p <= sqrtLimit; ++p) {
    //     // If sieve[p] is true, then p is a prime
    //     if (sieve[p]) {
    //         // Mark multiples of p in parallel
    //         markMultiplesParallel(p);
    //     }
    // }
    
    DEBUG_LOG("Attempting to access private member 'generated'");
    // generated = true;
}

std::string ParallelBasicSieve::getPerformanceStats() const {
    DEBUG_LOG("getPerformanceStats() called");
    
    // This will fail due to private access - LOGGING TO VALIDATE
    DEBUG_LOG("Attempting to access private members 'generated', 'limit', 'sieve'");
    // if (!generated) {
    //     return "Sieve not generated yet";
    // }
    
    std::ostringstream oss;
    oss << "Parallel BasicSieve Performance:\n";
    // oss << "  Limit: " << limit << "\n";
    oss << "  Threads: " << threadCount << "\n";
    oss << "  Parallel: " << (useParallel ? "Yes" : "No") << "\n";
    // oss << "  Memory Usage: " << (sieve.size() * sizeof(bool)) << " bytes\n";
    
    return oss.str();
}