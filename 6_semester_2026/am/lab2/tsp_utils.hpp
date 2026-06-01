#ifndef TSP_UTILS_HPP
#define TSP_UTILS_HPP

#include "graph.hpp"
#include <numeric>
#include <algorithm>

inline double calculate_tour_cost(const Graph& graph, const std::vector<size_t>& tour) {
    double cost = 0.0;
    for (size_t i = 0; i < tour.size() - 1; ++i) {
        cost += graph.adjacency_matrix[tour[i]][tour[i + 1]];
    }
    cost += graph.adjacency_matrix[tour.back()][tour.front()];
    return cost;
}

inline std::vector<size_t> get_random_tour(size_t n) {
    std::vector<size_t> tour(n);
    std::iota(tour.begin(), tour.end(), 0);
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(tour.begin(), tour.end(), g);
    return tour;
}

#endif