# Copilot Instructions for Prime Number Solver

This repository contains a high-performance C++ application that finds prime numbers using the Sieve of Eratosthenes algorithm with multiple optimizations.

## Project Overview

- **Language**: C++17
- **Build System**: CMake 3.15+
- **Package Manager**: Conan 2.0+
- **Testing Framework**: Google Test
- **Parallel Processing**: OpenMP

## Build and Test Commands

```bash
# Install dependencies
conan install . --output-folder=build --build=missing

# Build the project
./build.sh
# Or manually:
cmake --preset conan-release
cmake --build --preset conan-release

# Run tests
ctest --preset conan-release

# Run specific test suites
./prime_sieve_basic_tests
./prime_sieve_bit_tests
./prime_sieve_wheel_tests
```

## Code Structure

- `src/` - Source files for sieve implementations
  - `BasicSieve.cpp` - Standard Sieve of Eratosthenes
  - `BitSieve.cpp` - Memory-efficient bit array implementation
  - `WheelSieve.cpp` - 2,3,5-wheel factorization optimization
  - `ParallelBasicSieve.cpp`, `ParallelBitSieve.cpp`, `ParallelWheelSieve.cpp` - OpenMP parallel versions
  - `main.cpp` - CLI application entry point
  - `benchmark_parallel.cpp` - Performance benchmarking
- `include/` - Header files with class definitions
- `tests/` - Google Test unit tests

## Coding Standards

### Naming Conventions

- **Classes**: `PascalCase` (e.g., `BasicSieve`, `BitSieve`, `ParallelWheelSieve`)
- **Functions/methods**: `camelCase` (e.g., `findPrimes`, `isPrime`)
- **Variables**: `camelCase` (e.g., `primeCount`, `upperLimit`)
- **Constants**: `UPPER_CASE` (e.g., `MAX_LIMIT`, `DEFAULT_THREADS`)
- **Private members**: `camelCase` (e.g., `sieve`, `limit`, `generated`)

### Code Style

- **Indentation**: 4 spaces (no tabs)
- **Line length**: Maximum 100 characters
- **Braces**: Opening brace on same line (K&R style)
- **Spacing**: Space after keywords, around operators

### Example Code Pattern

```cpp
class MySieve {
public:
    std::vector<uint64_t> findPrimes(uint64_t limit) {
        if (limit < 2) {
            return {};
        }
        // Implementation
    }

private:
    std::vector<uint64_t> primes;
};
```

## Testing Guidelines

- All new features must include tests
- Place tests in `tests/` directory
- Name test files: `test_<ComponentName>.cpp`
- Use Google Test framework
- Test edge cases and boundary conditions

### Test Example

```cpp
#include <gtest/gtest.h>
#include "BasicSieve.hpp"

TEST(BasicSieveTest, SmallRange) {
    BasicSieve sieve;
    auto primes = sieve.findPrimes(10);
    ASSERT_EQ(primes.size(), 4);
    EXPECT_EQ(primes[0], 2);
    EXPECT_EQ(primes[1], 3);
    EXPECT_EQ(primes[2], 5);
    EXPECT_EQ(primes[3], 7);
}
```

## Performance Considerations

- Profile before optimizing
- Use appropriate data structures for cache locality
- Minimize memory allocations
- Use OpenMP for parallelizable operations
- Consider bit-level optimizations for memory-intensive operations

## Key Algorithms

1. **Basic Sieve**: Standard boolean array implementation
2. **Bit Sieve**: 8x memory reduction using bit manipulation
3. **Wheel Sieve**: ~73% operation reduction using 2,3,5-wheel factorization
4. **Parallel versions**: OpenMP-based multi-threaded implementations

## Commit Message Format

```
<type>: <short summary>

<detailed description (optional)>

<issue reference (optional)>
```

Types: `feat`, `fix`, `docs`, `test`, `perf`, `refactor`, `style`, `chore`
