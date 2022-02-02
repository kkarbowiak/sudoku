// Copyright 2022 Krzysztof Karbowiak

#pragma once

#include "options.h"

#include <array>
#include <algorithm>


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

    private:
        static constexpr auto m_width = 9;
        static constexpr auto m_height = 9;
        static constexpr std::array m_values = {1, 2, 3, 4, 5, 6, 7, 8, 9};
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
    return m_values;
}

inline auto Board::is_fixed() const
{
    for (auto const & row : m_options)
    {
        if (!std::all_of(row.begin(), row.end(), [](auto option){ return option.is_fixed(); }))
        {
            return false;
        }
    }
    return true;
}

inline auto Board::is_valid() const
{
    for (auto const & row : m_options)
    {
        if (std::any_of(row.begin(), row.end(), [](auto option){ return option.is_empty(); }))
        {
            return false;
        }
    }
    return true;
}

inline auto Board::has_option(int x, int y, int value) const
{
    return m_options[y][x].has(value);
}

inline auto Board::is_fixed_at(int x, int y) const
{
    return m_options[y][x].is_fixed();
}

inline auto Board::fix_option(int x, int y, int value)
{
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

    for (auto yy = 3 * (y / 3); yy < 3 * (y / 3) + 3; ++yy)
    {
        for (auto xx = 3 * (x / 3); xx < 3 * (x / 3) + 3; ++xx)
        {
            if (yy != y && xx != x)
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
    for (auto v = 1; v <= 9; ++v)
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
    for (auto v = 1; v <= 9; ++v)
    {
        bool found = false;
        for (int r = 0; r < 9; ++r)
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
