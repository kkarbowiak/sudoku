// Copyright 2022 Krzysztof Karbowiak

#pragma once

#include <vector>


template<class Board>
class Solver
{
    public:
        auto solve(Board board);

        auto get_solutions() const;

    private:
        std::vector<Board> m_solutions;
};

template<class Board>
inline auto Solver<Board>::solve(Board board)
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

template<class Board>
inline auto Solver<Board>::get_solutions() const
{
    return m_solutions;
}
