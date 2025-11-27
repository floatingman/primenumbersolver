#ifndef PARALLEL_BIT_SIEVE_HPP
#define PARALLEL_BIT_SIEVE_HPP

#include "BitSieve.hpp"
#include "ParallelSieveBase.hpp"
#include <omp.h>
#include <atomic>

/**
 * @class ParallelBitSieve
 * @brief Parallel implementation of BitSieve using OpenMP work-sharing approach.
 * 
 * This class extends BitSieve with OpenMP parallelization for improved performance
 * on multi-core systems. Uses work-sharing approach where the bit array is divided
 * among threads for better cache locality and memory access patterns.
 */
class ParallelBitSieve : public BitSieve, public ParallelSieveBase {
private:
    /**
     * @brief Clear a bit at the specified index with thread safety.
     * @param index The index of the bit to clear.
     */
    void clearBitParallel(std::size_t index);
    
    /**
     * @brief Mark multiples of a prime number in parallel.
     * @param prime The prime number whose multiples to mark.
     */
    void markMultiplesParallel(std::size_t prime);
    
    /**
     * @brief Mark multiples of a prime number in parallel with chunking.
     * @param prime The prime number whose multiples to mark.
     * @param chunkSize Size of chunks for work distribution.
     */
    void markMultiplesParallelChunked(std::size_t prime, std::size_t chunkSize);

public:
    /**
     * @brief Construct ParallelBitSieve with specified limit and thread configuration.
     * @param n The upper limit for finding prime numbers.
     * @param threads Number of threads to use (0 for auto-detection).
     */
    explicit ParallelBitSieve(std::size_t n, int threads = 0);
    
    /**
     * @brief Generate prime numbers using parallel bit sieve algorithm.
     * 
     * Overrides the base generate() method to implement parallel processing.
     * Uses work-sharing approach with OpenMP parallel for loops.
     * Optimized for cache-friendly memory access patterns.
     */
    void generate() override;
    
    /**
     * @brief Get performance statistics for parallel execution.
     * @return String containing performance information.
     */
    std::string getPerformanceStats() const;
};

#endif // PARALLEL_BIT_SIEVE_HPP