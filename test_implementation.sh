#!/bin/bash

# Test script to verify that our prime number finder works correctly

echo "Building the project..."
mkdir -p build
cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
cmake --build .

if [ $? -ne 0 ]; then
    echo "Build failed!"
    exit 1
fi

echo "Build successful!"

# Test with a small limit
echo "Testing with limit 30..."
./prime_sieve --limit 30 --list > output_small.txt

# Check if the output contains the expected primes
expected_primes="2 3 5 7 11 13 17 19 23 29"
actual_primes=$(grep -o '[0-9]\+' output_small.txt | tr '\n' ' ')

if [ "$actual_primes" = "$expected_primes " ]; then
    echo "✓ Small test passed!"
else
    echo "✗ Small test failed!"
    echo "Expected: $expected_primes"
    echo "Actual:   $actual_primes"
    exit 1
fi

# Test with bit sieve
echo "Testing with bit sieve and limit 100..."
./prime_sieve --limit 100 --bit-sieve --count > output_bit.txt

if grep -q "Found 25 prime numbers up to 100" output_bit.txt; then
    echo "✓ Bit sieve test passed!"
else
    echo "✗ Bit sieve test failed!"
    cat output_bit.txt
    exit 1
fi

# Test with wheel sieve
echo "Testing with wheel sieve and limit 100..."
./prime_sieve --limit 100 --wheel-sieve --count > output_wheel.txt

if grep -q "Found 25 prime numbers up to 100" output_wheel.txt; then
    echo "✓ Wheel sieve test passed!"
else
    echo "✗ Wheel sieve test failed!"
    cat output_wheel.txt
    exit 1
fi

# Test file output
echo "Testing file output..."
./prime_sieve --limit 30 --output primes_test.txt

if [ -f primes_test.txt ]; then
    file_primes=$(cat primes_test.txt | tr '\n' ' ')
    if [ "$file_primes" = "$expected_primes " ]; then
        echo "✓ File output test passed!"
    else
        echo "✗ File output test failed!"
        echo "Expected: $expected_primes"
        echo "Actual:   $file_primes"
        exit 1
    fi
else
    echo "✗ File output test failed - file not created!"
    exit 1
fi

# Test timing functionality
echo "Testing timing functionality..."
./prime_sieve --limit 1000 --time > output_time.txt

if grep -q "Execution time:" output_time.txt; then
    echo "✓ Timing test passed!"
else
    echo "✗ Timing test failed!"
    cat output_time.txt
    exit 1
fi

echo "All tests passed! ✓"

# Clean up
cd ..
rm -rf build output_*.txt primes_test.txt