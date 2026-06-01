#ifndef RANDOM_HPP
#define RANDOM_HPP

#include <algorithm>
#include <random>

#include "graph.hpp"

inline permutation_t random_tour(size_t n)
{
    permutation_t tour(n);
    for (size_t i = 0; i < n; ++i)
        tour[i] = i;

    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(tour.begin(), tour.end(), g);

    return tour;
}

#endif