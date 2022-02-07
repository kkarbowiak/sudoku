// Copyright 2022 Krzysztof Karbowiak

#pragma once

#include "board.h"

#include <string>
#include <vector>


class BoardReader
{
    public:
        auto read_board(std::vector<std::string> const & values) const;
};

inline auto BoardReader::read_board(std::vector<std::string> const & values) const
{
    Board board;

    auto y = 0u;
    for (auto const & row : values)
    {
        auto x = 0u;
        for (auto const & value : row)
        {
            if (value != '0')
            {
                board.fix_option(x, y, value - '0');
            }
            ++x;
        }
        ++y;
    }

    return board;
}
