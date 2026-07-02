#include <algorithm>
#include <cmath>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <omp.h>
#include <print>
#include <random>
#include <sstream>
#include <string>
#include <vector>
#include <deque>
#include <limits>

#include "graph.hpp"

constexpr const char *folder = "data/";
constexpr const char *match = "NODE_COORD_SECTION";
constexpr const char *files[] = {
    "western_sahara.tsp", "djibouti.tsp", "qatar.tsp",  "uruguay.tsp",
    "zimbabwe.tsp",       "oman.tsp",     "canada.tsp", "tanzania.tsp",
    "egypt.tsp",          "ireland.tsp"};

typedef std::pair<double, double> point;
typedef std::vector<point> point_list;
typedef std::vector<std::size_t> permutation;

uint64_t euclidean(const point x, const point y) {
    double dx = x.first - y.first;
    double dy = x.second - y.second;
    return static_cast<uint64_t>(std::round(std::sqrt(dx * dx + dy * dy)));
}

permutation get_nearest_neighbor(const Graph &g, size_t start_node, size_t n) {
    permutation perm;
    perm.reserve(n);
    std::vector<bool> visited(n, false);
    size_t current = start_node;
    perm.push_back(current);
    visited[current] = true;

    for (size_t i = 1; i < n; ++i) {
        size_t next_node = -1;
        uint64_t min_dist = std::numeric_limits<uint64_t>::max();
        for (size_t j = 0; j < n; ++j) {
            if (!visited[j] && g.adjacency_matrix[current][j] < min_dist) {
                min_dist = g.adjacency_matrix[current][j];
                next_node = j;
            }
        }
        if (next_node == -1) break; 
        current = next_node;
        visited[current] = true;
        perm.push_back(current);
    }
    return perm;
}

void tabu_search(const Graph &g, permutation &current_perm, uint64_t &current_dist, 
                 permutation &best_perm, uint64_t &best_dist, 
                 int max_iterations, size_t tabu_tenure, std::mt19937 &gen) {
    
    size_t n = current_perm.size();
    std::deque<std::pair<size_t, size_t>> tabu_list;

    for (int iter = 0; iter < max_iterations; ++iter) {
        int64_t best_move_delta = std::numeric_limits<int64_t>::max();
        size_t best_i = 0, best_j = 0;
        bool found_move = false;

        size_t sample_size = std::min((size_t)500, (n * (n - 1)) / 2);
        std::uniform_int_distribution<size_t> dist(1, n - 1);

        for (size_t s = 0; s < sample_size; ++s) {
            size_t i = dist(gen);
            size_t j = dist(gen);
            if (i > j) std::swap(i, j);
            if (i == j || i == 0) continue;

            size_t a = current_perm[i - 1];
            size_t b = current_perm[i];
            size_t c = current_perm[j];
            size_t d = (j + 1 == n) ? current_perm[0] : current_perm[j + 1];

            int64_t delta = static_cast<int64_t>(g.adjacency_matrix[a][c] + g.adjacency_matrix[b][d]) - 
                            static_cast<int64_t>(g.adjacency_matrix[a][b] + g.adjacency_matrix[c][d]);

            bool is_tabu = false;
            for (auto &edge : tabu_list) {
                if ((edge.first == a && edge.second == c) || (edge.first == b && edge.second == d)) {
                    is_tabu = true;
                    break;
                }
            }

            if (current_dist + delta < best_dist) {
                best_move_delta = delta;
                best_i = i; best_j = j;
                found_move = true;
                break; 
            }

            if (!is_tabu && delta < best_move_delta) {
                best_move_delta = delta;
                best_i = i; best_j = j;
                found_move = true;
            }
        }

        if (found_move) {
            std::reverse(current_perm.begin() + best_i, current_perm.begin() + best_j + 1);
            current_dist += best_move_delta;

            if (current_dist < best_dist) {
                best_dist = current_dist;
                best_perm = current_perm;
            }

            tabu_list.push_back({current_perm[best_i - 1], current_perm[best_i]});
            if (tabu_list.size() > tabu_tenure) tabu_list.pop_front();
        }
    }
}

int main() {
    for (std::string filename : files) {
        point_list points;
        std::ifstream infile(folder + filename);
        if (!infile) continue;

        std::string line;
        bool read = false;
        while (std::getline(infile, line)) {
            if (line.starts_with(match)) { read = true; continue; }
            if (!read || line.empty() || line.starts_with("EOF")) continue;
            std::istringstream iss(line);
            size_t id; double x, y;
            if (iss >> id >> x >> y) points.push_back({x, y});
        }

        size_t n = points.size();
        Graph full_graph(n);
        for (size_t i = 0; i < n; ++i) {
            for (size_t j = 0; j < n; ++j) {
                full_graph.adjacency_matrix[i][j] = (i == j) ? 0 : euclidean(points[i], points[j]);
            }
        }

        permutation global_best_perm;
        uint64_t global_best_dist = std::numeric_limits<uint64_t>::max();

        #pragma omp parallel
        {
            std::mt19937 thread_gen(std::random_device{}() ^ omp_get_thread_num());
            permutation local_best_p;
            uint64_t local_best_d = std::numeric_limits<uint64_t>::max();

            #pragma omp for schedule(dynamic)
            for (int start_node = 0; start_node < std::min((int)n, 64); ++start_node) {
                permutation curr_p = get_nearest_neighbor(full_graph, start_node, n);
                uint64_t curr_d = 0;
                for(size_t i=0; i<n; ++i) curr_d += full_graph.adjacency_matrix[curr_p[i]][curr_p[(i+1)%n]];

                permutation run_best_p = curr_p;
                uint64_t run_best_d = curr_d;

                tabu_search(full_graph, curr_p, curr_d, run_best_p, run_best_d, 2000, n/10, thread_gen);

                if (run_best_d < local_best_d) {
                    local_best_d = run_best_d;
                    local_best_p = run_best_p;
                }
            }

            #pragma omp critical
            {
                if (local_best_d < global_best_dist) {
                    global_best_dist = local_best_d;
                    global_best_perm = local_best_p;
                }
            }
        }

        std::println("File: {}\nbest_distance: {}", filename, global_best_dist);
        for (size_t v : global_best_perm) {
            std::println("{};{};{}", v + 1, points[v].first, points[v].second);
        }
    }
    return 0;
}