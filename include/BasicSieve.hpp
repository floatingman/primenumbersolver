#ifndef BASIC_SIEVE_HPP
#define BASIC_SIEVE_HPP

#include <vector>
#include <cstddef>
#include <string>

/**
 * @class BasicSieve
 * @brief Implementation of the Sieve of Eratosthenes algorithm for finding prime numbers.
 * 
 * This class provides a basic implementation of the Sieve of Eratosthenes algorithm,
 * which efficiently finds all prime numbers up to a specified limit.
 */
class BasicSieve {
private:
    std::vector<bool> sieve;
    std::size_t limit;
    bool generated;

protected:
    /**
     * @brief Get the sieve array for derived classes.
     * @return Reference to the sieve array.
     */
    std::vector<bool>& getSieve() { return sieve; }
    
    /**
     * @brief Get the sieve array for derived classes (const version).
     * @return Const reference to the sieve array.
     */
    const std::vector<bool>& getSieve() const { return sieve; }
    
    /**
     * @brief Set the generated flag for derived classes.
     * @param val The value to set.
     */
    void setGenerated(bool val) { generated = val; }

public:
    /**
     * @brief Construct a BasicSieve with the specified upper limit.
     * @param n The upper limit for finding prime numbers.
     */
    explicit BasicSieve(std::size_t n);
    
    /**
     * @brief Virtual destructor for proper polymorphic cleanup.
     */
    virtual ~BasicSieve() = default;

    /**
     * @brief Generate all prime numbers up to the limit.
     */
    virtual void generate();

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

#endif // BASIC_SIEVE_HPP