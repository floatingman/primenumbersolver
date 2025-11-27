#ifndef PARALLEL_BASIC_SIEVE_HPP
#define PARALLEL_BASIC_SIEVE_HPP

#include "BasicSieve.hpp"
#include "ParallelSieveBase.hpp"
#include <omp.h>

/**
 * @class ParallelBasicSieve
 * @brief Parallel implementation of BasicSieve using OpenMP work-sharing approach.
 * 
 * This class extends BasicSieve with OpenMP parallelization for improved performance
 * on multi-core systems. Uses work-sharing approach where the range is divided
 * among threads for better cache locality.
 */
class ParallelBasicSieve : public BasicSieve, public ParallelSieveBase {
private:
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
     * @brief Construct ParallelBasicSieve with specified limit and thread configuration.
     * @param n The upper limit for finding prime numbers.
     * @param threads Number of threads to use (0 for auto-detection).
     */
    explicit ParallelBasicSieve(std::size_t n, int threads = 0);
    
    /**
     * @brief Generate prime numbers using parallel sieve algorithm.
     * 
     * Overrides the base generate() method to implement parallel processing.
     * Uses work-sharing approach with OpenMP parallel for loops.
     */
    void generate() override;
    
    /**
     * @brief Get performance statistics for the parallel execution.
     * @return String containing performance information.
     */
    std::string getPerformanceStats() const;
};

#endif // PARALLEL_BASIC_SIEVE_HPP