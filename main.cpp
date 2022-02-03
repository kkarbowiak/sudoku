// Copyright 2022 Krzysztof Karbowiak

#include "board_mini.h"
#include "board.h"
#include "solver.h"

#include <string>
#include <vector>
#include <chrono>
#include <iostream>


BoardMini read_board_mini(std::string input)
{
    BoardMini board;

    auto pos = 0;
    for (auto v : input)
    {
        if (v != '0')
        {
            board.fix_option(pos % board.width(), pos / board.width(), v - '0');
        }
        ++pos;
    }

    return board;
}

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
    if (argc > 1)
    {
        if (argv[1] == std::string("3x3"))
        {
            auto board = argc > 2 ? read_board_mini(argv[2]) : BoardMini();

            auto solver = Solver<BoardMini>();
            auto const begin = std::chrono::steady_clock::now();
            solver.solve(board);
            auto const end = std::chrono::steady_clock::now();
            std::chrono::duration<double> const diff = end - begin;

            std::cout << "Number of solutions: " << solver.get_solutions().size() << '\n';
            std::cout << "Took: " << diff.count() << " seconds.\n";
        }
        else
        {
            auto board = argc > 2 ? read_board(std::vector<std::string>(&argv[2], &argv[argc])) : Board();
            auto solver = Solver<Board>();

            auto const begin = std::chrono::steady_clock::now();
            solver.solve(board);
            auto const end = std::chrono::steady_clock::now();
            std::chrono::duration<double> const diff = end - begin;

            std::cout << "Number of solutions: " << solver.get_solutions().size() << '\n';
            std::cout << "Took: " << diff.count() << " seconds.\n";
        }
    }
    
}
