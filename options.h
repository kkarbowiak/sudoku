// Copyright 2022 Krzysztof Karbowiak

#pragma once

#include <array>
#include <bitset>
#include <algorithm>
#include <limits>
#include <cassert>


class Options
{
    public:
        static constexpr auto options();

        auto fix(int value);
        auto remove(int value);

        auto is_empty() const;
        auto is_fixed() const;
        auto has(int value) const;

    private:
        static constexpr std::array m_values = {1, 2, 3, 4, 5, 6, 7, 8, 9};
        std::bitset<m_values.size()> m_options = std::numeric_limits<unsigned long long int>::max();
};

constexpr auto Options::options()
{
    return m_values;
}

inline auto Options::fix(int value)
{
    assert(std::find(m_values.begin(), m_values.end(), value) != m_values.end());

    m_options.reset();
    m_options.set(value - 1);
}

inline auto Options::remove(int value)
{
    assert(std::find(m_values.begin(), m_values.end(), value) != m_values.end());

    m_options.reset(value - 1);
}

inline auto Options::is_empty() const
{
    return m_options.none();
}

inline auto Options::is_fixed() const
{
    return m_options.count() == 1;
}

inline auto Options::has(int value) const
{
    assert(std::find(m_values.begin(), m_values.end(), value) != m_values.end());

    return m_options.test(value - 1);
}
