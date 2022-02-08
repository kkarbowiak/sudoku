// Copyright 2022 Krzysztof Karbowiak

#pragma once

#include "options.h"
#include "solution.h"

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

        auto has_option(unsigned int x, unsigned int y, unsigned int value) const;
        auto is_fixed_at(unsigned int x, unsigned int y) const;
        auto fix_option(unsigned int x, unsigned int y, unsigned int value);

        auto is_solved() const;

        auto get_solution() const;

    private:
        auto is_row_solved(unsigned int row) const -> bool;
        auto is_column_solved(unsigned int column) const -> bool;
        auto is_square_solved(unsigned int square) const -> bool;

        static auto round_coord(unsigned int coord) -> unsigned int;

    private:
        static constexpr auto m_width = 9u;
        static constexpr auto m_height = 9u;
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

inline auto Board::has_option(unsigned int x, unsigned int y, unsigned int value) const
{
    assert(x < m_width);
    assert(y < m_height);

    return m_options[y][x].has(value);
}

inline auto Board::is_fixed_at(unsigned int x, unsigned int y) const
{
    assert(x < m_width);
    assert(y < m_height);

    return m_options[y][x].is_fixed();
}

inline auto Board::fix_option(unsigned int x, unsigned int y, unsigned int value)
{
    assert(x < m_width);
    assert(y < m_height);

    m_options[y][x].fix(value);

    for (auto xx = 0u; xx < m_width; ++xx)
    {
        if (xx != x)
        {
            m_options[y][xx].remove(value);
        }
    }
    for (auto yy = 0u; yy < m_height; ++yy)
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

    for (auto i = 0u; i < 9u; ++i)
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

inline auto Board::get_solution() const
{
    Solution solution{};

    for (auto y = 0u; y < m_height; ++y)
    {
        for (auto x = 0u; x < m_width; ++x)
        {
            for (auto v : Options::options())
            {
                if (m_options[y][x].has(v))
                {
                    solution.values[y][x] = v;
                }
            }
        }
    }

    return solution;
}

inline auto Board::is_row_solved(unsigned int row) const -> bool
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

inline auto Board::is_column_solved(unsigned int column) const -> bool
{
    for (auto v : Options::options())
    {
        bool found = false;
        for (auto y = 0u; y < m_height; ++y)
        {
            if (m_options[y][column].has(v))
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

inline auto Board::is_square_solved(unsigned int square) const -> bool
{
    switch (square)
    {
        case 0u:
        {
            for (auto v = 1u; v <= 9u; ++v)
            {
                bool found = false;
                for (auto y = 0u; y < 3u; ++y)
                {
                    for (auto x = 0u; x < 3u; ++x)
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
        case 1u:
        {
            for (auto v = 1u; v <= 9u; ++v)
            {
                bool found = false;
                for (auto y = 0u; y < 3u; ++y)
                {
                    for (auto x = 3u; x < 6u; ++x)
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
        case 2u:
        {
            for (auto v = 1u; v <= 9u; ++v)
            {
                bool found = false;
                for (auto y = 0u; y < 3u; ++y)
                {
                    for (auto x = 6u; x < 9u; ++x)
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
        case 3u:
        {
            for (auto v = 1u; v <= 9u; ++v)
            {
                bool found = false;
                for (auto y = 3u; y < 6u; ++y)
                {
                    for (auto x = 0u; x < 3u; ++x)
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
        case 4u:
        {
            for (auto v = 1u; v <= 9u; ++v)
            {
                bool found = false;
                for (auto y = 3u; y < 6u; ++y)
                {
                    for (auto x = 3u; x < 6u; ++x)
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
        case 5u:
        {
            for (auto v = 1u; v <= 9u; ++v)
            {
                bool found = false;
                for (auto y = 3u; y < 6u; ++y)
                {
                    for (auto x = 6u; x < 9u; ++x)
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
        case 6u:
        {
            for (auto v = 1u; v <= 9u; ++v)
            {
                bool found = false;
                for (auto y = 6u; y < 9u; ++y)
                {
                    for (auto x = 0u; x < 3u; ++x)
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
        case 7u:
        {
            for (auto v = 1u; v <= 9u; ++v)
            {
                bool found = false;
                for (auto y = 6u; y < 9u; ++y)
                {
                    for (auto x = 3u; x < 6u; ++x)
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
        case 8u:
        {
            for (auto v = 1u; v <= 9u; ++v)
            {
                bool found = false;
                for (auto y = 6u; y < 9u; ++y)
                {
                    for (auto x = 6u; x < 9u; ++x)
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

inline auto Board::round_coord(unsigned int coord) -> unsigned int
{
    return 3u * (coord / 3u);
}
