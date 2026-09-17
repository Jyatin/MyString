#ifndef MYSTRING_H
#define MYSTRING_H

#include <cstddef>
#include <iosfwd>
#include <string_view>

class MyString {
public:
    static constexpr std::size_t npos = static_cast<std::size_t>(-1);

    MyString();
    explicit MyString(const char* text);
    explicit MyString(std::string_view text);
    MyString(const MyString& other);
    MyString(MyString&& other) noexcept;
    ~MyString();

    MyString& operator=(const MyString& other);
    MyString& operator=(MyString&& other) noexcept;

    std::size_t size() const noexcept;
    std::size_t length() const noexcept;
    std::size_t capacity() const noexcept;
    bool empty() const noexcept;
    const char* c_str() const noexcept;
    char* data() noexcept;
    const char* data() const noexcept;

    char& operator[](std::size_t index) noexcept;
    const char& operator[](std::size_t index) const noexcept;
    char& at(std::size_t index);
    const char& at(std::size_t index) const;
    char& front();
    const char& front() const;
    char& back();
    const char& back() const;

    void clear() noexcept;
    void reserve(std::size_t new_capacity);
    void swap(MyString& other) noexcept;

    MyString& append(const MyString& other);
    MyString& append(const char* text);
    MyString& append(char ch);
    MyString& operator+=(const MyString& other);
    MyString& operator+=(const char* text);
    MyString& operator+=(char ch);

    std::size_t find(char ch, std::size_t pos = 0) const noexcept;
    std::size_t find(const MyString& needle, std::size_t pos = 0) const noexcept;
    bool contains(const MyString& needle) const noexcept;
    bool starts_with(const MyString& prefix) const noexcept;
    bool ends_with(const MyString& suffix) const noexcept;
    MyString substr(std::size_t pos, std::size_t count = npos) const;
    MyString reversed() const;

    int compare(const MyString& other) const noexcept;

    friend MyString operator+(const MyString& lhs, const MyString& rhs);
    friend bool operator==(const MyString& lhs, const MyString& rhs) noexcept;
    friend bool operator!=(const MyString& lhs, const MyString& rhs) noexcept;
    friend bool operator<(const MyString& lhs, const MyString& rhs) noexcept;
    friend bool operator<=(const MyString& lhs, const MyString& rhs) noexcept;
    friend bool operator>(const MyString& lhs, const MyString& rhs) noexcept;
    friend bool operator>=(const MyString& lhs, const MyString& rhs) noexcept;
    friend std::ostream& operator<<(std::ostream& out, const MyString& value);
    friend std::istream& operator>>(std::istream& in, MyString& value);

private:
    char* data_;
    std::size_t size_;
    std::size_t capacity_;

    static std::size_t text_length(const char* text) noexcept;
    static void copy_n(char* destination, const char* source, std::size_t count) noexcept;
    void ensure_capacity(std::size_t required);
};

#endif
