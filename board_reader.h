// Copyright 2022 Krzysztof Karbowiak

#pragma once

#include "board.h"

#include <string>
#include <vector>
#include <algorithm>
#include <cctype>
#include <cassert>


class BoardReader
{
    public:
        auto read_board(std::vector<std::string> const & values) const;
};

inline auto BoardReader::read_board(std::vector<std::string> const & values) const
{
    assert(values.size() <= Board::height());
    assert(std::all_of(values.begin(), values.end(), [](auto const & row) { return row.size() <= Board::width(); }));
    assert(std::all_of(values.begin(), values.end(), [](auto const & row) { return std::all_of(row.begin(), row.end(), [](unsigned char c) { return std::isdigit(c); }); }));

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
