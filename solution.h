// Copyright 2022 Krzysztof Karbowiak

#pragma once

#include <array>


struct Solution
{
    static constexpr auto width = 9u;
    static constexpr auto height = 9u;
    std::array<std::array<unsigned int, width>, height> values;
};

inline auto operator==(Solution const & lhs, Solution const & rhs)
{
    return lhs.values == rhs.values;
}
