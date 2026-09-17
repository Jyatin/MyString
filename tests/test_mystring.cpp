#include <cassert>
#include <sstream>
#include <stdexcept>
#include <string_view>
#include <utility>

#include "MyString.h"

static void test_construction_and_access() {
    MyString empty;
    assert(empty.empty());
    assert(empty.size() == 0);
    assert(empty.c_str()[0] == '\0');

    MyString value("hello");
    assert(value.size() == 5);
    assert(value.length() == 5);
    assert(value.front() == 'h');
    assert(value.back() == 'o');
    value[0] = 'H';
    assert(value == MyString("Hello"));
    assert(value.at(1) == 'e');

    bool threw = false;
    try { (void)value.at(99); } catch (const std::out_of_range&) { threw = true; }
    assert(threw);
}

static void test_rule_of_five() {
    MyString original("resource");
    MyString copied(original);
    copied[0] = 'R';
    assert(original == MyString("resource"));
    assert(copied == MyString("Resource"));

    MyString assigned;
    assigned = original;
    assert(assigned == original);

    MyString moved(std::move(copied));
    assert(moved == MyString("Resource"));
    assert(copied.empty());
    assert(copied.c_str()[0] == '\0');

    MyString move_assigned;
    move_assigned = std::move(moved);
    assert(move_assigned == MyString("Resource"));
    assert(moved.empty());
}

static void test_modification_and_capacity() {
    MyString value("ab");
    value.reserve(32);
    assert(value.capacity() >= 32);
    value.append('c').append("def");
    assert(value == MyString("abcdef"));
    value += MyString("!");
    assert(value == MyString("abcdef!"));

    value += value;
    assert(value == MyString("abcdef!abcdef!"));

    const std::size_t old_capacity = value.capacity();
    value.clear();
    assert(value.empty());
    assert(value.capacity() == old_capacity);
}

static void test_search_and_substrings() {
    MyString value("banana bread");
    assert(value.find('b') == 0);
    assert(value.find('x') == MyString::npos);
    assert(value.find(MyString("bread")) == 7);
    assert(value.contains(MyString("ana")));
    assert(!value.contains(MyString("cake")));
    assert(value.starts_with(MyString("ban")));
    assert(value.ends_with(MyString("bread")));
    assert(value.substr(7) == MyString("bread"));
    assert(value.substr(0, 6) == MyString("banana"));
    assert(value.reversed() == MyString("daerb ananab"));
}

static void test_comparison_and_streams() {
    assert(MyString("abc") < MyString("abd"));
    assert(MyString("abc") <= MyString("abc"));
    assert(MyString("abd") > MyString("abc"));
    assert(MyString("abc") != MyString("abd"));

    std::stringstream input("hello world");
    MyString first;
    MyString second;
    input >> first >> second;
    assert(first == MyString("hello"));
    assert(second == MyString("world"));

    std::stringstream output;
    output << first << ' ' << second;
    assert(output.str() == "hello world");
}

static void test_embedded_nulls() {
    const char raw[] = {'a', '\0', 'b'};
    MyString value(std::string_view(raw, 3));
    assert(value.size() == 3);
    assert(value[1] == '\0');
    assert(value.substr(1, 2).size() == 2);
}

int main() {
    test_construction_and_access();
    test_rule_of_five();
    test_modification_and_capacity();
    test_search_and_substrings();
    test_comparison_and_streams();
    test_embedded_nulls();
    return 0;
}
