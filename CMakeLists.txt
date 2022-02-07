cmake_minimum_required(VERSION 3.15)

project("sudoku")

add_executable(sudoku)
target_sources(sudoku PRIVATE main.cpp)
target_compile_features(sudoku PRIVATE cxx_std_17)
target_compile_options(sudoku PRIVATE
    $<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:GNU>>: -Wall -Wextra -Werror -pedantic-errors>
    $<$<CXX_COMPILER_ID:MSVC>: /W4 /WX>)

enable_testing()
add_subdirectory(test/unittest)
