#ifndef ANNEALING_HPP
#define ANNEALING_HPP

#include <cmath>
#include <omp.h>
#include <vector>
#include <random>
#include <algorithm>

#include "graph.hpp"
#include "tsp_utils.hpp"
#include "mst_tour.hpp"

struct AnnealingStats {
    uint64_t best_distance;
    permutation_t best_permutation;
};

inline AnnealingStats simulated_annealing(const Graph& graph, double T_start, double alpha, int epochs, int trials_per_epoch, std::mt19937 &gen) {
    const size_t n = graph.n;
    permutation_t current_tour = get_initial_mst_tour(graph);

    uint64_t current_cost = calculate_tour_cost(graph, current_tour);
    permutation_t best_tour = current_tour;
    uint64_t best_cost = current_cost;
    
    double T = T_start;
    std::uniform_real_distribution<double> prob_dist(0.0, 1.0);
    std::uniform_int_distribution<size_t> idx_dist(0, n - 1);

    for (int e = 0; e < epochs; ++e) {
        for (int t = 0; t < trials_per_epoch; ++t) {
            size_t i = idx_dist(gen);
            size_t j = idx_dist(gen);
            if (i == j) continue;
            if (i > j) std::swap(i, j);

            size_t idx_before_i = (i == 0) ? n - 1 : i - 1;
            size_t idx_after_j  = (j == n - 1) ? 0 : j + 1;

            size_t node_before_i = current_tour[idx_before_i];
            size_t node_i        = current_tour[i];
            size_t node_j        = current_tour[j];
            size_t node_after_j  = current_tour[idx_after_j];

            double old_edges = graph.am[node_before_i][node_i] + graph.am[node_j][node_after_j];
            double new_edges = graph.am[node_before_i][node_j] + graph.am[node_i][node_after_j];
            double delta = new_edges - old_edges;

            if (i == 0 && j == n - 1) continue; 

            bool accept = false;
            if (delta <= 0) {
                accept = true;
            } else {
                if (T > 1e-9 && prob_dist(gen) < std::exp(-delta / T)) {
                    accept = true;
                }
            }

            if (accept) {
                std::reverse(current_tour.begin() + i, current_tour.begin() + j + 1);
                int64_t new_cost = static_cast<int64_t>(current_cost) + static_cast<int64_t>(delta);
                current_cost = static_cast<uint64_t>(new_cost);
                
                if (current_cost < best_cost) {
                    best_cost = current_cost;
                    best_tour = current_tour;
                }
            }
        }
        T *= alpha;
    }
    return {best_cost, best_tour};
}

inline AnnealingStats best_annealing(const Graph& g, const uint64_t n) {
    std::vector<uint64_t> results(n);
    std::vector<int> steps(n);
    
    uint64_t global_best_dist = std::numeric_limits<uint64_t>::max();
    permutation_t global_best_perm;

    #pragma omp parallel
    {
        std::mt19937 thread_gen(std::random_device{}() ^ (omp_get_thread_num() + 1));

        #pragma omp for schedule(dynamic)
        for (uint64_t i = 0; i < n; ++i) {
            AnnealingStats stats = simulated_annealing(g, 10000.0, 0.99, 500, 1000, thread_gen);

            results[i] = stats.best_distance;

            #pragma omp critical
            {
                if (stats.best_distance < global_best_dist) {
                    global_best_dist = stats.best_distance;
                    global_best_perm = stats.best_permutation;
                }
            }
        }
    }

    return {global_best_dist, global_best_perm};
}

#endif