# Prime Number Finder using Sieve of Eratosthenes

A high-performance C++ application that efficiently finds prime numbers using the Sieve of Eratosthenes algorithm, with multiple optimizations for large number ranges and memory efficiency.

## Features

- **Basic Sieve**: Standard implementation of the Sieve of Eratosthenes algorithm
- **Bit-Optimized Sieve**: Memory-efficient implementation using bit manipulation (8x memory reduction)
- **Wheel Factorization**: Performance-optimized implementation using 2,3,5-wheel factorization (~73% reduction in operations)
- **Command-Line Interface**: Flexible CLI with multiple options for different use cases
- **Performance Monitoring**: Built-in timing and memory usage tracking
- **Multiple Output Formats**: Support for console output, file output, and count-only display

## Performance Targets

- Small range (10^6): < 0.1 seconds
- Medium range (10^8): < 5 seconds
- Large range (10^9): < 60 seconds
- Memory usage: ~125MB for 10^9 (bit array)

## Building the Project

### Prerequisites

- CMake 3.15 or higher
- C++17 compatible compiler
- Conan package manager (recommended for dependency management)

### Build Instructions

1. Clone the repository:
   ```bash
   git clone <repository-url>
   cd primenumbersolver
   ```

2. Install dependencies using Conan:
   ```bash
   conan install . --build=missing
   ```

3. Build the project:
   ```bash
   mkdir build && cd build
   cmake .. -DCMAKE_BUILD_TYPE=Release
   cmake --build .
   ```

4. Run tests:
   ```bash
   ctest --verbose
   ```

### Alternative Build (without Conan)

If you prefer not to use Conan, you can install the dependencies manually:

- Boost (math utilities)
- CLI11 (command-line parsing)
- fmt (formatting library)
- Google Test (testing framework)
- OpenMP (parallel processing)

Then build with CMake as shown above.

## Usage

### Basic Usage

Find all prime numbers up to 1,000,000:
```bash
./prime_sieve --limit 1000000
```

### Command-Line Options

| Option | Description |
|--------|-------------|
| `-l, --limit N` | Upper limit for finding prime numbers (default: 1,000,000) |
| `-c, --count` | Show only the count of prime numbers |
| `-t, --time` | Show execution time |
| `-s, --list` | Show the list of prime numbers |
| `-o, --output FILE` | Save primes to a file |
| `--bit-sieve` | Use bit-optimized sieve for memory efficiency |
| `--wheel-sieve` | Use 2,3,5-wheel factorization for performance |
| `--segmented` | Use segmented sieve for large ranges |
| `--segment-size N` | Segment size for segmented sieve (default: 1,000,000) |
| `--per-line N` | Number of primes to print per line (default: 10) |

### Examples

1. Find primes up to 10,000,000 and show execution time:
   ```bash
   ./prime_sieve --limit 10000000 --time
   ```

2. Find primes up to 1,000,000,000 using bit-optimized sieve:
   ```bash
   ./prime_sieve --limit 1000000000 --bit-sieve --time
   ```

3. Find primes up to 100,000,000 using wheel factorization:
   ```bash
   ./prime_sieve --limit 100000000 --wheel-sieve --time
   ```

4. Save primes to a file:
   ```bash
   ./prime_sieve --limit 1000000 --output primes.txt
   ```

5. Show only the count of primes:
   ```bash
   ./prime_sieve --limit 1000000 --count --time
   ```

## Algorithm Details

### Sieve of Eratosthenes

The Sieve of Eratosthenes is an ancient algorithm for finding all prime numbers up to a specified limit. It works by:

1. Creating a list of consecutive integers from 2 through n
2. Marking all multiples of 2 (except 2 itself)
3. Finding the next unmarked number and marking its multiples
4. Repeating until p² > n
5. The remaining unmarked numbers are primes

### Optimizations Implemented

#### Bit-Optimized Sieve

Instead of using a boolean array (1 byte per number), we use a bit array (1 bit per number), reducing memory usage by a factor of 8.

#### Wheel Factorization

The 2,3,5-wheel factorization optimization skips multiples of 2, 3, and 5, reducing the number of operations by approximately 73%. This is achieved by:

1. Pre-marking multiples of 2, 3, and 5
2. Using a wheel pattern to skip these multiples during sieve generation
3. Only checking numbers that are not multiples of 2, 3, or 5

## Testing

The project includes comprehensive unit tests for all sieve implementations:

- Basic Sieve tests (`tests/test_BasicSieve.cpp`)
- Bit-Optimized Sieve tests (`tests/test_BitSieve.cpp`)
- Wheel Factorization tests (`tests/test_WheelSieve.cpp`)

To run the tests:

```bash
cd build
./prime_sieve_basic_tests
./prime_sieve_bit_tests
./prime_sieve_wheel_tests
```

Or using CTest:

```bash
ctest --verbose
```

## Future Enhancements

Potential improvements for future versions:

- **Segmented Sieve**: For very large ranges that exceed memory limitations
- **Parallel Processing**: Using OpenMP for multi-threaded execution
- **GPU Acceleration**: For very large ranges using CUDA or OpenCL
- **Advanced Sieves**: Implementation of Atkin's sieve or Sundaram's sieve
- **Web Interface**: Cloud deployment with a web-based interface

## License

This project is licensed under the MIT License - see the LICENSE file for details.

## Contributing

Contributions are welcome! Please feel free to submit a Pull Request.

## Acknowledgments

- The Sieve of Eratosthenes algorithm is attributed to the ancient Greek mathematician Eratosthenes
- Thanks to the developers of the libraries used: Boost, CLI11, fmt, Google Test, and OpenMP