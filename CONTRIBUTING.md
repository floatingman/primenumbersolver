# Contributing to Prime Number Solver

Thank you for your interest in contributing to the Prime Number Solver project! This document provides guidelines and instructions for contributing.

## Table of Contents

- [Code of Conduct](#code-of-conduct)
- [Getting Started](#getting-started)
- [Development Setup](#development-setup)
- [How to Contribute](#how-to-contribute)
- [Coding Standards](#coding-standards)
- [Testing Guidelines](#testing-guidelines)
- [Submitting Changes](#submitting-changes)
- [Branch Protection Rules](#branch-protection-rules)
- [Reporting Bugs](#reporting-bugs)
- [Suggesting Enhancements](#suggesting-enhancements)

## Code of Conduct

By participating in this project, you agree to maintain a respectful and inclusive environment. We expect all contributors to:

- Use welcoming and inclusive language
- Be respectful of differing viewpoints and experiences
- Gracefully accept constructive criticism
- Focus on what is best for the community
- Show empathy towards other community members

## Getting Started

1. **Fork the repository** on GitHub
2. **Clone your fork** locally:
   ```bash
   git clone git@github.com:YOUR_USERNAME/primenumbersolver.git
   cd primenumbersolver
   ```
3. **Add the upstream repository**:
   ```bash
   git remote add upstream git@github.com:floatingman/primenumbersolver.git
   ```
4. **Create a feature branch**:
   ```bash
   git checkout -b feature/your-feature-name
   ```

## Development Setup

### Prerequisites

- **CMake** 3.15 or higher
- **C++17** compatible compiler (GCC 7+, Clang 5+, MSVC 2017+)
- **Conan** package manager (version 2.0+)
- **OpenMP** support for parallel processing
- **Git** for version control

### Installing Dependencies

#### Using Conan (Recommended)

```bash
# Install Conan if you haven't already
pip install conan

# Install project dependencies
conan install . --build=missing
```

#### Manual Installation

If you prefer not to use Conan, install these dependencies manually:

- Boost 1.83.0+
- CLI11 2.3.2+
- fmt 10.2.1+
- Google Test 1.14.0+

### Building the Project

#### Quick Build (using build script)

```bash
./build.sh
```

#### Manual Build

```bash
# Install dependencies
conan install . --build=missing

# Configure with CMake
cmake --preset conan-release

# Build
cmake --build . --config Release

# Run tests
ctest --verbose
```

### Running Tests

```bash
# Run all tests
ctest --verbose

# Run specific test suite
./prime_sieve_basic_tests
./prime_sieve_bit_tests
./prime_sieve_wheel_tests

# Run benchmarks
./prime_sieve_benchmark 1000000000 4
```

## How to Contribute

### Types of Contributions

We welcome various types of contributions:

- **Bug fixes**: Fix issues in existing code
- **New features**: Add new sieve algorithms or optimizations
- **Performance improvements**: Optimize existing implementations
- **Documentation**: Improve or expand documentation
- **Tests**: Add or improve test coverage
- **Examples**: Add usage examples or tutorials

### Finding Issues to Work On

- Check the [Issues](https://github.com/floatingman/primenumbersolver/issues) page
- Look for issues labeled `good first issue` or `help wanted`
- Comment on the issue to let others know you're working on it

### Making Changes

1. **Keep changes focused**: One feature or bug fix per pull request
2. **Write clear commit messages**: Follow the format below
3. **Add tests**: All new features should include tests
4. **Update documentation**: Update README.md or other docs as needed
5. **Follow coding standards**: See section below

## Coding Standards

### C++ Style Guidelines

- **Standard**: Follow C++17 best practices
- **Naming conventions**:
  - Classes: `PascalCase` (e.g., `BasicSieve`, `BitSieve`)
  - Functions/methods: `camelCase` (e.g., `findPrimes`, `isPrime`)
  - Variables: `camelCase` (e.g., `primeCount`, `upperLimit`)
  - Constants: `UPPER_CASE` (e.g., `MAX_LIMIT`, `DEFAULT_THREADS`)
  - Private members: prefix with `m_` (e.g., `m_primes`, `m_isPrime`)

### Code Formatting

- **Indentation**: 4 spaces (no tabs)
- **Line length**: Maximum 100 characters
- **Braces**: Opening brace on same line (K&R style)
- **Spacing**: Space after keywords, around operators

Example:
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
    std::vector<uint64_t> m_primes;
};
```

### Comments

- Use comments to explain **why**, not **what**
- Document public APIs with clear descriptions
- Keep comments up-to-date with code changes
- Use TODO comments for future improvements:
  ```cpp
  // TODO: Optimize memory usage for very large ranges
  ```

### Performance Considerations

- Profile before optimizing
- Use appropriate data structures
- Consider cache locality
- Minimize memory allocations
- Use OpenMP for parallelizable operations

## Testing Guidelines

### Test Requirements

- All new features **must** include tests
- Bug fixes should include regression tests
- Aim for high code coverage (>80%)
- Tests should be fast and deterministic

### Writing Tests

Tests use Google Test framework:

```cpp
#include <gtest/gtest.h>
#include "BasicSieve.hpp"

TEST(BasicSieveTest, SmallRange) {
    BasicSieve sieve(10);
    sieve.generate();
    auto primes = sieve.getPrimes();
    ASSERT_EQ(primes.size(), 4);
    EXPECT_EQ(primes[0], 2);
    EXPECT_EQ(primes[1], 3);
    EXPECT_EQ(primes[2], 5);
    EXPECT_EQ(primes[3], 7);
}
```

### Test Organization

- Place tests in the `tests/` directory
- Name test files: `test_<ComponentName>.cpp`
- Group related tests using test fixtures
- Test edge cases and boundary conditions

## Submitting Changes

### Commit Message Format

Use clear, descriptive commit messages:

```
<type>: <short summary>

<detailed description (optional)>

<issue reference (optional)>
```

**Types:**
- `feat`: New feature
- `fix`: Bug fix
- `docs`: Documentation changes
- `test`: Adding or updating tests
- `perf`: Performance improvement
- `refactor`: Code refactoring
- `style`: Code style changes (formatting, etc.)
- `chore`: Build process or auxiliary tool changes

**Examples:**
```
feat: Add parallel wheel sieve implementation

Implements a parallel version of the wheel factorization sieve
using OpenMP for better performance on multi-core systems.

Closes #42
```

```
fix: Correct off-by-one error in bit sieve

The bit sieve was incorrectly marking the upper limit as composite
when it was actually prime.

Fixes #38
```

### Pull Request Process

1. **Update your branch** with the latest upstream changes:
   ```bash
   git fetch upstream
   git rebase upstream/main
   ```

2. **Push your changes** to your fork:
   ```bash
   git push origin feature/your-feature-name
   ```

3. **Create a Pull Request** on GitHub:
   - Use a clear, descriptive title
   - Reference related issues
   - Describe what changed and why
   - Include any relevant performance data
   - Add screenshots if applicable

4. **PR Description Template**:
   ```markdown
   ## Description
   Brief description of the changes

   ## Type of Change
   - [ ] Bug fix
   - [ ] New feature
   - [ ] Performance improvement
   - [ ] Documentation update

   ## Testing
   - [ ] All existing tests pass
   - [ ] Added new tests for changes
   - [ ] Manually tested the changes

   ## Checklist
   - [ ] Code follows project style guidelines
   - [ ] Documentation has been updated
   - [ ] No new warnings introduced
   - [ ] Performance benchmarks run (if applicable)

   ## Related Issues
   Closes #<issue_number>
   ```

5. **Code Review**:
   - Address reviewer feedback promptly
   - Push updates to the same branch
   - Request re-review after changes

## Branch Protection Rules

The `main` branch is protected with the following rules:

- ✅ **Pull Request Required**: All changes must go through a pull request
- ✅ **Review Required**: At least 1 approving review is required
- ✅ **Status Checks**: All tests must pass before merging
- ✅ **Linear History**: Merge commits are not allowed (use rebase or squash)
- ✅ **Conversation Resolution**: All review comments must be resolved
- ✅ **No Force Pushes**: Force pushes to main are disabled
- ✅ **Admin Enforcement**: Rules apply to all contributors including admins

### Working with Branch Protection

When your PR is approved:
1. Ensure all conversations are resolved
2. Rebase your branch if needed: `git rebase upstream/main`
3. The merge will be completed by a maintainer

## Reporting Bugs

### Before Submitting a Bug Report

- Check the [Issues](https://github.com/floatingman/primenumbersolver/issues) page for existing reports
- Verify the bug exists in the latest version
- Collect relevant information (OS, compiler version, etc.)

### Bug Report Template

```markdown
**Describe the bug**
A clear description of what the bug is.

**To Reproduce**
Steps to reproduce the behavior:
1. Run command '...'
2. With parameters '...'
3. See error

**Expected behavior**
What you expected to happen.

**Actual behavior**
What actually happened.

**Environment:**
- OS: [e.g., Ubuntu 22.04]
- Compiler: [e.g., GCC 11.3]
- CMake version: [e.g., 3.22]
- Conan version: [e.g., 2.0.0]

**Additional context**
Any other relevant information.
```

## Suggesting Enhancements

### Enhancement Suggestions

We welcome ideas for improvements! When suggesting enhancements:

1. **Check existing suggestions** in Issues
2. **Provide a clear use case**
3. **Consider performance implications**
4. **Think about backward compatibility**

### Enhancement Template

```markdown
**Enhancement Description**
Clear description of the proposed enhancement.

**Use Case**
Why is this enhancement needed?

**Proposed Solution**
How would you implement this?

**Alternatives Considered**
Other approaches you've thought about.

**Performance Impact**
Expected impact on performance.
```

## Performance Benchmarking

When making performance-related changes:

1. **Benchmark before and after**:
   ```bash
   # Baseline
   ./prime_sieve_benchmark 1000000000 8

   # After changes
   ./prime_sieve_benchmark 1000000000 8
   ```

2. **Include results** in your PR description
3. **Test multiple thread counts**: 1, 2, 4, 8 threads
4. **Test different range sizes**: 10^6, 10^8, 10^9

## Getting Help

- **Questions?** Open a [Discussion](https://github.com/floatingman/primenumbersolver/discussions)
- **Stuck?** Comment on the issue you're working on
- **Need clarification?** Ask in the pull request

## Recognition

Contributors will be acknowledged in:
- The project README
- Release notes
- Git commit history

Thank you for contributing to Prime Number Solver! 🎉
