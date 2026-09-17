# MyString — Engineering Case Study

## 1. Project Background

`MyString` is a small `std::string`-style class implemented from scratch in modern C++17. The project is intentionally focused on understanding the systems-level mechanisms normally hidden behind a production string implementation.

The implementation does not use `std::string` as its internal storage. Each object owns a dynamically allocated, null-terminated character buffer and is responsible for its lifetime.

## 2. Engineering Problem

A string abstraction looks simple at the API level, but it combines several non-trivial concerns:

- dynamic memory ownership
- object lifetime
- deep copying
- move semantics
- safe reallocation
- exception safety
- capacity management
- bounds checking
- operator overloading
- API and invariant design

The goal of this project was to make those concerns explicit and implement them in a small, testable library.

## 3. Major Engineering Challenges

### 3.1 Resource Ownership

Every `MyString` owns its character buffer. The implementation maintains the invariant that the allocation is large enough for the current characters plus the terminating null byte.

Core invariants:

1. `size_ <= capacity_`.
2. `data_[size_]` is the null terminator.
3. The allocated buffer provides at least `capacity_ + 1` characters.

This makes ownership explicit and provides a clear contract for every mutating operation.

### 3.2 Rule of Five

Because the class manages a raw resource, the special member functions are implemented deliberately:

- destructor
- copy constructor
- copy assignment operator
- move constructor
- move assignment operator

Copy operations create independent storage. Move operations transfer ownership instead of copying every character, leaving the source in a valid empty state.

### 3.3 Capacity Growth

Appending one character at a time can become expensive if the buffer is reallocated for every append. `MyString` therefore separates logical `size` from allocated `capacity` and grows capacity geometrically.

This gives repeated append operations amortized constant-time growth behavior, while individual reallocations remain linear in the amount of data copied.

### 3.4 Exception Safety

Copy assignment uses copy-and-swap. The replacement object is prepared before the current resource is exchanged, so an allocation/copy failure does not partially destroy the existing object.

### 3.5 API Safety

The class provides both low-level and checked access:

- `operator[]` for unchecked indexed access
- `at()` for bounds-checked access
- `front()` and `back()` for endpoint access
- `c_str()` for C-compatible read access

Searching, substring extraction, concatenation, prefix/suffix checks, and comparisons are exposed through a compact interface.

## 4. Functionality Implemented

| Area | Functionality |
|---|---|
| Ownership | Dynamic heap-backed character storage |
| Lifetime | Destructor + Rule of Five |
| Construction | C strings, characters, `std::string_view` |
| Capacity | `size`, `length`, `capacity`, `reserve`, `clear` |
| Access | `[]`, `at`, `front`, `back`, `data`, `c_str` |
| Mutation | `append`, `push_back`, `+=`, `resize` |
| Algorithms | `find`, `contains`, `substr`, `reversed` |
| Predicates | `starts_with`, `ends_with`, `empty` |
| Operators | `+`, `==`, `!=`, `<`, `<=`, `>`, `>=`, stream I/O |
| Testing | Assertion-based unit tests |
| Build | CMake + GCC/Clang-compatible workflow |
| CI | GitHub Actions + sanitizers |

## 5. Demonstration Flow

The example program intentionally exercises the class as a user would:

```text
construct
   ↓
concatenate
   ↓
append
   ↓
search / inspect
   ↓
substring / reverse
   ↓
deep copy
   ↓
move ownership
   ↓
reuse / clear
```

The demo also verifies an important ownership property: modifying a copied object does not modify the original object.

## 6. Complexity Considerations

| Operation | Expected complexity |
|---|---:|
| `size()` / `length()` | O(1) |
| `capacity()` | O(1) |
| `operator[]` / `at()` | O(1) |
| `push_back()` | Amortized O(1) |
| `append()` | O(n) |
| `reserve()` | O(n) when reallocation occurs |
| `find()` | O(n·m) worst case |
| `substr()` | O(k) |
| `reversed()` | O(n) |
| comparison | O(min(n, m)) |

Here `n` and `m` represent the relevant input lengths, and `k` is the length of the produced substring.

## 7. Testing Strategy

The test suite covers both normal functionality and ownership-sensitive edge cases:

- construction and empty strings
- character and indexed access
- bounds errors from `at()`
- copy construction
- copy assignment
- move construction
- move assignment
- moved-from object reuse
- self-assignment
- self-append
- capacity behavior after `clear()`
- searching and substring boundaries
- comparisons
- stream input/output
- embedded null bytes

The repository also includes GitHub Actions CI that builds the project, runs the tests, and runs sanitizer-backed tests on Ubuntu.

## 8. Why This Project Matters

The value of `MyString` is not replacing `std::string`. In application code, the standard library should normally be preferred because it is mature, optimized, and extensively tested.

The value of this implementation is educational and systems-oriented: it exposes how a high-level abstraction depends on resource ownership, memory allocation, object lifetime, copying, moving, invariants, and complexity decisions.

## 9. Key Takeaways

Building this project strengthened understanding of:

- RAII and deterministic resource management
- shallow vs. deep copy
- move semantics and ownership transfer
- Rule of Five
- copy-and-swap exception safety
- dynamic arrays and geometric growth
- API contracts and class invariants
- operator overloading
- algorithmic complexity
- automated testing and CI

## 10. Future Improvements

Potential extensions include:

- iterator support (`begin`, `end`, `cbegin`, `cend`)
- heterogeneous lookup with `std::string_view`
- additional search algorithms
- configurable allocator support
- benchmark suite against representative `std::string` operations
- fuzz testing for parser and boundary cases

These are deliberately separated from the current core so the implementation remains small enough to study.
