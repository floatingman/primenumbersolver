#include "ParallelWheelSieve.hpp"
#include <chrono>
#include <sstream>
#include <iomanip>

ParallelWheelSieve::ParallelWheelSieve(std::size_t n, int threads) 
    : WheelSieve(n), ParallelSieveBase(threads) {
}

void ParallelWheelSieve::markMultiplesParallel(std::size_t prime) {
    if (!useParallel || threadCount <= 1) {
        // Fallback to sequential implementation
        std::size_t multiple = prime * prime;
        while (multiple <= limit) {
            sieve[multiple] = false;
            multiple += prime;
        }
        return;
    }
    
    // Parallel implementation using work-sharing
    std::size_t start = prime * prime;
    std::size_t end = limit;
    
    // Calculate optimal chunk size for load balancing
    // Use smaller chunks for wheel operations to improve cache efficiency
    std::size_t chunkSize = std::max((end - start) / (threadCount * 8), 
                                     static_cast<std::size_t>(200));
    
    #pragma omp parallel for schedule(static, chunkSize)
    for (std::size_t i = start; i <= end; i += prime) {
        sieve[i] = false;
    }
}

void ParallelWheelSieve::markMultiplesParallelChunked(std::size_t prime, std::size_t chunkSize) {
    if (!useParallel || threadCount <= 1) {
        // Fallback to sequential implementation
        std::size_t multiple = prime * prime;
        while (multiple <= limit) {
            sieve[multiple] = false;
            multiple += prime;
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

std::size_t ParallelWheelSieve::getNextWheelNumberParallel(std::size_t current) const {
    if (!useParallel || threadCount <= 1) {
        // Fallback to sequential implementation
        return getNextWheelNumber(current);
    }
    
    // For parallel wheel navigation, we need to be careful about
    // maintaining the wheel state across threads
    if (current < 7) {
        // Handle small numbers (same as sequential)
        if (current < 2) return 2;
        if (current == 2) return 3;
        if (current == 3) return 5;
        if (current == 5) return 7;
        return limit + 1; // Signal end
    }
    
    // For numbers >= 7, use the wheel to find the next number
    // that is not divisible by 2, 3, or 5
    std::size_t next = current + 1;
    
    // Use parallel reduction to find the next valid wheel number
    std::size_t found = 0;
    
    #pragma omp parallel reduction(+:found)
    {
        while (next <= limit) {
            if (next % 2 != 0 && next % 3 != 0 && next % 5 != 0) {
                found = 1;
                #pragma omp flush(found)
                break;
            }
            if (found) break;
            next++;
        }
    }
    
    return found ? next : limit + 1;
}

void ParallelWheelSieve::markMultiplesParallelChunked(std::size_t prime, std::size_t chunkSize) {
    if (!useParallel || threadCount <= 1) {
        // Fallback to sequential implementation
        std::size_t multiple = prime * prime;
        while (multiple <= limit) {
            sieve[multiple] = false;
            multiple += prime;
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

void ParallelWheelSieve::generate() {
    if (generated) return; // Already generated
    
    if (!useParallel || threadCount <= 1) {
        // Use sequential implementation for single thread
        WheelSieve::generate();
        return;
    }
    
    // Start with first prime in the wheel (7)
    std::size_t p = 7;
    
    while (p * p <= limit) {
        // If p is prime
        if (sieve[p]) {
            // Mark multiples of p in parallel
            markMultiplesParallel(p);
        }
        
        // Move to the next potential prime using the wheel
        p = getNextWheelNumberParallel(p);
    }
    
    generated = true;
}

std::string ParallelWheelSieve::getPerformanceStats() const {
    if (!generated) {
        return "Sieve not generated yet";
    }
    
    std::ostringstream oss;
    oss << "Parallel WheelSieve Performance:\n";
    oss << "  Limit: " << limit << "\n";
    oss << "  Threads: " << threadCount << "\n";
    oss << "  Parallel: " << (useParallel ? "Yes" : "No") << "\n";
    oss << "  Memory Usage: " << getMemoryUsage() << " bytes\n";
    
    return oss.str();
}