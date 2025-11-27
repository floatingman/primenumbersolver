#include "BasicSieve.hpp"
#include "BitSieve.hpp"
#include "WheelSieve.hpp"
#include "ParallelBasicSieve.hpp"
#include "ParallelBitSieve.hpp"
#include "ParallelWheelSieve.hpp"
#include <CLI/CLI.hpp>
#include <fmt/format.h>
#include <iostream>
#include <chrono>
#include <string>
#include <fstream>

int main(int argc, char** argv) {
    std::size_t limit = 1000000;  // Default limit: 1,000,000
    bool showCount = false;
    bool showTime = false;
    bool showList = false;
    std::string outputFile;
    bool useSegmented = false;
    bool useBitSieve = false;
    bool useWheelSieve = false;
    std::size_t segmentSize = 1000000;  // Default segment size: 1,000,000
    std::size_t perLine = 10;  // Default primes per line for output
    int threadCount = 0;  // Default: auto-detect
    bool useParallel = true;  // Default: enable parallel processing

    CLI::App app{"Prime Number Finder using Sieve of Eratosthenes"};

    // Add command line options
    app.add_option("-l,--limit", limit, "Upper limit for finding prime numbers")
        ->check(CLI::PositiveNumber);
    
    app.add_flag("-c,--count", showCount, "Show only count of prime numbers");
    
    app.add_flag("-t,--time", showTime, "Show execution time");
    
    app.add_flag("-s,--list", showList, "Show list of prime numbers");
    
    app.add_option("-o,--output", outputFile, "Output file to save primes");
    
    app.add_flag("--segmented", useSegmented, "Use segmented sieve for large ranges");
    
    app.add_option("--segment-size", segmentSize, "Segment size for segmented sieve")
        ->check(CLI::PositiveNumber);
    
    app.add_option("--per-line", perLine, "Number of primes to print per line")
        ->check(CLI::PositiveNumber);
    
    app.add_flag("--bit-sieve", useBitSieve, "Use bit-optimized sieve for memory efficiency");
    
    app.add_flag("--wheel-sieve", useWheelSieve, "Use 2,3,5-wheel factorization for performance");
    
    app.add_option("--threads", threadCount, "Number of threads to use (0 for auto-detect)")
        ->check(CLI::PositiveNumber);
    
    app.add_flag("--parallel", useParallel, "Enable parallel processing (default)")
        ->default_val(true);
    
    app.add_flag("--no-parallel", [](bool no_parallel) { return !no_parallel; }, "Disable parallel processing");
    
    app.add_flag("--thread-info", [](bool) { 
        std::cout << "System information:\n";
        std::cout << "  Logical cores: " << std::thread::hardware_concurrency() << "\n";
        std::cout << "  Max OpenMP threads: " << omp_get_max_threads() << "\n";
        return true; 
    }, "Display thread information and exit");

    CLI11_PARSE(app, argc, argv);

    // Start timer
    auto startTime = std::chrono::high_resolution_clock::now();

    try {
        std::vector<std::size_t> primes;
        std::size_t memoryUsage = 0;
        
        if (useBitSieve) {
            if (useParallel) {
                // Create and run parallel bit-optimized sieve
                ParallelBitSieve sieve(limit, threadCount);
                sieve.generate();
                
                // Get primes and memory usage
                primes = sieve.getPrimes();
                memoryUsage = sieve.getMemoryUsage();
                
                // Stop timer
                auto endTime = std::chrono::high_resolution_clock::now();
                auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);
                
                // Output results
                if (showCount || (!showList && outputFile.empty())) {
                    fmt::print("Found {} prime numbers up to {} (using Parallel BitSieve)\n", primes.size(), limit);
                }
                
                if (showTime) {
                    fmt::print("Execution time: {} ms\n", duration.count());
                    fmt::print("Memory usage: {} bytes\n", memoryUsage);
                    fmt::print("Threads used: {}\n", threadCount);
                    fmt::print("Parallel processing: {}\n", useParallel ? "Yes" : "No");
                }
                
                if (showList) {
                    fmt::print("Prime numbers up to {} (using Parallel BitSieve):\n", limit);
                    sieve.printPrimes(perLine);
                }
                
                if (!outputFile.empty()) {
                    if (sieve.savePrimesToFile(outputFile)) {
                        fmt::print("Primes saved to {}\n", outputFile);
                    } else {
                        fmt::print(stderr, "Error: Could not save primes to {}\n", outputFile);
                        return 1;
                    }
                }
            } else {
                // Use sequential bit-optimized sieve
                BitSieve sieve(limit);
                sieve.generate();
                
                // Get primes and memory usage
                primes = sieve.getPrimes();
                memoryUsage = sieve.getMemoryUsage();
                
                // Stop timer
                auto endTime = std::chrono::high_resolution_clock::now();
                auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);
                
                // Output results
                if (showCount || (!showList && outputFile.empty())) {
                    fmt::print("Found {} prime numbers up to {} (using BitSieve)\n", primes.size(), limit);
                }
                
                if (showTime) {
                    fmt::print("Execution time: {} ms\n", duration.count());
                    fmt::print("Memory usage: {} bytes\n", memoryUsage);
                }
                
                if (showList) {
                    fmt::print("Prime numbers up to {} (using BitSieve):\n", limit);
                    sieve.printPrimes(perLine);
                }
                
                if (!outputFile.empty()) {
                    if (sieve.savePrimesToFile(outputFile)) {
                        fmt::print("Primes saved to {}\n", outputFile);
                    } else {
                        fmt::print(stderr, "Error: Could not save primes to {}\n", outputFile);
                        return 1;
                    }
                }
            }
        } else if (useWheelSieve) {
            if (useParallel) {
                // Create and run parallel wheel-optimized sieve
                ParallelWheelSieve sieve(limit, threadCount);
                sieve.generate();
                
                // Get primes and memory usage
                primes = sieve.getPrimes();
                memoryUsage = sieve.getMemoryUsage();
                
                // Stop timer
                auto endTime = std::chrono::high_resolution_clock::now();
                auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);
                
                // Output results
                if (showCount || (!showList && outputFile.empty())) {
                    fmt::print("Found {} prime numbers up to {} (using Parallel WheelSieve)\n", primes.size(), limit);
                }
                
                if (showTime) {
                    fmt::print("Execution time: {} ms\n", duration.count());
                    fmt::print("Memory usage: {} bytes\n", memoryUsage);
                    fmt::print("Threads used: {}\n", threadCount);
                    fmt::print("Parallel processing: {}\n", useParallel ? "Yes" : "No");
                }
                
                if (showList) {
                    fmt::print("Prime numbers up to {} (using Parallel WheelSieve):\n", limit);
                    sieve.printPrimes(perLine);
                }
                
                if (!outputFile.empty()) {
                    if (sieve.savePrimesToFile(outputFile)) {
                        fmt::print("Primes saved to {}\n", outputFile);
                    } else {
                        fmt::print(stderr, "Error: Could not save primes to {}\n", outputFile);
                        return 1;
                    }
                }
            } else {
                // Use sequential wheel-optimized sieve
                WheelSieve sieve(limit);
                sieve.generate();
                
                // Get primes and memory usage
                primes = sieve.getPrimes();
                memoryUsage = sieve.getMemoryUsage();
                
                // Stop timer
                auto endTime = std::chrono::high_resolution_clock::now();
                auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);
                
                // Output results
                if (showCount || (!showList && outputFile.empty())) {
                    fmt::print("Found {} prime numbers up to {} (using WheelSieve)\n", primes.size(), limit);
                }
                
                if (showTime) {
                    fmt::print("Execution time: {} ms\n", duration.count());
                    fmt::print("Memory usage: {} bytes\n", memoryUsage);
                }
                
                if (showList) {
                    fmt::print("Prime numbers up to {} (using WheelSieve):\n", limit);
                    sieve.printPrimes(perLine);
                }
                
                if (!outputFile.empty()) {
                    if (sieve.savePrimesToFile(outputFile)) {
                        fmt::print("Primes saved to {}\n", outputFile);
                    } else {
                        fmt::print(stderr, "Error: Could not save primes to {}\n", outputFile);
                        return 1;
                    }
                }
            }
        } else {
            if (useParallel) {
                // Create and run parallel basic sieve
                ParallelBasicSieve sieve(limit, threadCount);
                sieve.generate();
                
                // Get primes
                primes = sieve.getPrimes();
                
                // Stop timer
                auto endTime = std::chrono::high_resolution_clock::now();
                auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);
                
                // Output results
                if (showCount || (!showList && outputFile.empty())) {
                    fmt::print("Found {} prime numbers up to {} (using Parallel BasicSieve)\n", primes.size(), limit);
                }
                
                if (showTime) {
                    fmt::print("Execution time: {} ms\n", duration.count());
                    fmt::print("Threads used: {}\n", threadCount);
                    fmt::print("Parallel processing: {}\n", useParallel ? "Yes" : "No");
                }
                
                if (showList) {
                    fmt::print("Prime numbers up to {} (using Parallel BasicSieve):\n", limit);
                    sieve.printPrimes(perLine);
                }
                
                if (!outputFile.empty()) {
                    if (sieve.savePrimesToFile(outputFile)) {
                        fmt::print("Primes saved to {}\n", outputFile);
                    } else {
                        fmt::print(stderr, "Error: Could not save primes to {}\n", outputFile);
                        return 1;
                    }
                }
            } else {
                // Use sequential basic sieve
                BasicSieve sieve(limit);
                sieve.generate();
                
                // Get primes
                primes = sieve.getPrimes();
                
                // Stop timer
                auto endTime = std::chrono::high_resolution_clock::now();
                auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);
                
                // Output results
                if (showCount || (!showList && outputFile.empty())) {
                    fmt::print("Found {} prime numbers up to {} (using BasicSieve)\n", primes.size(), limit);
                }
                
                if (showTime) {
                    fmt::print("Execution time: {} ms\n", duration.count());
                }
                
                if (showList) {
                    fmt::print("Prime numbers up to {} (using BasicSieve):\n", limit);
                    sieve.printPrimes(perLine);
                }
                
                if (!outputFile.empty()) {
                    if (sieve.savePrimesToFile(outputFile)) {
                        fmt::print("Primes saved to {}\n", outputFile);
                    } else {
                        fmt::print(stderr, "Error: Could not save primes to {}\n", outputFile);
                        return 1;
                    }
                }
            }
        }

    } catch (const std::exception& e) {
        fmt::print(stderr, "Error: {}\n", e.what());
        return 1;
    }

    return 0;
}