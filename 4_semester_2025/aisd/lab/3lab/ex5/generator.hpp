#ifndef GENERATOR_H
#define GENERATOR_H

#include <vector>
#include <algorithm>
#include <random>
#include <chrono>

std::vector<int> generate_random_keys(int n)
{
    std::vector<int> keys(n);
    std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());
    std::uniform_int_distribution<int> dist(0, 2 * n - 1);

    for (int i = 0; i < n; ++i)
    {
        keys[i] = dist(rng);
    }

    return keys;
}

std::vector<int> generate_ascending_keys(int n)
{
    std::vector<int> keys(2 * n);
    std::iota(keys.begin(), keys.end(), 0);

    std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());
    std::shuffle(keys.begin(), keys.end(), rng);

    keys.resize(n);

    std::sort(keys.begin(), keys.end());
    return keys;
}

std::vector<int> generate_descending_keys(int n)
{
    std::vector<int> keys(2 * n);
    std::iota(keys.begin(), keys.end(), 0);

    std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());
    std::shuffle(keys.begin(), keys.end(), rng);

    keys.resize(n);

    std::sort(keys.begin(), keys.end(), std::greater<int>());

    return keys;
}

int generate_random_key(int n) {
    std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());
    std::uniform_int_distribution<int> dist(1, n);
    return dist(rng);
}

#endif // GENERATOR_H