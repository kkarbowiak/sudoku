// Copyright 2022 Krzysztof Karbowiak

#pragma once

#include <array>


struct Solution
{
    static constexpr auto m_width = 9u;
    static constexpr auto m_height = 9u;
    std::array<std::array<unsigned int, m_width>, m_height> m_values;
};

inline auto operator==(Solution const & lhs, Solution const & rhs)
{
    return lhs.m_values == rhs.m_values;
}
