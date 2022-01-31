// Copyright 2022 Krzysztof Karbowiak

#pragma once

#include <bitset>


class Options
{
    public:
        auto fix(int value);
        auto remove(int value);

        auto is_empty() const;
        auto is_fixed() const;
        auto has(int value) const;

    private:
        std::bitset<9> m_options = 0b111111111;
};

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
