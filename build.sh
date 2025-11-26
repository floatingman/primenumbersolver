#!/bin/bash

# Exit on any error
set -e

# Create build directory if it doesn't exist
if [ ! -d "build" ]; then
    mkdir build
fi

# Install dependencies with Conan
conan install . --build=missing

# Configure with CMake using Conan preset
cmake --preset conan-release

# Build the project
cmake --build . --config Release

# Run tests
ctest --verbose

echo "Build completed successfully!"