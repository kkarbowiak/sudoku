// Copyright 2022 Krzysztof Karbowiak

#include "board.h"
#include "solver.h"

#include <iostream>


BoardMini read_board(std::string input)
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

int main(int argc, char * argv[])
{
    auto board = argc > 1 ? read_board(argv[1]) : BoardMini();

    auto solver = Solver();
    solver.solve(board);

    std::cout << "Number of solutions: " << solver.get_solutions().size() << '\n';
}
