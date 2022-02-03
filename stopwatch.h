// Copyright 2022 Krzysztof Karbowiak

#pragma once

#include <chrono>


class Stopwatch
{
    public:
        auto start();
        auto stop();
        auto get_seconds() const;

    private:
        std::chrono::time_point<std::chrono::steady_clock> m_begin;
        std::chrono::time_point<std::chrono::steady_clock> m_end;
};

inline auto Stopwatch::start()
{
    m_begin = std::chrono::steady_clock::now();
}

inline auto Stopwatch::stop()
{
    m_end = std::chrono::steady_clock::now();
}

inline auto Stopwatch::get_seconds() const
{
    std::chrono::duration<double> const diff = m_end - m_begin;
    return diff.count();
}
