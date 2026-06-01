#ifndef ANNEALING_HPP
#define ANNEALING_HPP

#include "tsp_utils.hpp"
#include <cmath>

inline std::vector<size_t> simulated_annealing(const Graph& graph, double T_start, double alpha, int epochs, int trials_per_epoch) {
    std::vector<size_t> current_tour = get_random_tour(graph.n);
    double current_cost = calculate_tour_cost(graph, current_tour);
    
    std::vector<size_t> best_tour = current_tour;
    double best_cost = current_cost;
    
    double T = T_start;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dist(0.0, 1.0);
    std::uniform_int_distribution<size_t> v_dist(0, graph.n - 1);

    for (int e = 0; e < epochs; ++e) {
        for (int t = 0; t < trials_per_epoch; ++t) {
            std::vector<size_t> next_tour = current_tour;
            size_t i = v_dist(gen);
            size_t j = v_dist(gen);
            std::swap(next_tour[i], next_tour[j]);
            
            double next_cost = calculate_tour_cost(graph, next_tour);
            double delta = next_cost - current_cost;

            if (delta < 0 || dist(gen) < std::exp(-delta / T)) {
                current_tour = next_tour;
                current_cost = next_cost;
                
                if (current_cost < best_cost) {
                    best_cost = current_cost;
                    best_tour = current_tour;
                }
            }
        }
        T *= alpha;
    }
    return best_tour;
}

#endif