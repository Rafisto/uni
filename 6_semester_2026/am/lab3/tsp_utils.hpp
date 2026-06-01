#ifndef TSP_UTILS_HPP
#define TSP_UTILS_HPP

#include "graph.hpp"

inline uint64_t calculate_tour_cost(const Graph &graph, const permutation_t tour)
{
    uint64_t cost = 0.0;
    for (size_t i = 0; i < tour.size() - 1; ++i)
    {
        cost += graph.am[tour[i]][tour[i + 1]];
    }
    cost += graph.am[tour.back()][tour.front()];
    return cost;
}

#endif
