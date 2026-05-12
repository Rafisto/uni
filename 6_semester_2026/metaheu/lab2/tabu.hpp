#ifndef TABU_SEARCH_HPP
#define TABU_SEARCH_HPP

#include "tsp_utils.hpp"
#include <deque>

struct Move {
    size_t u, v;
    bool operator==(const Move& other) const {
        return (u == other.u && v == other.v) || (u == other.v && v == other.u);
    }
};

inline std::vector<size_t> tabu_search(const Graph& graph, int max_iterations, size_t tabu_size) {
    std::vector<size_t> current_tour = get_random_tour(graph.n);
    double current_cost = calculate_tour_cost(graph, current_tour);
    
    std::vector<size_t> best_overall_tour = current_tour;
    double best_overall_cost = current_cost;
    
    std::deque<Move> tabu_list;

    for (int iter = 0; iter < max_iterations; ++iter) {
        double best_neighbor_cost = std::numeric_limits<double>::max();
        std::vector<size_t> best_neighbor_tour;
        Move best_move = {0, 0};

        for (size_t i = 0; i < graph.n; ++i) {
            for (size_t j = i + 1; j < graph.n; ++j) {
                Move current_move = {i, j};
                
                bool is_tabu = false;
                for (const auto& m : tabu_list) {
                    if (m == current_move) {
                        is_tabu = true;
                        break;
                    }
                }

                std::vector<size_t> neighbor = current_tour;
                std::swap(neighbor[i], neighbor[j]);
                double neighbor_cost = calculate_tour_cost(graph, neighbor);

                if (!is_tabu || neighbor_cost < best_overall_cost) {
                    if (neighbor_cost < best_neighbor_cost) {
                        best_neighbor_cost = neighbor_cost;
                        best_neighbor_tour = neighbor;
                        best_move = current_move;
                    }
                }
            }
        }

        if (best_neighbor_tour.empty()) break; 

        current_tour = best_neighbor_tour;
        current_cost = best_neighbor_cost;

        if (current_cost < best_overall_cost) {
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