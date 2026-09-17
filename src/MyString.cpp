#include "MyString.h"

#include <algorithm>
#include <cctype>
#include <istream>
#include <ostream>
#include <stdexcept>
#include <utility>

std::size_t MyString::text_length(const char* text) noexcept {
    if (text == nullptr) {
        return 0;
    }
    std::size_t length = 0;
    while (text[length] != '\0') {
        ++length;
    }
    return length;
}

void MyString::copy_n(char* destination, const char* source, std::size_t count) noexcept {
    for (std::size_t i = 0; i < count; ++i) {
        destination[i] = source[i];
    }
}

MyString::MyString() : data_(new char[1]{'\0'}), size_(0), capacity_(0) {}

MyString::MyString(const char* text) : MyString(std::string_view(text == nullptr ? "" : text)) {}

MyString::MyString(std::string_view text)
    : data_(new char[text.size() + 1]), size_(text.size()), capacity_(text.size()) {
    copy_n(data_, text.data(), size_);
    data_[size_] = '\0';
}

MyString::MyString(const MyString& other)
    : data_(new char[other.size_ + 1]), size_(other.size_), capacity_(other.size_) {
    copy_n(data_, other.data_, size_);
    data_[size_] = '\0';
}

MyString::MyString(MyString&& other) noexcept
    : data_(other.data_), size_(other.size_), capacity_(other.capacity_) {
    other.data_ = new char[1]{'\0'};
    other.size_ = 0;
    other.capacity_ = 0;
}

MyString::~MyString() {
    delete[] data_;
}

MyString& MyString::operator=(const MyString& other) {
    if (this == &other) {
        return *this;
    }
    MyString copy(other);
    swap(copy);
    return *this;
}

MyString& MyString::operator=(MyString&& other) noexcept {
    if (this == &other) {
        return *this;
    }
    delete[] data_;
    data_ = other.data_;
    size_ = other.size_;
    capacity_ = other.capacity_;
    other.data_ = new char[1]{'\0'};
    other.size_ = 0;
    other.capacity_ = 0;
    return *this;
}

std::size_t MyString::size() const noexcept { return size_; }
std::size_t MyString::length() const noexcept { return size_; }
std::size_t MyString::capacity() const noexcept { return capacity_; }
bool MyString::empty() const noexcept { return size_ == 0; }
const char* MyString::c_str() const noexcept { return data_; }
char* MyString::data() noexcept { return data_; }
const char* MyString::data() const noexcept { return data_; }

char& MyString::operator[](std::size_t index) noexcept { return data_[index]; }
const char& MyString::operator[](std::size_t index) const noexcept { return data_[index]; }

char& MyString::at(std::size_t index) {
    if (index >= size_) throw std::out_of_range("MyString::at: index out of range");
    return data_[index];
}

const char& MyString::at(std::size_t index) const {
    if (index >= size_) throw std::out_of_range("MyString::at: index out of range");
    return data_[index];
}

char& MyString::front() {
    if (empty()) throw std::out_of_range("MyString::front: empty string");
    return data_[0];
}

const char& MyString::front() const {
    if (empty()) throw std::out_of_range("MyString::front: empty string");
    return data_[0];
}

char& MyString::back() {
    if (empty()) throw std::out_of_range("MyString::back: empty string");
    return data_[size_ - 1];
}

const char& MyString::back() const {
    if (empty()) throw std::out_of_range("MyString::back: empty string");
    return data_[size_ - 1];
}

void MyString::clear() noexcept {
    size_ = 0;
    data_[0] = '\0';
}

void MyString::ensure_capacity(std::size_t required) {
    if (required <= capacity_) return;
    std::size_t new_capacity = std::max(required, capacity_ == 0 ? std::size_t{1} : capacity_ * 2);
    char* replacement = new char[new_capacity + 1];
    copy_n(replacement, data_, size_);
    replacement[size_] = '\0';
    delete[] data_;
    data_ = replacement;
    capacity_ = new_capacity;
}

void MyString::reserve(std::size_t new_capacity) {
    if (new_capacity <= capacity_) return;
    char* replacement = new char[new_capacity + 1];
    copy_n(replacement, data_, size_);
    replacement[size_] = '\0';
    delete[] data_;
    data_ = replacement;
    capacity_ = new_capacity;
}

void MyString::swap(MyString& other) noexcept {
    using std::swap;
    swap(data_, other.data_);
    swap(size_, other.size_);
    swap(capacity_, other.capacity_);
}

MyString& MyString::append(const MyString& other) {
    if (this == &other) {
        MyString copy(other);
        return append(copy);
    }
    ensure_capacity(size_ + other.size_);
    copy_n(data_ + size_, other.data_, other.size_);
    size_ += other.size_;
    data_[size_] = '\0';
    return *this;
}

