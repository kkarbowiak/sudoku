cmake_minimum_required(VERSION 3.15)

include(CTest)

add_executable(unittest)
target_sources(unittest
    PRIVATE
    main.cpp
    test_options.cpp
    test_board.cpp)

target_include_directories(unittest PRIVATE $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}>)

target_compile_features(unittest PRIVATE cxx_std_17)
target_compile_options(unittest PRIVATE
    $<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:GNU>>: -Wall -Wextra -Werror -pedantic-errors>
    $<$<CXX_COMPILER_ID:MSVC>: /W4 /WX>)

add_test(NAME unittest COMMAND unittest)
add_custom_target(run_unit_test ALL
    COMMAND ${CMAKE_CTEST_COMMAND} -C debug --output-on-failure
    DEPENDS unittest)
