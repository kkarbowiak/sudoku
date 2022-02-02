// Copyright 2022 Krzysztof Karbowiak

#pragma once

#include "board_mini.h"

#include <vector>


class Solver
{
    public:
        auto solve(BoardMini board);

        auto get_solutions() const;

    private:
        std::vector<BoardMini> m_solutions;
};

inline auto Solver::solve(BoardMini board)
{
    if (board.is_solved())
    {
        m_solutions.push_back(board);
        return;
    }

    for (auto y = 0; y < board.height(); ++y)
    {
        for (auto x = 0; x < board.width(); ++x)
        {
            if (!board.is_fixed_at(x, y))
            {
                for (auto v : board.options())
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
