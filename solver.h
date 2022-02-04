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
        auto solve(Board board, int x, int y);

    private:
        std::vector<Board> m_solutions;
};

template<class Board>
inline auto Solver<Board>::solve(Board board)
{
    solve(board, 0, 0);
}

template<class Board>
inline auto Solver<Board>::get_solutions() const
{
    return m_solutions;
}

template<class Board>
inline auto Solver<Board>::solve(Board board, int x, int y)
{
    if (board.is_solved())
    {
        m_solutions.push_back(board);
        return;
    }

    for (auto yy = y; yy < Board::height(); ++yy)
    {
        for (auto xx = x; xx < Board::width(); ++xx)
        {
            if (!board.is_fixed_at(xx, yy))
            {
                for (auto v : Board::options())
                {
                    if (board.has_option(xx, yy, v))
                    {
                        auto copy = board;
                        copy.fix_option(xx, yy, v);
                        if (copy.is_valid())
                        {
                            solve(copy, xx, yy);
                        }
                    }
                }
                return;
            }
        }
        x = 0;
    }
}
