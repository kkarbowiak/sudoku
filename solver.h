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
        auto solve(Board board, unsigned int x, unsigned int y);

    private:
        std::vector<Board> m_solutions;
};

template<class Board>
inline auto Solver<Board>::solve(Board board)
{
    solve(board, 0u, 0u);
}

template<class Board>
inline auto Solver<Board>::get_solutions() const
{
    return m_solutions;
}

template<class Board>
inline auto Solver<Board>::solve(Board board, unsigned int x, unsigned int y)
{
    if (board.is_solved())
    {
        m_solutions.push_back(board);
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
                        copy.fix_option(x, y, v);
                        if (copy.is_valid())
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
