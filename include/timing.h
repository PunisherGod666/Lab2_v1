#pragma once
#include "common.h"
#include <algorithm>
#include <array>
#include <chrono>
#include <stdexcept>
#include <utility>

namespace lab::timing
{
    inline constexpr std::size_t repetitions = 5;
    extern volatile bool result_sink;
    void print_row(const Experiment &test, const std::string &method,
                   unsigned k, Timing timing);

    template <class F>
    Timing timeit(F &&operation, bool expected)
    {
        if (operation() != expected)
            throw std::logic_error("Incorrect warm-up result");
        std::array<double, repetitions> times{};
        for (auto &time : times)
        {
            const auto start = std::chrono::steady_clock::now();
            const bool result = operation();
            const auto finish = std::chrono::steady_clock::now();
            result_sink = result;
            if (result != expected)
                throw std::logic_error("Incorrect measured result");
            time = std::chrono::duration<double, std::milli>(finish - start).count();
        }
        std::sort(times.begin(), times.end());
        return {times[times.size() / 2], result_sink};
    }

    template <class F>
    Timing record(const Experiment &test, const std::string &method,
                  unsigned k, F &&operation)
    {
        const auto result = timeit(std::forward<F>(operation), test.scenario == "all_true");
        print_row(test, method, k, result);
        return result;
    }
}
