# Custom MyString Class in C++

A custom implementation of the `String` class in C++ built completely from scratch without using the Standard Template Library (`std::string`). This project demonstrates fundamental Object-Oriented Programming concepts, dynamic memory management, deep copying, and operator overloading.

The primary objective of this project is to understand how a string class is implemented internally and to gain hands-on experience with manual memory management in C++.

---

## Project Overview

The `MyString` class is a user-defined string implementation that provides commonly used string operations while managing memory dynamically.

Unlike `std::string`, this implementation explicitly handles memory allocation and deallocation using `new` and `delete`, helping in understanding how C++ manages objects internally.

---

## Features

- Dynamic Memory Allocation
- Default Constructor
- Parameterized Constructor
- Copy Constructor
- Destructor
- Copy Assignment Operator
- Deep Copy Implementation
- String Length Calculation
- Character Access
- String Comparison
- Copying Strings
- Operator Overloading
- Memory Safety

---

## Concepts Demonstrated

This project covers several important C++ concepts:

### Object-Oriented Programming
- Classes and Objects
- Data Encapsulation
- Member Functions

### Memory Management
- Dynamic allocation using `new`
- Memory deallocation using `delete`
- Preventing memory leaks

### Rule of Three
Implementation of:
- Destructor
- Copy Constructor
- Copy Assignment Operator

### Operator Overloading

The project demonstrates custom implementations of operators such as:

- Assignment (`=`)
- Equality (`==`)
- Inequality (`!=`)
- Index Operator (`[]`)

---

## Project Structure

```
Custom-MyString-CPP/
│
├── Main.cpp          # Driver program
├── MyString.cpp      # Function definitions
└── MyString.h        # Class declaration
```

---

## How It Works

The `MyString` class internally maintains a dynamically allocated character array.

Whenever a string object is created:

1. Memory is allocated dynamically.
2. Characters are copied into the allocated memory.
3. Memory ownership belongs exclusively to the object.
4. Deep copies are performed whenever copying occurs.
5. Memory is automatically released by the destructor.

This prevents problems such as:

- Memory leaks
- Double deletion
- Dangling pointers
- Shallow copying

---

## Compilation

Compile using **g++**

```bash
g++ Main.cpp MyString.cpp -o MyString
```

---

## Running

### Windows

```bash
MyString.exe
```

### Linux/macOS

```bash
./MyString
```

---

## Skills Demonstrated

This project demonstrates practical knowledge of:

- C++
- Object-Oriented Programming
- Dynamic Memory Allocation
- Pointer Manipulation
- Operator Overloading
- Rule of Three
- Copy Constructors
- Destructors
- Memory Management
- Modular Programming

---

## Learning Outcomes

By building this project, I gained a deeper understanding of:

- Internal implementation of string classes
- Manual memory management
- Deep copy vs shallow copy
- Importance of constructors and destructors
- Safe object copying
- Writing reusable C++ classes
- Managing resources efficiently

---

## Future Improvements

Possible future enhancements include:

- Move Constructor
- Move Assignment Operator
- Rule of Five implementation
- String Concatenation (`+`)
- Append Function
- Insert Function
- Erase Function
- Substring Extraction
- Find Function
- Reverse Function
- Case Conversion
- Iterator Support
- STL Compatibility

---

## Technologies Used

- C++
- Visual Studio Code
- Git
- GitHub

---

## Repository

```
Main.cpp
MyString.cpp
MyString.h
```

---

## Author

**Jyatin Singh**

B.Tech Computer Science Engineering

Lovely Professional University

GitHub: https://github.com/Jyatin

---

## License

This project is developed for educational purposes to demonstrate the implementation of a custom string class in C++.