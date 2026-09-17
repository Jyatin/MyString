#include <iostream>
#include <utility>

#include "MyString.h"

int main() {
    MyString language("Modern C++17");
    MyString project("MyString");

    std::cout << "=== MyString demo ===\n";
    std::cout << "language : " << language << '\n';
    std::cout << "project  : " << project << '\n';

    MyString combined = language + " - " + project;
    std::cout << "combined : " << combined << '\n';
    std::cout << "size     : " << combined.size() << '\n';
    std::cout << "capacity : " << combined.capacity() << '\n';

    combined += " library";
    std::cout << "append   : " << combined << '\n';
    std::cout << "find     : " << combined.find(MyString("String")) << '\n';
    std::cout << "contains : " << std::boolalpha << combined.contains(MyString("C++")) << '\n';
    std::cout << "prefix   : " << combined.starts_with(MyString("Modern")) << '\n';
    std::cout << "suffix   : " << combined.ends_with(MyString("library")) << '\n';
    std::cout << "substr   : " << combined.substr(7, 5) << '\n';
    std::cout << "reverse  : " << combined.reversed() << '\n';

    MyString copied(combined);
    copied[0] = 'm';
    std::cout << "copy     : " << copied << '\n';
    std::cout << "original : " << combined << '\n';

    MyString moved(std::move(copied));
    std::cout << "moved    : " << moved << '\n';
    std::cout << "moved-from size: " << copied.size() << '\n';

    MyString cleared = combined;
    cleared.clear();
    std::cout << "cleared  : \"" << cleared << "\" (empty=" << cleared.empty() << ")\n";

    std::cout << "=== demo complete ===\n";
    return 0;
}
