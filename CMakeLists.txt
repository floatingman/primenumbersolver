cmake_minimum_required(VERSION 3.15)
project(PrimeNumberSolver VERSION 1.0.0 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Set compilation flags for optimization
if(CMAKE_BUILD_TYPE STREQUAL "Release")
    add_compile_options(-O3 -march=native -flto -DNDEBUG)
endif()

# Find required packages
find_package(Boost REQUIRED)
find_package(CLI11 REQUIRED)
find_package(fmt REQUIRED)
find_package(OpenMP REQUIRED)
find_package(GTest REQUIRED)

# Add source files
set(SOURCES
    src/BasicSieve.cpp
    src/BitSieve.cpp
    src/WheelSieve.cpp
    src/main.cpp
)

set(HEADERS
    include/BasicSieve.hpp
    include/BitSieve.hpp
    include/WheelSieve.hpp
)

# Create the main executable
add_executable(prime_sieve ${SOURCES} ${HEADERS})

# Link libraries
target_link_libraries(prime_sieve 
    PRIVATE 
    Boost::boost 
    CLI11::CLI11 
    fmt::fmt 
    OpenMP::OpenMP_CXX
)

# Include directories
target_include_directories(prime_sieve 
    PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Add test executables
set(BASIC_TEST_SOURCES
    tests/test_BasicSieve.cpp
    src/BasicSieve.cpp
)

add_executable(prime_sieve_basic_tests ${BASIC_TEST_SOURCES} ${HEADERS})

# Link test libraries
target_link_libraries(prime_sieve_basic_tests
    PRIVATE
    GTest::gtest
    GTest::gtest_main
)

# Include directories for tests
target_include_directories(prime_sieve_basic_tests
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Add BitSieve test executable
set(BIT_TEST_SOURCES
    tests/test_BitSieve.cpp
    src/BasicSieve.cpp
    src/BitSieve.cpp
)

add_executable(prime_sieve_bit_tests ${BIT_TEST_SOURCES} ${HEADERS})

# Link test libraries
target_link_libraries(prime_sieve_bit_tests
    PRIVATE
    GTest::gtest
    GTest::gtest_main
)

# Include directories for tests
target_include_directories(prime_sieve_bit_tests
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Add WheelSieve test executable
set(WHEEL_TEST_SOURCES
    tests/test_WheelSieve.cpp
    src/BasicSieve.cpp
    src/BitSieve.cpp
    src/WheelSieve.cpp
)

add_executable(prime_sieve_wheel_tests ${WHEEL_TEST_SOURCES} ${HEADERS})

# Link test libraries
target_link_libraries(prime_sieve_wheel_tests
    PRIVATE
    GTest::gtest
    GTest::gtest_main
)

# Include directories for tests
target_include_directories(prime_sieve_wheel_tests
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Enable testing
enable_testing()
add_test(NAME BasicSieveTest COMMAND prime_sieve_basic_tests)
add_test(NAME BitSieveTest COMMAND prime_sieve_bit_tests)
add_test(NAME WheelSieveTest COMMAND prime_sieve_wheel_tests)

# Install targets
install(TARGETS prime_sieve DESTINATION bin)