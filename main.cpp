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

auto print_solution(Solution const & solution)
{
    for (auto y = 0u; y < Solution::height; ++y)
    {
        if (y == 3 || y == 6)
        {
            std::cout << '\n';
        }
        for (auto x = 0u; x < Solution::width; ++x)
        {
            if (x == 3 || x == 6)
            {
                std::cout << ' ';
            }
            std::cout << solution.values[y][x];
        }
        std::cout << '\n';
    }
    std::cout << "\n\n";
}

auto print_results(std::vector<Solution> const & solutions, double time_s)
{
    std::cout << "Number of solutions: " << solutions.size() << '\n';
    std::cout << "Took: " << time_s << " seconds.\n\n";
    for (auto const & solution : solutions)
    {
        print_solution(solution);
    }
}

int main(int argc, char * argv[])
{
    Stopwatch stopwatch;

    auto board = argc > 1 ? read_board(std::vector<std::string>(&argv[1], &argv[argc])) : Board();
    auto solver = Solver();

    stopwatch.start();
    solver.solve(board);
    stopwatch.stop();

    auto const & solutions = solver.get_solutions();

    print_results(solutions, stopwatch.get_seconds());
}
