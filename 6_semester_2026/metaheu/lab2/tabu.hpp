#ifndef TABU_SEARCH_HPP
#define TABU_SEARCH_HPP

#include "tsp_utils.hpp"
#include <deque>
#include <limits>
#include <vector>

struct Move {
    size_t u, v;
    bool operator==(const Move& other) const {
        return (u == other.u && v == other.v) || (u == other.v && v == other.u);
    }
};

inline std::vector<size_t> tabu_search(const Graph& graph, int max_iterations, size_t tabu_size) {
    const size_t n = graph.n;
    if (n < 2) return get_random_tour(n);

    std::vector<size_t> current_tour = get_random_tour(n);
    double current_cost = calculate_tour_cost(graph, current_tour);
    
    std::vector<size_t> best_overall_tour = current_tour;
    double best_overall_cost = current_cost;
    
    std::deque<Move> tabu_list;
    const auto& matrix = graph.adjacency_matrix;

    for (int iter = 0; iter < max_iterations; ++iter) {
        double best_delta = std::numeric_limits<double>::max();
        Move best_move = {0, 0};
        bool move_found = false;

        for (size_t i = 0; i < n; ++i) {
            for (size_t j = i + 1; j < n; ++j) {
                
                size_t prev_i = (i == 0) ? n - 1 : i - 1;
                size_t next_i = (i + 1) % n;
                size_t prev_j = (j == 0) ? n - 1 : j - 1;
                size_t next_j = (j + 1) % n;

                double delta = 0.0;

                if (next_i == j) { 
                    delta -= matrix[current_tour[prev_i]][current_tour[i]];
                    delta -= matrix[current_tour[j]][current_tour[next_j]];
                    
                    delta += matrix[current_tour[prev_i]][current_tour[j]];
                    delta += matrix[current_tour[i]][current_tour[next_j]];
                } 
                else if (next_j == i) {
                    delta -= matrix[current_tour[prev_j]][current_tour[j]];
                    delta -= matrix[current_tour[i]][current_tour[next_i]];
                    
                    delta += matrix[current_tour[prev_j]][current_tour[i]];
                    delta += matrix[current_tour[j]][current_tour[next_i]];
                }
                else { 
                    delta -= (matrix[current_tour[prev_i]][current_tour[i]] + matrix[current_tour[i]][current_tour[next_i]]);
                    delta -= (matrix[current_tour[prev_j]][current_tour[j]] + matrix[current_tour[j]][current_tour[next_j]]);
                    
                    delta += (matrix[current_tour[prev_i]][current_tour[j]] + matrix[current_tour[j]][current_tour[next_i]]);
                    delta += (matrix[current_tour[prev_j]][current_tour[i]] + matrix[current_tour[i]][current_tour[next_j]]);
                }

                Move current_move = {i, j};
                bool is_tabu = false;
                for (const auto& m : tabu_list) {
                    if (m == current_move) {
                        is_tabu = true;
                        break;
                    }
                }

                if (!is_tabu || (current_cost + delta < best_overall_cost - 1e-9)) {
                    if (delta < best_delta) {
                        best_delta = delta;
                        best_move = current_move;
                        move_found = true;
                    }
                }
            }
        }

        if (!move_found) break; 

        std::swap(current_tour[best_move.u], current_tour[best_move.v]);
        current_cost += best_delta;

        if (current_cost < best_overall_cost - 1e-9) {
            best_overall_cost = current_cost;
            best_overall_tour = current_tour;
        }

        tabu_list.push_back(best_move);
        if (tabu_list.size() > tabu_size) {
            tabu_list.pop_front();
        }
    }
    return best_overall_tour;
}

#endif