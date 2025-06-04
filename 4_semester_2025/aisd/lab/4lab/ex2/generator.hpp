#ifndef GENERATOR_H
#define GENERATOR_H

#include <vector>
#include <algorithm>
#include <random>
#include <chrono>

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

inline std::vector<int> generate_ascending_keys(size_t n)
{
    std::vector<int> keys(n);
    std::iota(keys.begin(), keys.end(), 0);
    std::mt19937 rng(static_cast<unsigned long>(std::chrono::steady_clock::now().time_since_epoch().count()));
    std::shuffle(keys.begin(), keys.end(), rng);

    keys.resize(n);

    std::sort(keys.begin(), keys.end());
    return keys;
}

inline std::vector<int> generate_descending_keys(size_t n)
{
    std::vector<int> keys(n);
    std::iota(keys.begin(), keys.end(), 0);

    std::mt19937 rng(static_cast<unsigned long>(std::chrono::steady_clock::now().time_since_epoch().count()));
    std::shuffle(keys.begin(), keys.end(), rng);

    keys.resize(n);

    std::sort(keys.begin(), keys.end(), std::greater<int>());

    return keys;
}

inline std::vector<int> ascending_keys(size_t n)
{
    std::vector<int> keys(static_cast<unsigned long int>(n));
    std::iota(keys.begin(), keys.end(), 0);
    return keys;
}

inline std::vector<int> descending_keys(size_t n)
{
    std::vector<int> keys(n);
    std::iota(keys.begin(), keys.end(), 0);
    std::reverse(keys.begin(), keys.end());
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

inline int generate_random_key(size_t n)
{
    std::mt19937 rng(static_cast<unsigned long>(std::chrono::steady_clock::now().time_since_epoch().count()));
    std::uniform_int_distribution<int> dist(1, static_cast<int>(n));
    return dist(rng);
}

#endif // GENERATOR_H