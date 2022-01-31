#pragma once

#include "board.h"

#include <vector>


class Solver
{
    public:
        auto solve(Board board);

        auto get_solutions() const;

    private:
        std::vector<Board> m_solutions;
};

inline auto Solver::solve(Board board)
{
    if (board.is_solved())
    {
        m_solutions.push_back(board);
        return;
    }

    for (auto y = 0; y < 3; ++y)
    {
        for (auto x = 0; x < 3; ++x)
        {
            if (!board.is_fixed_at(x, y))
            {
                for (auto v = 1; v <= 9; ++v)
                {
                    if (board.has_option(x, y, v))
                    {
                        auto copy = board;
                        copy.fix_option(x, y, v);
                        if (copy.is_valid())
                        {
                            solve(copy);
                        }
                    }
                }
                return;
            }
        }
    }
}

inline auto Solver::get_solutions() const
{
    return m_solutions;
}
