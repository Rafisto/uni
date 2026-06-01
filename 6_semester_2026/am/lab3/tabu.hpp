#ifndef TABU_SEARCH_HPP
#define TABU_SEARCH_HPP

#include <vector>
#include <algorithm>
#include <numeric>
#include <omp.h>
#include <limits>
#include <random>

#include "graph.hpp"
#include "tsp_utils.hpp"
#include "mst_tour.hpp"

struct TabuStats {
    uint64_t best_distance;
    double avg_distance;
    permutation_t best_permutation;
};

inline permutation_t tabu_search_step(const Graph &g, const permutation_t& start_perm, size_t tenure, int max_no_improve) {
    const size_t n = g.n;
    permutation_t current_perm = start_perm;
    uint64_t current_dist = calculate_tour_cost(g, current_perm);

    permutation_t best_so_far_perm = current_perm;
    uint64_t best_so_far_dist = current_dist;

    std::vector<std::vector<int>> tabu_matrix(n, std::vector<int>(n, 0));

    int iter = 0;
    int last_improvement = 0;

    while (iter - last_improvement < max_no_improve) {
        iter++;
        
        size_t best_i = 0, best_j = 0;
        int64_t best_delta = std::numeric_limits<int64_t>::max();
        bool found_move = false;

        for (size_t i = 0; i < n - 1; ++i) {
            for (size_t j = i + 2; j < n; ++j) {
                size_t u = current_perm[i];
                size_t v = current_perm[i + 1];
                size_t w = current_perm[j];
                size_t z = (j == n - 1) ? current_perm[0] : current_perm[j + 1];

                int64_t delta = static_cast<int64_t>(g.am[u][w] + g.am[v][z]) - 
                                static_cast<int64_t>(g.am[u][v] + g.am[w][z]);

                bool is_tabu = (tabu_matrix[u][v] > iter || tabu_matrix[w][z] > iter);
                
                if (delta < best_delta) {
                    if (!is_tabu || (current_dist + delta < best_so_far_dist)) {
                        best_delta = delta;
                        best_i = i;
                        best_j = j;
                        found_move = true;
                    }
                }
            }
        }

        if (found_move) {
            size_t u = current_perm[best_i];
            size_t v = current_perm[best_i + 1];
            size_t w = current_perm[best_j];
            size_t z = (best_j == n - 1) ? current_perm[0] : current_perm[best_j + 1];

            std::reverse(current_perm.begin() + best_i + 1, current_perm.begin() + best_j + 1);
            current_dist = static_cast<uint64_t>(static_cast<int64_t>(current_dist) + best_delta);

            tabu_matrix[u][v] = iter + (int)tenure;
            tabu_matrix[v][u] = iter + (int)tenure;
            tabu_matrix[w][z] = iter + (int)tenure;
            tabu_matrix[z][w] = iter + (int)tenure;

            if (current_dist < best_so_far_dist) {
                best_so_far_dist = current_dist;
                best_so_far_perm = current_perm;
                last_improvement = iter;
            }
        } else {
            break; 
        }
    }

    return best_so_far_perm;
}

inline TabuStats tabu_search(const Graph &g, int num_tries = 100) {
    const size_t n = g.n;
    permutation_t mst_tour = get_initial_mst_tour(g);
    
    std::vector<uint64_t> all_results(num_tries);
    uint64_t global_best_dist = std::numeric_limits<uint64_t>::max();
    permutation_t global_best_perm;

    size_t tenure = (size_t)sqrt(n) > 10 ? (size_t)sqrt(n) : 10;
    int max_no_improve = 100;

    #pragma omp parallel
    {
        std::mt19937 thread_gen(std::random_device{}() ^ omp_get_thread_num());

        #pragma omp for schedule(dynamic)
        for (int i = 0; i < num_tries; ++i) {
            permutation_t start_perm = mst_tour;
            permutation_t result = tabu_search_step(g, start_perm, tenure, max_no_improve);
            uint64_t dist = calculate_tour_cost(g, result);
            
            all_results[i] = dist;

            #pragma omp critical
            {
                if (dist < global_best_dist) {
                    global_best_dist = dist;
                    global_best_perm = result;
                }
            }
        }
    }

    double avg = std::accumulate(all_results.begin(), all_results.end(), 0.0) / num_tries;
    return {global_best_dist, avg, global_best_perm};
}

#endif