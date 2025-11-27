#include "BasicSieve.hpp"
#include "BitSieve.hpp"
#include "WheelSieve.hpp"
#include "ParallelBasicSieve.hpp"
#include "ParallelBitSieve.hpp"
#include "ParallelWheelSieve.hpp"
#include <chrono>
#include <iostream>
#include <iomanip>
#include <sstream>

/**
 * @struct BenchmarkResult
 * @brief Structure to hold benchmark results for comparison.
 */
struct BenchmarkResult
{
    std::size_t limit;
    std::string algorithm;
    int threadCount;
    double sequentialTime;
    double parallelTime;
    double speedup;
    std::size_t memoryUsage;

    BenchmarkResult(std::size_t lim, const std::string &algo, int threads,
                    double seqTime, double parTime, std::size_t mem)
        : limit(lim), algorithm(algo), threadCount(threads),
          sequentialTime(seqTime), parallelTime(parTime), speedup(parTime > 0 ? seqTime / parTime : 0.0),
          memoryUsage(mem) {}
};

/**
 * @brief Run benchmark comparing sequential vs parallel performance.
 * @param limit Upper limit for prime numbers.
 * @param threadCount Number of threads to use for parallel tests.
 */
void runBenchmark(std::size_t limit, int threadCount)
{
    std::vector<BenchmarkResult> results;

    // Benchmark BasicSieve
    {
        auto start = std::chrono::high_resolution_clock::now();
        BasicSieve basicSieve(limit);
        basicSieve.generate();
        auto end = std::chrono::high_resolution_clock::now();
        double seqTime = std::chrono::duration<double, std::milli>(end - start).count();
        std::size_t basicMemory = limit + 1;

        start = std::chrono::high_resolution_clock::now();
        ParallelBasicSieve parallelBasicSieve(limit, threadCount);
        parallelBasicSieve.generate();
        end = std::chrono::high_resolution_clock::now();
        double parTime = std::chrono::duration<double, std::milli>(end - start).count();
        std::size_t parallelMemory = limit + 1;

        BenchmarkResult basicResult(limit, "BasicSieve", threadCount,
                                    seqTime, parTime, basicMemory);
        results.push_back(basicResult);
    }

    // Benchmark BitSieve
    {
        auto start = std::chrono::high_resolution_clock::now();
        BitSieve bitSieve(limit);
        bitSieve.generate();
        auto end = std::chrono::high_resolution_clock::now();
        double seqTime = std::chrono::duration<double, std::milli>(end - start).count();
        std::size_t bitMemory = bitSieve.getMemoryUsage();

        start = std::chrono::high_resolution_clock::now();
        ParallelBitSieve parallelBitSieve(limit, threadCount);
        parallelBitSieve.generate();
        end = std::chrono::high_resolution_clock::now();
        double parTime = std::chrono::duration<double, std::milli>(end - start).count();
        std::size_t parallelMemory = parallelBitSieve.getMemoryUsage();

        BenchmarkResult bitResult(limit, "BitSieve", threadCount,
                                  seqTime, parTime, bitMemory);
        results.push_back(bitResult);
    }

    // Benchmark WheelSieve
    {
        auto start = std::chrono::high_resolution_clock::now();
        WheelSieve wheelSieve(limit);
        wheelSieve.generate();
        auto end = std::chrono::high_resolution_clock::now();
        double seqTime = std::chrono::duration<double, std::milli>(end - start).count();
        std::size_t wheelMemory = wheelSieve.getMemoryUsage();

        start = std::chrono::high_resolution_clock::now();
        ParallelWheelSieve parallelWheelSieve(limit, threadCount);
        parallelWheelSieve.generate();
        end = std::chrono::high_resolution_clock::now();
        double parTime = std::chrono::duration<double, std::milli>(end - start).count();
        std::size_t parallelMemory = parallelWheelSieve.getMemoryUsage();

        BenchmarkResult wheelResult(limit, "WheelSieve", threadCount,
                                    seqTime, parTime, wheelMemory);
        results.push_back(wheelResult);
    }

    // Print results
    std::cout << "Benchmark Results for limit " << limit << " with " << threadCount << " threads:\n\n";
    std::cout << std::left << std::setw(15) << std::setfill(' ') << "Algorithm"
              << std::setw(12) << "Sequential (ms)"
              << std::setw(15) << "Parallel (ms)"
              << std::setw(10) << "Speedup"
              << std::setw(15) << "Seq Memory (bytes)"
              << std::setw(18) << "Par Memory (bytes)" << "\n";
    std::cout << std::string(65, '-') << "\n";

    for (const auto &result : results)
    {
        std::cout << std::left << std::setw(12) << result.algorithm
                  << std::setw(15) << std::fixed << std::setprecision(2) << result.sequentialTime
                  << std::setw(18) << std::fixed << std::setprecision(2) << result.parallelTime
                  << std::setw(8) << std::fixed << std::setprecision(2) << result.speedup
                  << std::setw(18) << result.memoryUsage << "\n";
    }
}

/**
 * @brief Main function to run performance benchmarks.
 */
int main(int argc, char **argv)
{
    if (argc < 3)
    {
        std::cerr << "Usage: " << argv[0] << " <limit> <threads>\n";
        std::cerr << "  <limit>: Upper limit for prime numbers\n";
        std::cerr << "  <threads>: Number of threads to use\n";
        return 1;
    }

    std::size_t limit = std::stoull(argv[1]);
    int threadCount = std::stoi(argv[2]);

    std::cout << "Running benchmarks...\n";
    runBenchmark(limit, threadCount);

    return 0;
}