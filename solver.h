// Copyright 2022 Krzysztof Karbowiak

#pragma once

#include "board.h"
#include "solution.h"

#include <vector>


class Solver
{
    public:
        auto solve(Board board);

        auto get_solutions() const;

    private:
        auto solve(Board board, unsigned int x, unsigned int y) -> void;

    private:
        std::vector<Solution> m_solutions;
};

inline auto Solver::solve(Board board)
{
    solve(board, 0u, 0u);
}

inline auto Solver::get_solutions() const
{
    return m_solutions;
}

inline auto Solver::solve(Board board, unsigned int x, unsigned int y) -> void
{
    if (board.is_solved())
    {
        m_solutions.push_back(board.get_solution());
        return;
    }

    while(y < Board::height())
    {
        while(x < Board::width())
        {
            if (!board.is_fixed_at(x, y))
            {
                for (auto v : Board::options())
                {
                    if (board.has_option(x, y, v))
                    {
                        auto copy = board;
                        if (copy.fix_option(x, y, v))
                        {
                            solve(copy, x, y);
                        }
                    }
                }
                return;
            }
            ++x;
        }
        x = 0u;
        ++y;
    }
}
