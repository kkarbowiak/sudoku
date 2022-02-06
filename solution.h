// Copyright 2022 Krzysztof Karbowiak

#pragma once

#include <array>


struct Solution
{
    static constexpr auto m_width = 9;
    static constexpr auto m_height = 9;
    std::array<std::array<int, m_width>, m_height> m_values;
};

inline auto operator==(Solution const & lhs, Solution const & rhs)
{
    return lhs.m_values == rhs.m_values;
}
