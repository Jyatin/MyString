cmake_minimum_required(VERSION 3.16)

project(MyString VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(mystring src/MyString.cpp)
target_include_directories(mystring PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_compile_options(mystring PRIVATE
    $<$<CXX_COMPILER_ID:GNU,Clang>:-Wall;-Wextra;-Wpedantic>
    $<$<CXX_COMPILER_ID:MSVC>:/W4>
)

add_executable(mystring_demo examples/main.cpp)
target_link_libraries(mystring_demo PRIVATE mystring)

include(CTest)
if(BUILD_TESTING)
    add_executable(mystring_tests tests/test_mystring.cpp)
    target_link_libraries(mystring_tests PRIVATE mystring)
    add_test(NAME MyStringTests COMMAND mystring_tests)
endif()
