#include "solver.h"
#include "board_reader.h"

#include "doctest.h"


TEST_CASE("Solver identifies a solved board and returns it as a solution")
{
    BoardReader const board_reader;
    auto board = board_reader.read_board({
        "534678912",
        "672195348",
        "198342567",
        "859761423",
        "426853791",
        "713924856",
        "961537284",
        "287419635",
        "345286179"});
    Solver solver;
    solver.solve(board);

    auto solutions = solver.get_solutions();

    REQUIRE(solutions.size() == 1u);
    REQUIRE(solutions.front() == Solution{{{
        {{5u, 3u, 4u, 6u, 7u, 8u, 9u, 1u, 2u}},
        {{6u, 7u, 2u, 1u, 9u, 5u, 3u, 4u, 8u}},
        {{1u, 9u, 8u, 3u, 4u, 2u, 5u, 6u, 7u}},
        {{8u, 5u, 9u, 7u, 6u, 1u, 4u, 2u, 3u}},
        {{4u, 2u, 6u, 8u, 5u, 3u, 7u, 9u, 1u}},
        {{7u, 1u, 3u, 9u, 2u, 4u, 8u, 5u, 6u}},
        {{9u, 6u, 1u, 5u, 3u, 7u, 2u, 8u, 4u}},
        {{2u, 8u, 7u, 4u, 1u, 9u, 6u, 3u, 5u}},
        {{3u, 4u, 5u, 2u, 8u, 6u, 1u, 7u, 9u}}}}});
}

TEST_CASE("Solver finds and returns a single solution")
{
    BoardReader const board_reader;
    auto board = board_reader.read_board({
        "530070000",
        "600195000",
        "098000060",
        "800060003",
        "400803001",
        "700020006",
        "060000280",
        "000419005",
        "000080079"});
    Solver solver;
    solver.solve(board);

    auto solutions = solver.get_solutions();

    REQUIRE(solutions.size() == 1u);
    REQUIRE(solutions.front() == Solution{{{
        {{5u, 3u, 4u, 6u, 7u, 8u, 9u, 1u, 2u}},
        {{6u, 7u, 2u, 1u, 9u, 5u, 3u, 4u, 8u}},
        {{1u, 9u, 8u, 3u, 4u, 2u, 5u, 6u, 7u}},
        {{8u, 5u, 9u, 7u, 6u, 1u, 4u, 2u, 3u}},
        {{4u, 2u, 6u, 8u, 5u, 3u, 7u, 9u, 1u}},
        {{7u, 1u, 3u, 9u, 2u, 4u, 8u, 5u, 6u}},
        {{9u, 6u, 1u, 5u, 3u, 7u, 2u, 8u, 4u}},
        {{2u, 8u, 7u, 4u, 1u, 9u, 6u, 3u, 5u}},
        {{3u, 4u, 5u, 2u, 8u, 6u, 1u, 7u, 9u}}}}});
}
