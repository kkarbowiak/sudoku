#include "Board.h"
#include "Solver.h"

#include <iostream>


Board read_board(std::string input)
{
    Board board;

    int pos = 0;
    for (auto v : input)
    {
        if (v != '0')
        {
            board.fix_option(pos % 3, pos / 3, v - '0');
        }
        ++pos;
    }

    return board;
}

int main(int argc, char * argv[])
{
    auto board = argc > 1 ? read_board(argv[1]) : Board();

    auto solver = Solver();
    solver.solve(board);

    std::cout << "Number of solutions: " << solver.get_solutions().size() << '\n';
}
