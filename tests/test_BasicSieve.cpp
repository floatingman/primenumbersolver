#include <gtest/gtest.h>
#include "../include/BasicSieve.hpp"
#include <vector>
#include <algorithm>
#include <fstream>

class BasicSieveTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Setup code
    }

    void TearDown() override {
        // Cleanup code
    }
};

// Test that the sieve correctly identifies small primes
TEST_F(BasicSieveTest, IdentifiesSmallPrimes) {
    BasicSieve sieve(30);
    sieve.generate();
    
    // Known primes up to 30
    std::vector<std::size_t> expectedPrimes = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};
    std::vector<std::size_t> actualPrimes = sieve.getPrimes();
    
    ASSERT_EQ(actualPrimes, expectedPrimes);
}

// Test that isPrime correctly identifies prime numbers
TEST_F(BasicSieveTest, IsPrimeCorrectness) {
    BasicSieve sieve(100);
    sieve.generate();
    
    // Test known primes
    ASSERT_TRUE(sieve.isPrime(2));
    ASSERT_TRUE(sieve.isPrime(3));
    ASSERT_TRUE(sieve.isPrime(5));
    ASSERT_TRUE(sieve.isPrime(7));
    ASSERT_TRUE(sieve.isPrime(11));
    ASSERT_TRUE(sieve.isPrime(13));
    ASSERT_TRUE(sieve.isPrime(17));
    ASSERT_TRUE(sieve.isPrime(19));
    ASSERT_TRUE(sieve.isPrime(23));
    ASSERT_TRUE(sieve.isPrime(29));
    ASSERT_TRUE(sieve.isPrime(97));
    
    // Test known non-primes
    ASSERT_FALSE(sieve.isPrime(1));
    ASSERT_FALSE(sieve.isPrime(4));
    ASSERT_FALSE(sieve.isPrime(6));
    ASSERT_FALSE(sieve.isPrime(8));
    ASSERT_FALSE(sieve.isPrime(9));
    ASSERT_FALSE(sieve.isPrime(10));
    ASSERT_FALSE(sieve.isPrime(12));
    ASSERT_FALSE(sieve.isPrime(15));
    ASSERT_FALSE(sieve.isPrime(25));
    ASSERT_FALSE(sieve.isPrime(49));
    ASSERT_FALSE(sieve.isPrime(100));
}

// Test that getPrimeCount returns the correct count
TEST_F(BasicSieveTest, PrimeCountCorrectness) {
    BasicSieve sieve(100);
    sieve.generate();
    
    // There are 25 primes less than 100
    ASSERT_EQ(sieve.getPrimeCount(), 25);
}

// Test edge cases
TEST_F(BasicSieveTest, EdgeCases) {
    // Test with limit 0
    BasicSieve sieve0(0);
    sieve0.generate();
    ASSERT_EQ(sieve0.getPrimes().size(), 0);
    ASSERT_EQ(sieve0.getPrimeCount(), 0);
    
    // Test with limit 1
    BasicSieve sieve1(1);
    sieve1.generate();
    ASSERT_EQ(sieve1.getPrimes().size(), 0);
    ASSERT_EQ(sieve1.getPrimeCount(), 0);
    
    // Test with limit 2
    BasicSieve sieve2(2);
    sieve2.generate();
    std::vector<std::size_t> primes2 = sieve2.getPrimes();
    ASSERT_EQ(primes2.size(), 1);
    ASSERT_EQ(primes2[0], 2);
    ASSERT_EQ(sieve2.getPrimeCount(), 1);
}

// Test that sieve generates correctly for larger limits
TEST_F(BasicSieveTest, LargerLimit) {
    BasicSieve sieve(1000);
    sieve.generate();
    
    // There are 168 primes less than 1000
    ASSERT_EQ(sieve.getPrimeCount(), 168);
    
    // Check a few specific primes
    ASSERT_TRUE(sieve.isPrime(997));
    ASSERT_FALSE(sieve.isPrime(999));
}

// Test that sieve throws exception for numbers beyond limit
TEST_F(BasicSieveTest, ExceedsLimit) {
    BasicSieve sieve(100);
    sieve.generate();
    
    ASSERT_THROW(sieve.isPrime(101), std::invalid_argument);
    ASSERT_THROW(sieve.isPrime(200), std::invalid_argument);
}

// Test that sieve doesn't regenerate if already generated
TEST_F(BasicSieveTest, NoRegeneration) {
    BasicSieve sieve(100);
    
    // Generate once
    sieve.generate();
    std::vector<std::size_t> primesFirst = sieve.getPrimes();
    
    // Generate again (should not regenerate)
    sieve.generate();
    std::vector<std::size_t> primesSecond = sieve.getPrimes();
    
    // Results should be identical
    ASSERT_EQ(primesFirst, primesSecond);
}

// Test file saving functionality
TEST_F(BasicSieveTest, FileSaving) {
    BasicSieve sieve(30);
    sieve.generate();
    
    std::string filename = "test_primes.txt";
    bool result = sieve.savePrimesToFile(filename);
    
    ASSERT_TRUE(result);
    
    // Read the file and verify its contents
    std::ifstream file(filename);
    std::vector<std::size_t> filePrimes;
    std::size_t prime;
    
    while (file >> prime) {
        filePrimes.push_back(prime);
    }
    
    file.close();
    
    // Verify the primes match
    std::vector<std::size_t> expectedPrimes = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};
    ASSERT_EQ(filePrimes, expectedPrimes);
    
    // Clean up
    std::remove(filename.c_str());
}

// Test that isGenerated works correctly
TEST_F(BasicSieveTest, IsGenerated) {
    BasicSieve sieve(100);
    
    // Initially not generated
    ASSERT_FALSE(sieve.isGenerated());
    
    // After generating, should be true
    sieve.generate();
    ASSERT_TRUE(sieve.isGenerated());
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}