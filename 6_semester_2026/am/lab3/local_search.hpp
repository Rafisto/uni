#ifndef LOCAL_SEARCH_HPP
#define LOCAL_SEARCH_HPP

#include <algorithm>
#include <functional>
#include <vector>
#include <numeric>
#include <random>
#include <omp.h>
#include <limits>

#include "graph.hpp"
#include "tsp_utils.hpp"
#include "mst_tour.hpp"

struct LocalSearchStats {
    double avg_distance;
    double avg_steps;
    uint64_t best_distance;
    permutation_t best_permutation;
};

// best of all neighbors
inline bool local_search_full_step(const Graph &g, permutation_t &perm, uint64_t &current_dist, std::mt19937 _) {
    const size_t n = perm.size();
    for (size_t i = 0; i < n - 1; ++i) {
        for (size_t j = i + 2; j < n; ++j) {
            size_t a = perm[i];
            size_t b = perm[i + 1];
            size_t c = perm[j];
            size_t d = (j == n - 1) ? perm[0] : perm[j + 1];

            int64_t old_edges = g.am[a][b] + g.am[c][d];
            int64_t new_edges = g.am[a][c] + g.am[b][d];

            if (new_edges < old_edges) {
                std::reverse(perm.begin() + i + 1, perm.begin() + j + 1);
                current_dist -= (old_edges - new_edges);
                return true;
            }
        }
    }
    return false;
}

// best of n random neighbors
inline bool local_search_best_n_step(const Graph &g, permutation_t &perm, uint64_t &current_dist, std::mt19937 &gen) {
    const size_t n = perm.size();
    if (n < 4) return false;
    
    bool improved = false;

    for (size_t k = 0; k < n; ++k) {
        std::uniform_int_distribution<size_t> dist_i(0, n - 3);
        size_t i = dist_i(gen);

        std::uniform_int_distribution<size_t> dist_j(i + 2, n - 1);
        size_t j = dist_j(gen);

        size_t a = perm[i];
        size_t b = perm[i + 1];
        size_t c = perm[j];
        size_t d = (j == n - 1) ? perm[0] : perm[j + 1];

        int64_t old_edges = g.am[a][b] + g.am[c][d];
        int64_t new_edges = g.am[a][c] + g.am[b][d];

        if (new_edges < old_edges) {
            std::reverse(perm.begin() + i + 1, perm.begin() + j + 1);
            current_dist -= (old_edges - new_edges);
            improved = true;
        }
    }
    return improved;
}

enum StartStrategy {
    START_RANDOM,
    START_MST
};

inline LocalSearchStats local_search(const Graph &g, StartStrategy start_strategy, std::function<bool(const Graph&, permutation_t&, uint64_t&, std::mt19937&)> local_search_step) {
    const size_t n = g.n;
    
    std::vector<uint64_t> all_distances(n);
    std::vector<size_t> all_steps(n);
    
    uint64_t global_best_dist = std::numeric_limits<uint64_t>::max();
    permutation_t global_best_perm;

    #pragma omp parallel
    {
        std::mt19937 thread_gen(std::random_device{}() ^ omp_get_thread_num());

        permutation_t base_perm(n);
        if (start_strategy == START_MST) {
            permutation_t mst_perm = get_initial_mst_tour(g);
            std::copy(mst_perm.begin(), mst_perm.end(), base_perm.begin());
        }
        else {
            std::iota(base_perm.begin(), base_perm.end(), 0);
        }

        #pragma omp for schedule(dynamic)
        for (size_t i = 0; i < sqrt(n); ++i) {
            permutation_t current_perm = base_perm;
            std::shuffle(current_perm.begin(), current_perm.end(), thread_gen);
            
            uint64_t current_dist = calculate_tour_cost(g, current_perm);
            size_t steps = 0;

            while (local_search_step(g, current_perm, current_dist, thread_gen)) {
                steps++;
            }

            all_distances[i] = current_dist;
            all_steps[i] = steps;

            #pragma omp critical
            {
                if (current_dist < global_best_dist) {
                    global_best_dist = current_dist;
                    global_best_perm = current_perm;
                }
            }
        }
    }

    double sum_dist = std::accumulate(all_distances.begin(), all_distances.end(), 0.0);
    double sum_steps = std::accumulate(all_steps.begin(), all_steps.end(), 0.0);

    return {
        sum_dist / n,
        sum_steps / n,
        global_best_dist,
        global_best_perm
    };
}

#endif