# Prime Number Finder using Sieve of Eratosthenes

A high-performance C++ application that efficiently finds prime numbers using the Sieve of Eratosthenes algorithm, with multiple optimizations for large number ranges and memory efficiency.

## Features

- **Basic Sieve**: Standard implementation of the Sieve of Eratosthenes algorithm
- **Bit-Optimized Sieve**: Memory-efficient implementation using bit manipulation (8x memory reduction)
- **Wheel Factorization**: Performance-optimized implementation using 2,3,5-wheel factorization (~73% reduction in operations)
- **Parallel Processing**: Multi-threaded execution using OpenMP for improved performance on multi-core systems
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
- OpenMP support (for parallel processing)

### Build Instructions

1. Clone the repository:
   ```bash
   git clone <repository-url>
   cd primenumbersolver
   ```

2. Install dependencies using Conan:
   ```bash
   conan install . --output-folder=build --build=missing
   ```

3. Build the project:
   ```bash
   cmake --preset conan-release
   cmake --build --preset conan-release
   ```

4. Run tests:
   ```bash
   ctest --preset conan-release
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

### Parallel Processing

Find primes up to 10,000,000 using 4 threads with bit-optimized sieve:
```bash
./prime_sieve --limit 10000000 --bit-sieve --threads 4
```

Find primes up to 100,000,000 using wheel factorization with parallel processing:
```bash
./prime_sieve --limit 10000000 --wheel-sieve --threads 8
```

### Command-Line Options

| Option | Description |
|--------|-------------|
| `-l,--limit N` | Upper limit for finding prime numbers (default: 1,000,000) |
| `-c,--count` | Show only the count of prime numbers |
| `-t,--time` | Show execution time |
| `-s,--list` | Show the list of prime numbers |
| `-o,--output FILE` | Save primes to a file |
| `--segmented` | Use segmented sieve for large ranges |
| `--segment-size N` | Segment size for segmented sieve (default: 1,000,000) |
| `--per-line N` | Number of primes to print per line (default: 10) |
| `--bit-sieve` | Use bit-optimized sieve for memory efficiency |
| `--wheel-sieve` | Use 2,3,5-wheel factorization for performance |
| `--threads N` | Number of threads to use (0 for auto-detect) |
| `--parallel` | Enable parallel processing (default) |
| `--no-parallel` | Disable parallel processing |
| `--thread-info` | Display thread information and exit |

### Performance Examples

1. Find primes up to 10,000,000 and show execution time:
   ```bash
   ./prime_sieve --limit 10000000 --time
   ```

2. Find primes up to 1,000,000,000 using bit-optimized sieve with 8 threads:
   ```bash
   ./prime_sieve --limit 1000000000 --bit-sieve --threads 8 --time
   ```

3. Find primes up to 1,000,000,000 using wheel factorization with parallel processing:
   ```bash
   ./prime_sieve --limit 1000000000 --wheel-sieve --threads 8 --time
   ```

4. Run performance benchmarks:
   ```bash
   ./prime_sieve_benchmark 1000000000 4
   ```

5. Display system thread information:
   ```bash
   ./prime_sieve --thread-info
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

#### Parallel Processing with OpenMP

The parallel implementation uses OpenMP to distribute work among multiple CPU cores:

- **Work-sharing approach**: The range is divided among threads for better cache locality
- **Automatic core detection**: Detects available CPU cores and optimizes thread count
- **Load balancing**: Uses appropriate OpenMP scheduling for optimal performance
- **Thread safety**: Proper synchronization for shared data structures

## Testing

The project includes comprehensive unit tests for all sieve implementations:

- Basic Sieve tests (`tests/test_BasicSieve.cpp`)
- Bit-Optimized Sieve tests (`tests/test_BitSieve.cpp`)
- Wheel Factorization tests (`tests/test_WheelSieve.cpp`)
- Parallel processing benchmarks (`src/benchmark_parallel.cpp`)

To run tests:

```bash
ctest --preset conan-release
```

## Future Enhancements

Potential improvements for future versions:

- **Segmented Sieve**: For very large ranges that exceed memory limitations
- **GPU Acceleration**: For very large ranges using CUDA or OpenCL
- **Advanced Sieves**: Implementation of Atkin's sieve or Sundaram's sieve
- **Web Interface**: Cloud deployment with a web-based interface
- **Distributed Computing**: Support for cluster-based prime number generation

## License

This project is licensed under the MIT License - see the LICENSE file for details.

## Contributing

Contributions are welcome! Please read our [Contributing Guidelines](CONTRIBUTING.md) for details on:

- How to set up your development environment
- Coding standards and best practices
- How to submit pull requests
- Testing requirements
- Branch protection rules

For quick contributions, feel free to submit a Pull Request following the guidelines in CONTRIBUTING.md.

## Acknowledgments

- The Sieve of Eratosthenes algorithm is attributed to the ancient Greek mathematician Eratosthenes
- Thanks to the developers of the libraries used: Boost, CLI11, fmt, Google Test, and OpenMP