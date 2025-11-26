#!/bin/bash

# Exit on any error
set -e

# Create build directory if it doesn't exist
if [ ! -d "build" ]; then
    mkdir build
fi

# Change to build directory
cd build

# Install dependencies with Conan
conan install .. --build=missing

# Configure with CMake
cmake .. -DCMAKE_BUILD_TYPE=Release

# Build the project
cmake --build .

# Run tests
ctest --verbose

echo "Build completed successfully!"