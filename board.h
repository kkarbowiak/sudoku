// Copyright 2022 Krzysztof Karbowiak

#pragma once

#include "options.h"

#include <array>
#include <algorithm>


class Board
{
    public:
        constexpr auto width();
        constexpr auto height();
        constexpr auto options();

        auto is_fixed() const;
        auto is_valid() const;

        auto has_option(int x, int y, int value) const;
        auto is_fixed_at(int x, int y) const;
        auto fix_option(int x, int y, int value);

        auto is_solved() const;

    private:
        auto index(int x, int y) const -> int;

    private:
        static constexpr auto m_width = 3;
        static constexpr auto m_height = 3;
        static constexpr std::array m_values = {1, 2, 3, 4, 5, 6, 7, 8, 9};
        std::array<Options, m_width * m_height> m_options;
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
    return std::all_of(m_options.begin(), m_options.end(), [](auto option){ return option.is_fixed(); });
}

inline auto Board::is_valid() const
{
    return std::none_of(m_options.begin(), m_options.end(), [](auto option){ return option.is_empty(); });
}

inline auto Board::has_option(int x, int y, int value) const
{
    return m_options[index(x, y)].has(value);
}

inline auto Board::is_fixed_at(int x, int y) const
{
    return m_options[index(x, y)].is_fixed();
}

inline auto Board::fix_option(int x, int y, int value)
{
    for (auto yy = 0; yy < m_height; ++yy)
    {
        for (auto xx = 0; xx < m_width; ++xx)
        {
            if (yy == y && xx == x)
            {
                m_options[index(xx, yy)].fix(value);
            }
            else
            {
                m_options[index(xx, yy)].remove(value);
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

    for (auto v : m_values)
    {
        if (std::none_of(m_options.begin(), m_options.end(), [v](auto option){ return option.has(v); }))
        {
            return false;
        }
    }

    return true;
}

inline auto Board::index(int x, int y) const -> int
{
    return y * m_width + x;
}
