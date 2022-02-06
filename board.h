// Copyright 2022 Krzysztof Karbowiak

#pragma once

#include "options.h"

#include <array>
#include <algorithm>
#include <cassert>


class Board
{
    public:
        static constexpr auto width();
        static constexpr auto height();
        static constexpr auto options();

        auto is_fixed() const;
        auto is_valid() const;

        auto has_option(int x, int y, int value) const;
        auto is_fixed_at(int x, int y) const;
        auto fix_option(int x, int y, int value);

        auto is_solved() const;

    private:
        auto is_row_solved(int row) const -> bool;
        auto is_column_solved(int column) const -> bool;
        auto is_square_solved(int square) const -> bool;

        static auto round_coord(int coord) -> int;

    private:
        static constexpr auto m_width = 9;
        static constexpr auto m_height = 9;
        std::array<std::array<Options, m_width>, m_height> m_options;
};

constexpr auto Board::width()
{
    return m_width;
}

constexpr auto Board::height()
{
    return m_height;
}

constexpr auto Board::options()
{
    return Options::options();
}

inline auto Board::is_fixed() const
{
    return std::all_of(
        m_options.begin(),
        m_options.end(),
        [](auto const & row){ return std::all_of(
            row.begin(),
            row.end(),
            [](auto const & option){ return option.is_fixed(); }); });
}

inline auto Board::is_valid() const
{
    return std::all_of(
        m_options.begin(),
        m_options.end(),
        [](auto const & row){ return std::none_of(
            row.begin(),
            row.end(),
            [](auto const & option){ return option.is_empty(); }); });
}

inline auto Board::has_option(int x, int y, int value) const
{
    assert(x < m_width);
    assert(y < m_height);

    return m_options[y][x].has(value);
}

inline auto Board::is_fixed_at(int x, int y) const
{
    assert(x < m_width);
    assert(y < m_height);

    return m_options[y][x].is_fixed();
}

inline auto Board::fix_option(int x, int y, int value)
{
    assert(x < m_width);
    assert(y < m_height);

    m_options[y][x].fix(value);

    for (auto xx = 0; xx < m_width; ++xx)
    {
        if (xx != x)
        {
            m_options[y][xx].remove(value);
        }
    }
    for (auto yy = 0; yy < m_height; ++yy)
    {
        if (yy != y)
        {
            m_options[yy][x].remove(value);
        }
    }

    auto const y_start = round_coord(y);
    auto const x_start = round_coord(x);
    for (auto yy = y_start; yy < y_start + 3; ++yy)
    {
        for (auto xx = x_start; xx < x_start + 3; ++xx)
        {
            if (yy != y || xx != x)
            {
                m_options[yy][xx].remove(value);
            }
        }
    }
}

inline auto Board::is_solved() const
{
    if (!is_fixed())
    {
        return false;
    }

    for (int i = 0; i < 9; ++i)
    {
        if (!is_row_solved(i))
        {
            return false;
        }
        if (!is_column_solved(i))
        {
            return false;
        }
        if (!is_square_solved(i))
        {
            return false;
        }
    }
    return true;
}

auto Board::is_row_solved(int row) const -> bool
{
    for (auto v : Options::options())
    {
        if (std::none_of(m_options[row].begin(), m_options[row].end(), [v](auto option){ return option.has(v); }))
        {
            return false;
        }
    }
    return true;
}

auto Board::is_column_solved(int column) const -> bool
{
    for (auto v : Options::options())
    {
        bool found = false;
        for (int r = 0; r < m_width; ++r)
        {
            if (m_options[column][r].has(v))
            {
                found = true;
                break;
            }
        }
        if (!found)
        {
            return false;
        }
    }
    return true;
}

auto Board::is_square_solved(int square) const -> bool
{
    switch (square)
    {
        case 0:
        {
            for (auto v = 1; v <= 9; ++v)
            {
                bool found = false;
                for (int y = 0; y < 3; ++y)
                {
                    for (int x = 0; x < 3; ++x)
                    {
                        if (m_options[y][x].has(v))
                        {
                            found = true;
                        }
                    }
                }
                if (!found)
                {
                    return false;
                }
            }
            return true;
        }
        case 1:
        {
            for (auto v = 1; v <= 9; ++v)
            {
                bool found = false;
                for (int y = 0; y < 3; ++y)
                {
                    for (int x = 3; x < 6; ++x)
                    {
                        if (m_options[y][x].has(v))
                        {
                            found = true;
                        }
                    }
                }
                if (!found)
                {
                    return false;
                }
            }
            return true;
        }
        case 2:
        {
            for (auto v = 1; v <= 9; ++v)
            {
                bool found = false;
                for (int y = 0; y < 3; ++y)
                {
                    for (int x = 6; x < 9; ++x)
                    {
                        if (m_options[y][x].has(v))
                        {
                            found = true;
                        }
                    }
                }
                if (!found)
                {
                    return false;
                }
            }
            return true;
        }
        case 3:
        {
            for (auto v = 1; v <= 9; ++v)
            {
                bool found = false;
                for (int y = 3; y < 6; ++y)
                {
                    for (int x = 0; x < 3; ++x)
                    {
                        if (m_options[y][x].has(v))
                        {
                            found = true;
                        }
                    }
                }
                if (!found)
                {
                    return false;
                }
            }
            return true;
        }
        case 4:
        {
            for (auto v = 1; v <= 9; ++v)
            {
                bool found = false;
                for (int y = 3; y < 6; ++y)
                {
                    for (int x = 3; x < 6; ++x)
                    {
                        if (m_options[y][x].has(v))
                        {
                            found = true;
                        }
                    }
                }
                if (!found)
                {
                    return false;
                }
            }
            return true;
        }
        case 5:
        {
            for (auto v = 1; v <= 9; ++v)
            {
                bool found = false;
                for (int y = 3; y < 6; ++y)
                {
                    for (int x = 6; x < 9; ++x)
                    {
                        if (m_options[y][x].has(v))
                        {
                            found = true;
                        }
                    }
                }
                if (!found)
                {
                    return false;
                }
            }
            return true;
        }
        case 6:
        {
            for (auto v = 1; v <= 9; ++v)
            {
                bool found = false;
                for (int y = 6; y < 9; ++y)
                {
                    for (int x = 0; x < 3; ++x)
                    {
                        if (m_options[y][x].has(v))
                        {
                            found = true;
                        }
                    }
                }
                if (!found)
                {
                    return false;
                }
            }
            return true;
        }
        case 7:
        {
            for (auto v = 1; v <= 9; ++v)
            {
                bool found = false;
                for (int y = 6; y < 9; ++y)
                {
                    for (int x = 3; x < 6; ++x)
                    {
                        if (m_options[y][x].has(v))
                        {
                            found = true;
                        }
                    }
                }
                if (!found)
                {
                    return false;
                }
            }
            return true;
        }
        case 8:
        {
            for (auto v = 1; v <= 9; ++v)
            {
                bool found = false;
                for (int y = 6; y < 9; ++y)
                {
                    for (int x = 6; x < 9; ++x)
                    {
                        if (m_options[y][x].has(v))
                        {
                            found = true;
                        }
                    }
                }
                if (!found)
                {
                    return false;
                }
            }
            return true;
        }
    }
    return false;
}

auto Board::round_coord(int coord) -> int
{
    return 3 * (coord / 3);
}
