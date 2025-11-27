#!/bin/bash

# Exit on any error
set -e

# Create build directory if it doesn't exist
if [ ! -d "build" ]; then
    mkdir build
fi

# Install dependencies with Conan
conan install . --output-folder=build --build=missing

# Configure with CMake using Conan preset
cmake --preset conan-release

# Build the project
cmake --build --preset conan-release

# Run tests
ctest --preset conan-release

echo "Build completed successfully!"