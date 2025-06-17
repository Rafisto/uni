#ifndef GENERATOR_H
#define GENERATOR_H

#include <vector>
#include <random>
#include <chrono>
#include <algorithm>

inline std::vector<int> generate_random_keys(size_t n)
{
    std::vector<int> keys(n);
    std::mt19937 rng(static_cast<unsigned long>(std::chrono::steady_clock::now().time_since_epoch().count()));
    std::uniform_int_distribution<int> dist(0, static_cast<int>(n));

    for (size_t i = 0; i < n; ++i)
    {
        keys[i] = dist(rng);
    }

    return keys;
}

inline std::vector<int> generate_random_permutation(size_t n)
{
    std::vector<int> keys(n);
    std::iota(keys.begin(), keys.end(), 0);

    std::mt19937 rng(static_cast<unsigned long>(std::chrono::steady_clock::now().time_since_epoch().count()));
    std::shuffle(keys.begin(), keys.end(), rng);

    return keys;
}

#endif