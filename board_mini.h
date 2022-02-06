// Copyright 2022 Krzysztof Karbowiak

#pragma once

#include "options.h"

#include <array>
#include <algorithm>


class BoardMini
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

    private:
        auto index(unsigned int x, unsigned int y) const -> unsigned int;

    private:
        static constexpr auto m_width = 3u;
        static constexpr auto m_height = 3u;
        static constexpr std::array m_values = {1u, 2u, 3u, 4u, 5u, 6u, 7u, 8u, 9u};
        std::array<Options, m_width * m_height> m_options;
};

constexpr auto BoardMini::width()
{
    return m_width;
}

constexpr auto BoardMini::height()
{
    return m_height;
}

constexpr auto BoardMini::options()
{
    return m_values;
}

inline auto BoardMini::is_fixed() const
{
    return std::all_of(m_options.begin(), m_options.end(), [](auto option){ return option.is_fixed(); });
}

inline auto BoardMini::is_valid() const
{
    return std::none_of(m_options.begin(), m_options.end(), [](auto option){ return option.is_empty(); });
}

inline auto BoardMini::has_option(unsigned int x, unsigned int y, unsigned int value) const
{
    return m_options[index(x, y)].has(value);
}

inline auto BoardMini::is_fixed_at(unsigned int x, unsigned int y) const
{
    return m_options[index(x, y)].is_fixed();
}

inline auto BoardMini::fix_option(unsigned int x, unsigned int y, unsigned int value)
{
    for (auto yy = 0u; yy < m_height; ++yy)
    {
        for (auto xx = 0u; xx < m_width; ++xx)
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

inline auto BoardMini::is_solved() const
{
    if (!is_fixed())
    {
        return false;
    }

    if (std::any_of(m_values.begin(), m_values.end(), [this](auto value){ return std::none_of(m_options.begin(), m_options.end(), [value](auto option){ return option.has(value); }); }))
    {
        return false;
    }

    return true;
}

inline auto BoardMini::index(unsigned int x, unsigned int y) const -> unsigned int
{
    return y * m_width + x;
}
