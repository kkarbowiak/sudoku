#pragma once

#include "options.h"

#include <array>
#include <algorithm>


class Board
{
    public:
        auto is_fixed() const;
        auto is_valid() const;

        auto has_option(int x, int y, int value) const;
        auto is_fixed_at(int x, int y) const;
        auto fix_option(int x, int y, int value);

        auto is_solved() const;

    private:
        std::array<Options, 9> m_options;
};

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
    return m_options[y * 3 + x].has(value);
}

inline auto Board::is_fixed_at(int x, int y) const
{
    return m_options[y * 3 + x].is_fixed();
}

inline auto Board::fix_option(int x, int y, int value)
{
    for (auto yy = 0; yy < 3; ++yy)
    {
        for (auto xx = 0; xx < 3; ++xx)
        {
            if (yy == y && xx == x)
            {
                m_options[yy * 3 + xx].fix(value);
            }
            else
            {
                m_options[yy * 3 + xx].remove(value);
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

    for (auto v = 1; v <= 9; ++v)
    {
        if (std::none_of(m_options.begin(), m_options.end(), [v](auto option){ return option.has(v); }))
        {
            return false;
        }
    }

    return true;
}