MyString& MyString::append(const char* text) {
    if (text == nullptr) return *this;
    const std::size_t count = text_length(text);
    if (count == 0) return *this;
    if (text >= data_ && text <= data_ + size_) {
        MyString copy(text);
        return append(copy);
    }
    ensure_capacity(size_ + count);
    copy_n(data_ + size_, text, count);
    size_ += count;
    data_[size_] = '\0';
    return *this;
}

MyString& MyString::append(char ch) {
    ensure_capacity(size_ + 1);
    data_[size_++] = ch;
    data_[size_] = '\0';
    return *this;
}

MyString& MyString::operator+=(const MyString& other) { return append(other); }
MyString& MyString::operator+=(const char* text) { return append(text); }
MyString& MyString::operator+=(char ch) { return append(ch); }

std::size_t MyString::find(char ch, std::size_t pos) const noexcept {
    for (std::size_t i = pos; i < size_; ++i) {
        if (data_[i] == ch) return i;
    }
    return npos;
}

std::size_t MyString::find(const MyString& needle, std::size_t pos) const noexcept {
    if (needle.empty()) return pos <= size_ ? pos : npos;
    if (needle.size_ > size_ || pos > size_ - needle.size_) return npos;
    for (std::size_t i = pos; i <= size_ - needle.size_; ++i) {
        std::size_t j = 0;
        while (j < needle.size_ && data_[i + j] == needle.data_[j]) ++j;
        if (j == needle.size_) return i;
    }
    return npos;
}

bool MyString::contains(const MyString& needle) const noexcept { return find(needle) != npos; }

bool MyString::starts_with(const MyString& prefix) const noexcept {
    if (prefix.size_ > size_) return false;
    for (std::size_t i = 0; i < prefix.size_; ++i) if (data_[i] != prefix.data_[i]) return false;
    return true;
}

bool MyString::ends_with(const MyString& suffix) const noexcept {
    if (suffix.size_ > size_) return false;
    const std::size_t offset = size_ - suffix.size_;
    for (std::size_t i = 0; i < suffix.size_; ++i) if (data_[offset + i] != suffix.data_[i]) return false;
    return true;
}

MyString MyString::substr(std::size_t pos, std::size_t count) const {
    if (pos > size_) throw std::out_of_range("MyString::substr: position out of range");
    const std::size_t actual = std::min(count, size_ - pos);
    return MyString(std::string_view(data_ + pos, actual));
}

MyString MyString::reversed() const {
    MyString result(*this);
    for (std::size_t left = 0, right = size_ == 0 ? 0 : size_ - 1; left < right; ++left, --right) {
        std::swap(result.data_[left], result.data_[right]);
    }
    return result;
}

int MyString::compare(const MyString& other) const noexcept {
    const std::size_t common = std::min(size_, other.size_);
    for (std::size_t i = 0; i < common; ++i) {
        if (data_[i] < other.data_[i]) return -1;
        if (data_[i] > other.data_[i]) return 1;
    }
    if (size_ < other.size_) return -1;
    if (size_ > other.size_) return 1;
    return 0;
}

MyString operator+(const MyString& lhs, const MyString& rhs) {
    MyString result;
    result.reserve(lhs.size_ + rhs.size_);
    result.append(lhs);
    result.append(rhs);
    return result;
}

bool operator==(const MyString& lhs, const MyString& rhs) noexcept { return lhs.compare(rhs) == 0; }
bool operator!=(const MyString& lhs, const MyString& rhs) noexcept { return !(lhs == rhs); }
bool operator<(const MyString& lhs, const MyString& rhs) noexcept { return lhs.compare(rhs) < 0; }
bool operator<=(const MyString& lhs, const MyString& rhs) noexcept { return lhs.compare(rhs) <= 0; }
bool operator>(const MyString& lhs, const MyString& rhs) noexcept { return lhs.compare(rhs) > 0; }
bool operator>=(const MyString& lhs, const MyString& rhs) noexcept { return lhs.compare(rhs) >= 0; }

std::ostream& operator<<(std::ostream& out, const MyString& value) {
    return out.write(value.data_, static_cast<std::streamsize>(value.size_));
}

std::istream& operator>>(std::istream& in, MyString& value) {
    value.clear();
    in >> std::ws;
    while (in.good()) {
        const int next = in.peek();
        if (next == std::char_traits<char>::eof() || std::isspace(static_cast<unsigned char>(next))) break;
        value.append(static_cast<char>(in.get()));
    }
    return in;
}
