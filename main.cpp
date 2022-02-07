// Copyright 2022 Krzysztof Karbowiak

#include "board.h"
#include "board_reader.h"
#include "solver.h"
#include "stopwatch.h"

#include <string>
#include <vector>
#include <chrono>
#include <iostream>


auto read_board(std::vector<std::string> const & input)
{
    BoardReader const board_reader;
    return board_reader.read_board(input);
}

int main(int argc, char * argv[])
{
    Stopwatch stopwatch;

    auto board = argc > 1 ? read_board(std::vector<std::string>(&argv[1], &argv[argc])) : Board();
    auto solver = Solver();

    stopwatch.start();
    solver.solve(board);
    stopwatch.stop();

    std::cout << "Number of solutions: " << solver.get_solutions().size() << '\n';
    std::cout << "Took: " << stopwatch.get_seconds() << " seconds.\n";
}
