// Copyright 2022 Krzysztof Karbowiak

#pragma once

#include <array>
#include <bitset>


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
        std::bitset<9> m_options = 0b111111111;
};

constexpr auto Options::options()
{
    return m_values;
}

inline auto Options::fix(int value)
{
    m_options.reset();
    m_options.set(value - 1);
}

inline auto Options::remove(int value)
{
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
    return m_options.test(value - 1);
}
