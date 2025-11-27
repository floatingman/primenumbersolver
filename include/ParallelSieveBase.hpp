#ifndef PARALLEL_SIEVE_BASE_HPP
#define PARALLEL_SIEVE_BASE_HPP

#include <omp.h>
#include <thread>
#include <algorithm>

/**
 * @class ParallelSieveBase
 * @brief Base class for parallel sieve implementations with common OpenMP functionality.
 * 
 * This class provides common functionality for parallel sieve implementations,
 * including thread management, configuration, and performance monitoring.
 */
class ParallelSieveBase {
protected:
    int threadCount;
    bool useParallel;
    
    /**
     * @brief Get optimal thread count based on hardware.
     * @return Optimal number of threads for current system.
     */
    int getOptimalThreadCount() const {
        int maxThreads = omp_get_max_threads();
        int logicalCores = std::thread::hardware_concurrency();
        return std::min(maxThreads, logicalCores);
    }

public:
    /**
     * @brief Construct parallel sieve base with specified thread configuration.
     * @param threads Number of threads to use (0 for auto-detection).
     */
    explicit ParallelSieveBase(int threads = 0) 
        : threadCount(threads > 0 ? threads : getOptimalThreadCount()),
          useParallel(threads != 1) {}
    
    /**
     * @brief Get the configured thread count.
     * @return Number of threads configured for parallel execution.
     */
    int getThreadCount() const { return threadCount; }
    
    /**
     * @brief Check if parallel processing is enabled.
     * @return True if parallel processing is enabled, false otherwise.
     */
    bool isParallelEnabled() const { return useParallel; }
    
    /**
     * @brief Set thread count for parallel execution.
     * @param threads Number of threads to use.
     */
    void setThreadCount(int threads) {
        threadCount = threads > 0 ? threads : getOptimalThreadCount();
        useParallel = (threads != 1);
    }
    
    /**
     * @brief Enable or disable parallel processing.
     * @param parallel True to enable parallel processing, false to disable.
     */
    void setParallelEnabled(bool parallel) {
        useParallel = parallel;
    }
    
    /**
     * @brief Get thread information for display.
     * @return String containing thread information.
     */
    std::string getThreadInfo() const {
        return "Threads: " + std::to_string(threadCount) + 
               " (Parallel: " + (useParallel ? "Yes" : "No") + ")";
    }
};

#endif // PARALLEL_SIEVE_BASE_HPP