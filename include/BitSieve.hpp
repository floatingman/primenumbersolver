#ifndef BIT_SIEVE_HPP
#define BIT_SIEVE_HPP

#include <vector>
#include <cstddef>
#include <cstdint>
#include <string>

/**
 * @class BitSieve
 * @brief Optimized implementation of the Sieve of Eratosthenes using bit manipulation.
 * 
 * This class provides an optimized implementation of the Sieve of Eratosthenes algorithm
 * using bit manipulation to reduce memory usage by a factor of 8 compared to the basic
 * boolean array implementation.
 */
class BitSieve {
private:
    std::vector<uint64_t> bits;
    std::size_t limit;
    std::size_t bitCount;
    bool generated;

protected:
    /**
     * @brief Get the bits array for derived classes.
     * @return Reference to the bits array.
     */
    std::vector<uint64_t>& getBits() { return bits; }
    
    /**
     * @brief Get the bits array for derived classes (const version).
     * @return Const reference to the bits array.
     */
    const std::vector<uint64_t>& getBits() const { return bits; }
    
    /**
     * @brief Get the limit for derived classes.
     * @return The upper limit.
     */
    std::size_t getLimit() const { return limit; }
    
    /**
     * @brief Get the bit count for derived classes.
     * @return The bit count.
     */
    std::size_t getBitCount() const { return bitCount; }
    
    /**
     * @brief Check if the sieve has been generated for derived classes.
     * @return True if generated, false otherwise.
     */
    bool isGenerated() const { return generated; }
    
    /**
     * @brief Set the generated flag for derived classes.
     * @param val The value to set.
     */
    void setGenerated(bool val) { generated = val; }
    
    /**
     * @brief Get the value of a bit at the specified index.
     * @param index The index of the bit to get.
     * @return True if the bit is set (1), false if it's clear (0).
     */
    inline bool getBit(std::size_t index) const;

    /**
     * @brief Set a bit at the specified index to 1 (non-prime).
     * @param index The index of the bit to set.
     */
    inline void setBit(std::size_t index);

    /**
     * @brief Clear a bit at the specified index to 0 (prime).
     * @param index The index of the bit to clear.
     */
    inline void clearBit(std::size_t index);

public:
    /**
     * @brief Construct a BitSieve with the specified upper limit.
     * @param n The upper limit for finding prime numbers.
     */
    explicit BitSieve(std::size_t n);
    
    /**
     * @brief Virtual destructor for proper polymorphic cleanup.
     */
    virtual ~BitSieve() = default;

    /**
     * @brief Generate all prime numbers up to the limit using bit manipulation.
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

#endif // BIT_SIEVE_HPP