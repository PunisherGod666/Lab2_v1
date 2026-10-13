#pragma once
#include "common.h"
#include <algorithm>
#include <functional>
#include <iterator>
#include <thread>

namespace lab::parallel
{
    template <class Iterator, class Predicate>
    struct all_of_block
    {
        void operator()(Iterator first, Iterator last, Predicate predicate,
                        unsigned char &result) const
        {
            result = std::all_of(first, last, predicate);
        }
    };

    template <class Iterator, class Predicate>
    bool parallel_all_of(Iterator first, Iterator last, Predicate predicate, unsigned k)
    {
        const std::size_t length = std::distance(first, last);
        if (length == 0)
            return true;
        k = static_cast<unsigned>(std::max<std::size_t>(1, std::min<std::size_t>(k, length)));
        const std::size_t block_size = length / k;
        const std::size_t remainder = length % k;
        std::vector<unsigned char> results(k);
        std::vector<std::jthread> threads;
        threads.reserve(k);
        Iterator block_start = first;
        for (unsigned i = 0; i < k; ++i)
        {
            Iterator block_end = block_start;
            std::advance(block_end, block_size + (i < remainder ? 1 : 0));
            threads.emplace_back(all_of_block<Iterator, Predicate>(), block_start,
                                 block_end, predicate, std::ref(results[i]));
            block_start = block_end;
        }
        for (auto &thread : threads)
            thread.join();
        return std::all_of(results.begin(), results.end(), [](unsigned char result)
                           { return result != 0; });
    }

    void run(const Experiment &test);
}
