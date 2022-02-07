// Copyright 2022 Krzysztof Karbowiak

#include "board.h"
#include "solver.h"
#include "stopwatch.h"

#include <string>
#include <vector>
#include <chrono>
#include <iostream>


Board read_board(std::vector<std::string> input)
{
    Board board;

    auto y = 0;
    for (auto values : input)
    {
        auto x = 0;
        for (auto v : values)
        {
            if (v != '0')
            {
                board.fix_option(x, y, v - '0');
            }
            ++x;
        }
        ++y;
    }

    return board;
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
