#ifndef PARALLEL_WHEEL_SIEVE_HPP
#define PARALLEL_WHEEL_SIEVE_HPP

#include "WheelSieve.hpp"
#include "ParallelSieveBase.hpp"
#include <omp.h>

/**
 * @class ParallelWheelSieve
 * @brief Parallel implementation of WheelSieve using OpenMP work-sharing approach.
 * 
 * This class extends WheelSieve with OpenMP parallelization for improved performance
 * on multi-core systems. Uses work-sharing approach where the wheel-based
 * range is divided among threads for better cache locality while preserving
 * the 2,3,5-wheel optimization.
 */
class ParallelWheelSieve : public WheelSieve, public ParallelSieveBase {
private:
    /**
     * @brief Mark multiples of a prime number in parallel.
     * @param prime The prime number whose multiples to mark.
     */
    void markMultiplesParallel(std::size_t prime);
    
    /**
     * @brief Get next wheel number in parallel with thread safety.
     * @param current The current number in wheel sequence.
     * @return Next number in wheel sequence.
     */
    std::size_t getNextWheelNumberParallel(std::size_t current) const;
    
    /**
     * @brief Mark multiples of a prime number in parallel with chunking.
     * @param prime The prime number whose multiples to mark.
     * @param chunkSize Size of chunks for work distribution.
     */
    void markMultiplesParallelChunked(std::size_t prime, std::size_t chunkSize);

public:
    /**
     * @brief Construct ParallelWheelSieve with specified limit and thread configuration.
     * @param n The upper limit for finding prime numbers.
     * @param threads Number of threads to use (0 for auto-detection).
     */
    explicit ParallelWheelSieve(std::size_t n, int threads = 0);
    
    /**
     * @brief Generate prime numbers using parallel wheel sieve algorithm.
     * 
     * Overrides the base generate() method to implement parallel processing.
     * Uses work-sharing approach with OpenMP parallel for loops.
     * Maintains 2,3,5-wheel optimization for improved performance.
     */
    void generate() override;
    
    /**
     * @brief Get performance statistics for parallel execution.
     * @return String containing performance information.
     */
    std::string getPerformanceStats() const;
};

#endif // PARALLEL_WHEEL_SIEVE_HPP