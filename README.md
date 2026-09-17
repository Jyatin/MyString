# MyString — A `std::string`-Style Class Built from Scratch

[![C++ CI](https://github.com/Jyatin/MyString/actions/workflows/ci.yml/badge.svg)](https://github.com/Jyatin/MyString/actions/workflows/ci.yml)
[![C++17](https://img.shields.io/badge/C%2B%2B-17-00599C.svg)](https://en.cppreference.com/w/cpp/17)
[![License](https://img.shields.io/badge/License-MIT-green.svg)](LICENSE)

> A systems-oriented C++17 string implementation focused on **memory ownership, Rule of Five, move semantics, dynamic capacity growth, exception safety, and API design**.

`MyString` is a small `std::string`-style class implemented without using `std::string` as its internal storage. Each object owns a dynamically allocated, null-terminated character buffer and manages that resource explicitly.

**This project is not intended to replace `std::string`.** It is an engineering exercise designed to make the mechanisms behind a high-level string abstraction visible and testable.

---

## ✨ Highlights

- 🧠 **Rule of Five** — explicit copy/move ownership semantics
- 💾 **Manual dynamic storage** — heap-backed character buffer
- 📈 **Geometric capacity growth** — efficient repeated appends
- 🛡️ **Exception-aware assignment** — copy-and-swap
- 🔎 **Searching** — character and substring search
- ✂️ **String operations** — append, substring, reverse, prefix/suffix checks
- ⚡ **Move semantics** — ownership transfer without character copying
- 🧪 **Automated tests** — edge cases and ownership behavior
- 🔧 **CMake support** — portable project configuration
- 🤖 **GitHub Actions CI** — build, test, and sanitizer validation
- 🧩 **C++17 API** — including `std::string_view` construction

---

## 📌 Engineering Case Study

### Project Background

A string looks simple at the API level, but implementing one from scratch requires solving several systems-level problems: resource ownership, object lifetime, dynamic allocation, copying, moving, resizing, bounds checking, and exception safety.

The purpose of `MyString` was to expose those mechanisms rather than hide them behind the standard library.

### Major Engineering Challenges

**1. Resource Ownership**  
Each object owns its character buffer and is responsible for allocating, resizing, and releasing it safely.

**2. Rule of Five**  
The implementation explicitly handles destruction, copying, copy assignment, moving, and move assignment so ownership is never accidentally shared.

**3. Capacity Management**  
The class maintains separate `size` and `capacity` values and grows the allocation geometrically. This avoids reallocating the buffer for every append.

**4. Exception Safety**  
Copy assignment uses the **copy-and-swap** technique so the existing object is not destroyed before replacement state has been prepared successfully.

**5. API Safety**  
The interface provides unchecked `operator[]` as well as bounds-checked `at()`, plus `front()`, `back()`, `c_str()`, and `data()` access.

### Design Flow

```text
User-facing API
      ↓
Object lifetime
      ↓
Resource ownership
      ↓
Heap allocation
      ↓
Copy / Move semantics
      ↓
Capacity management
      ↓
Algorithms + operators
      ↓
Tests + sanitizers + CI
```

### Key Learning

Building a small string implementation makes concepts such as **RAII, deep copy, move semantics, dynamic arrays, exception safety, invariants, and amortized complexity** concrete instead of purely theoretical.

➡️ **Read the full technical case study:** [`docs/ENGINEERING_CASE_STUDY.md`](docs/ENGINEERING_CASE_STUDY.md)

---

## 🚀 Functionality

### Construction & ownership

- Default and C-string construction
- Character construction
- `std::string_view` construction
- Deep copy construction
- Move construction
- Copy assignment
- Move assignment
- Self-assignment handling

### Capacity & mutation

- `size()` / `length()`
- `capacity()`
- `empty()`
- `clear()`
- `reserve()`
- `resize()`
- `push_back()`
- `append()`
- `operator+=`

### Access

- `operator[]`
- `at()` with bounds checking
- `front()` / `back()`
- `data()`
- `c_str()`

### Algorithms & utilities

- `find()` for characters and substrings
- `contains()`
- `starts_with()`
- `ends_with()`
- `substr()`
- `reversed()`

### Operators

- `operator+`
- `operator+=`
- `==`, `!=`
- `<`, `<=`, `>`, `>=`
- stream insertion `<<`
- stream extraction `>>`

---

## 🏗️ Architecture

The implementation is deliberately split into public interface, implementation, examples, and tests:

```text
MyString/
│
├── include/
│   └── MyString.h
│
├── src/
│   └── MyString.cpp
│
├── examples/
│   └── main.cpp
│
├── tests/
│   └── test_mystring.cpp
│
├── docs/
│   └── ENGINEERING_CASE_STUDY.md
│
├── .github/
│   └── workflows/
│       └── ci.yml
│
├── CMakeLists.txt
├── LICENSE
└── README.md
```

### Why this structure?

| Directory | Responsibility |
|---|---|
| `include/` | Public API exposed to users |
| `src/` | Implementation and memory-management logic |
| `examples/` | Runnable feature demonstration |
| `tests/` | Automated behavioral and edge-case tests |
| `docs/` | Deeper engineering documentation |
| `.github/` | Continuous integration |

---

## ⚡ Quick Start

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

### Windows + Visual Studio generator

```bash
cmake -S . -B build
cmake --build build --config Release
ctest --test-dir build -C Release --output-on-failure
```

---

## 🖥️ Demo

The example demonstrates construction, concatenation, append, searching, prefix/suffix checks, substring extraction, reversal, deep copying, move construction, and clearing.

```text
=== MyString demo ===
language : Modern C++17
project  : MyString
combined : Modern C++17 - MyString
size     : 23
capacity : 30
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

The output is generated by the runnable example in [`examples/main.cpp`](examples/main.cpp).

---

## 🧮 API & Complexity

| API | Purpose | Complexity |
|---|---|---:|
| `size()` / `length()` | Current character count | O(1) |
| `capacity()` | Allocated character capacity | O(1) |
| `operator[]` | Unchecked indexed access | O(1) |
| `at()` | Bounds-checked access | O(1) |
| `push_back()` | Add one character | Amortized O(1) |
| `append()` | Add another sequence | O(n) |
| `reserve()` | Increase allocated capacity | O(n) if reallocation occurs |
| `find()` | Search for character/subsequence | O(n·m) worst case |
| `substr()` | Create a substring | O(k) |
| `reversed()` | Return reversed copy | O(n) |
| comparisons | Lexicographical comparison | O(min(n,m)) |

The exact constant factors depend on allocation and input size. The important design choice is that geometric capacity growth avoids a fresh allocation for every single append.

---

## 🧠 Memory Management

Each object maintains three important pieces of state:

```text
                    MyString
                ┌──────────────┐
                │ data_        │ ──────► [characters ... '\0']
                │ size_        │
                │ capacity_    │
                └──────────────┘
```

The core invariants are:

1. `size_ <= capacity_`.
2. `data_[size_]` is the null terminator.
3. The allocation contains at least `capacity_ + 1` characters.

### Copy

```text
original ──► [H e l l o \0]
                  ↑
                copy
                  ↓
copy     ──► [H e l l o \0]
```

The copy owns independent storage, so modifying it does not modify the original.

### Move

```text
source ──► [H e l l o \0]
              │
              │ ownership transfer
              ▼
target ──► [H e l l o \0]

source ──► empty / reusable state
```

Move construction transfers the buffer instead of copying every character.

---

## 🛡️ Exception Safety

Copy assignment follows the **copy-and-swap** pattern:

```text
Existing object
      │
      ├── create copy ──► temporary
      │                     │
      │                     ▼
      └───────────────► swap resources
                            │
                            ▼
                     temporary destroyed
```

This keeps replacement state separate from the existing object until the copy has been successfully created.

---

## 🧪 Testing

The test suite covers normal behavior, ownership semantics, and edge cases including:

- default and normal construction
- indexed access
- `at()` boundary errors
- deep copy semantics
- copy assignment
- move construction
- move assignment
- moved-from object reuse
- self-assignment
- self-append
- capacity behavior after `clear()`
- searching
- substring boundaries
- lexicographical comparisons
- stream input/output
- embedded null characters

Run the tests with:

```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build --parallel
ctest --test-dir build --output-on-failure
```

### Sanitizers

The CI workflow also validates the test suite using:

- AddressSanitizer
- UndefinedBehaviorSanitizer

This is particularly useful for a project that deliberately manages dynamic memory.

---

## 🤖 Continuous Integration

GitHub Actions automatically builds and tests the project on pushes and pull requests. The sanitizer job provides an additional memory/undefined-behavior check on Ubuntu.

This keeps the repository closer to a real library workflow rather than relying only on a manually run demo.

---

## 🎯 Why Build This Instead of Using `std::string`?

In normal application development, **use `std::string`**. It is mature, portable, optimized, and heavily tested.

`MyString` exists for a different reason: understanding what a string abstraction has to do internally.

The project provides hands-on practice with:

- RAII
- resource ownership
- shallow vs. deep copy
- Rule of Five
- move semantics
- exception safety
- dynamic memory allocation
- capacity growth
- object lifetime
- operator overloading
- API contracts
- class invariants
- algorithmic complexity
- automated testing
- CI and sanitizers

---

## 🔮 Future Improvements

Possible extensions:

- iterator support (`begin`, `end`, `cbegin`, `cend`)
- richer `std::string_view` interoperability
- additional search algorithms
- configurable allocator support
- dedicated benchmark suite
- fuzz testing for boundary-heavy operations

These can be added without changing the project's core educational focus.

---

## 📚 Documentation

- [Engineering Case Study](docs/ENGINEERING_CASE_STUDY.md)
- [Public API](include/MyString.h)
- [Implementation](src/MyString.cpp)
- [Example](examples/main.cpp)
- [Tests](tests/test_mystring.cpp)
- [Build Configuration](CMakeLists.txt)

---

## 📄 License

MIT — see [`LICENSE`](LICENSE).

## 👨‍💻 Author

**Jyatin Kumar Singh**  
C++ / Full-Stack Developer · Open Source Contributor

[GitHub](https://github.com/Jyatin)
