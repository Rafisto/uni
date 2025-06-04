#ifndef GENERATOR_H
#define GENERATOR_H

using namespace std;

#include <vector>
#include <algorithm>
#include <random>
#include <chrono>

inline vector<int> generate_random_keys(size_t n)
{
    vector<int> keys(n);
    mt19937 rng(static_cast<unsigned long>(chrono::steady_clock::now().time_since_epoch().count()));
    uniform_int_distribution<int> dist(0, static_cast<int>(n));

    for (size_t i = 0; i < n; ++i)
    {
        keys[i] = dist(rng);
    }

    return keys;
}

inline vector<int> generate_ascending_keys(size_t n)
{
    vector<int> keys(n);
    iota(keys.begin(), keys.end(), 0);
    mt19937 rng(static_cast<unsigned long>(chrono::steady_clock::now().time_since_epoch().count()));
    shuffle(keys.begin(), keys.end(), rng);

    keys.resize(n);

    sort(keys.begin(), keys.end());
    return keys;
}

inline vector<int> generate_descending_keys(size_t n)
{
    vector<int> keys(n);
    iota(keys.begin(), keys.end(), 0);

    mt19937 rng(static_cast<unsigned long>(chrono::steady_clock::now().time_since_epoch().count()));
    shuffle(keys.begin(), keys.end(), rng);

    keys.resize(n);

    sort(keys.begin(), keys.end(), greater<int>());

    return keys;
}

inline vector<int> ascending_keys(size_t n)
{
    vector<int> keys(static_cast<unsigned long int>(n));
    iota(keys.begin(), keys.end(), 0);
    return keys;
}

inline vector<int> descending_keys(size_t n)
{
    vector<int> keys(n);
    iota(keys.begin(), keys.end(), 0);
    reverse(keys.begin(), keys.end());
    return keys;
}

inline vector<int> generate_random_permutation(size_t n)
{
    vector<int> keys(n);
    iota(keys.begin(), keys.end(), 0);

    mt19937 rng(static_cast<unsigned long>(chrono::steady_clock::now().time_since_epoch().count()));
    shuffle(keys.begin(), keys.end(), rng);

    return keys;
}

inline int generate_random_key(size_t n)
{
    mt19937 rng(static_cast<unsigned long>(chrono::steady_clock::now().time_since_epoch().count()));
    uniform_int_distribution<int> dist(1, static_cast<int>(n));
    return dist(rng);
}

#endif // GENERATOR_H