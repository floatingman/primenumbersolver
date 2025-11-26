#ifndef WHEEL_SIEVE_HPP
#define WHEEL_SIEVE_HPP

#include <vector>
#include <cstddef>
#include <cstdint>
#include <string>

/**
 * @class WheelSieve
 * @brief Implementation of the Sieve of Eratosthenes with 2,3,5-wheel factorization.
 * 
 * This class provides an optimized implementation of the Sieve of Eratosthenes algorithm
 * using wheel factorization to skip multiples of 2, 3, and 5, reducing operations by ~73%.
 */
class WheelSieve {
private:
    std::vector<bool> sieve;
    std::size_t limit;
    bool generated;

    // Wheel parameters for 2,3,5-wheel
    static constexpr std::size_t WHEEL_SIZE = 30;  // 2*3*5
    static constexpr std::size_t WHEEL_PRIMES_COUNT = 8;  // Number of primes in wheel
    static constexpr std::size_t WHEEL_SKIP[WHEEL_SIZE] = {
        4, 2, 4, 2, 4, 6, 2, 6, 4, 2, 4, 2, 4, 6, 2, 6, 4, 2, 4, 2, 4, 6, 2, 6, 4, 2, 4, 2, 4, 6
    };
    
    // Primes in the wheel
    static constexpr std::size_t WHEEL_PRIMES[WHEEL_PRIMES_COUNT] = {7, 11, 13, 17, 19, 23, 29, 31};

    /**
     * @brief Convert a number to its wheel index.
     * @param num The number to convert.
     * @return The wheel index.
     */
    std::size_t numToWheelIndex(std::size_t num) const;

    /**
     * @brief Convert a wheel index to a number.
     * @param index The wheel index.
     * @return The corresponding number.
     */
    std::size_t wheelIndexToNum(std::size_t index) const;

    /**
     * @brief Get the next number in the wheel sequence.
     * @param current The current number.
     * @return The next number in the wheel sequence.
     */
    std::size_t getNextWheelNumber(std::size_t current) const;

public:
    /**
     * @brief Construct a WheelSieve with the specified upper limit.
     * @param n The upper limit for finding prime numbers.
     */
    explicit WheelSieve(std::size_t n);

    /**
     * @brief Generate all prime numbers up to the limit using wheel factorization.
     */
    void generate();

    /**
     * @brief Get a vector of all prime numbers found.
     * @return A vector containing all prime numbers up to the limit.
     */
    std::vector<std::size_t> getPrimes();

    /**
     * @brief Check if a specific number is prime.
     * @param num The number to check.
     * @return True if the number is prime, false otherwise.
     */
    bool isPrime(std::size_t num);

    /**
     * @brief Get the count of prime numbers found.
     * @return The count of prime numbers up to the limit.
     */
    std::size_t getPrimeCount();

    /**
     * @brief Get the upper limit for this sieve.
     * @return The upper limit.
     */
    std::size_t getLimit() const { return limit; }

    /**
     * @brief Check if the sieve has been generated.
     * @return True if the sieve has been generated, false otherwise.
     */
    bool isGenerated() const { return generated; }

    /**
     * @brief Get the memory usage in bytes.
     * @return The memory usage in bytes.
     */
    std::size_t getMemoryUsage() const;

    /**
     * @brief Print prime numbers to stdout.
     * @param perLine Number of primes to print per line (default: 10).
     */
    void printPrimes(std::size_t perLine = 10) const;

    /**
     * @brief Save prime numbers to a file.
     * @param filename The name of the file to save to.
     * @return True if successful, false otherwise.
     */
    bool savePrimesToFile(const std::string& filename) const;
};

#endif // WHEEL_SIEVE_HPP