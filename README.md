# MyString — a small `std::string`-style class built from scratch

[![C++ CI](https://github.com/Jyatin/MyString/actions/workflows/ci.yml/badge.svg)](https://github.com/Jyatin/MyString/actions/workflows/ci.yml)
[![C++17](https://img.shields.io/badge/C%2B%2B-17-00599C.svg)](https://en.cppreference.com/w/cpp/17)

A production-minded custom string implementation in modern C++17. The goal is not to replace `std::string`, but to make the mechanics behind a dynamic string explicit: ownership, heap allocation, deep copying, move semantics, capacity growth, bounds checking, searching, and operator overloading.

> **Constraint:** the implementation does not use `std::string` for its internal storage. It owns a null-terminated `char` buffer and manages that buffer itself.

## What changed

The original project was a compact Rule-of-Five demonstration. It is now organised as a small library with a demo, automated tests, CMake build support, and GitHub Actions CI.

### Core functionality

- Rule of Five: destructor, copy constructor/assignment, move constructor/assignment
- Dynamic heap-backed storage with geometric capacity growth
- Stronger copy-assignment exception safety using copy-and-swap
- `size()`, `length()`, `capacity()`, `empty()`, `clear()`, `reserve()`
- `operator[]`, checked `at()`, `front()`, `back()`
- `c_str()` and mutable/const `data()` access
- `append()` and `operator+=` for strings and characters
- Concatenation with `operator+`
- Equality and lexicographical relational operators
- `find()` for characters and substrings
- `contains()`, `starts_with()`, `ends_with()`
- `substr()` and non-mutating `reversed()`
- Stream insertion/extraction (`<<`, `>>`)
- `std::string_view` construction, including strings containing embedded `\0` bytes
- Self-append protection and a reusable moved-from state

## Project structure

```text
MyString/
├── include/
│   └── MyString.h              # Public class interface
├── src/
│   └── MyString.cpp            # Memory management + implementation
├── examples/
│   └── main.cpp                # Feature demonstration
├── tests/
│   └── test_mystring.cpp       # Assertion-based test suite
├── .github/
│   └── workflows/
│       └── ci.yml              # Build, test and sanitizer CI
├── CMakeLists.txt              # Portable build configuration
└── README.md
```

## Quick start

### GCC / Clang

```bash
g++ -std=c++17 -Wall -Wextra -Wpedantic \
    -Iinclude src/MyString.cpp examples/main.cpp \
    -o mystring_demo

./mystring_demo
```

### CMake

```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --parallel
ctest --test-dir build --output-on-failure
./build/mystring_demo
```

On Windows with a Visual Studio generator, build the same CMake targets from the generated solution or with `cmake --build build --config Release`.

## Demo output

The example exercises construction, concatenation, capacity, append, search, prefix/suffix checks, substring extraction, reversal, deep copy, move construction, and clearing.

```text
=== MyString demo ===
language : Modern C++17
project  : MyString
combined : Modern C++17 - MyString
size     : 24
capacity : 24
append   : Modern C++17 - MyString library
find     : 17
contains : true
prefix   : true
suffix   : true
substr   : C++17
reverse  : yrarbil gnirtSyM - 71++C nredoM
copy     : modern C++17 - MyString library
original : Modern C++17 - MyString library
moved    : modern C++17 - MyString library
moved-from size: 0
cleared  : "" (empty=true)
=== demo complete ===
```

The CI workflow builds this demo and runs the test suite on pushes and pull requests. It also runs the tests under AddressSanitizer and UndefinedBehaviorSanitizer on Ubuntu.

## API at a glance

| API | Purpose | Complexity |
|---|---|---:|
| `size()` / `length()` | Current number of characters | O(1) |
| `capacity()` | Allocated character capacity | O(1) |
| `operator[]` | Unchecked indexed access | O(1) |
| `at()` | Bounds-checked indexed access | O(1) |
| `append()` / `+=` | Add characters or another string | Amortized O(n) |
| `reserve()` | Pre-allocate capacity | O(n) when reallocation occurs |
| `find()` | Find character/subsequence | O(n·m) worst case |
| `substr()` | Create a substring | O(k) |
| `reversed()` | Return a reversed copy | O(n) |
| comparisons | Lexicographical comparison | O(min(n,m)) |

`append()` uses geometric capacity growth, so repeated appends avoid an allocation on every operation.

## Memory-management design

Each `MyString` owns one character buffer and maintains three invariants:

1. `data_[size_]` is always the null terminator.
2. `size_ <= capacity_`.
3. The allocated buffer contains at least `capacity_ + 1` characters.

Copying allocates independent storage, so modifying a copy cannot mutate the source. Moving transfers the owned buffer without copying its characters; the source becomes an empty, reusable object.

Copy assignment uses **copy-and-swap**, which avoids destroying the existing state before the replacement allocation succeeds.

## Testing

The test suite covers:

- default and normal construction
- indexed access and `at()` exceptions
- deep copy semantics
- copy and move assignment
- moved-from object reuse
- capacity preservation after `clear()`
- self-append
- searching and substring boundaries
- lexicographical comparisons
- stream input/output
- embedded null characters

Run it with:

```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build --parallel
ctest --test-dir build --output-on-failure
```

## Why build this instead of using `std::string`?

Because it is a useful systems-programming exercise. Implementing a small string type exposes concepts that are easy to hide behind the standard library:

- RAII and ownership
- Rule of Five
- shallow vs deep copy
- move semantics
- exception safety
- dynamic allocation and reallocation
- object lifetime
- operator overloading
- API design and invariants
- algorithmic complexity

For application development, prefer the battle-tested standard library. For learning C++ internals, this project makes those mechanisms visible.

## License

MIT — see [`LICENSE`](LICENSE).

## Author

**Jyatin Kumar Singh**  
C++ / Full-Stack Developer · Open Source Contributor

GitHub: https://github.com/Jyatin
