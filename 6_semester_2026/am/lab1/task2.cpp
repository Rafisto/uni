#include <algorithm>
#include <cmath>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <numeric>
#include <print>
#include <random>
#include <sstream>
#include <string>
#include <vector>
#include <omp.h>
#include <atomic>

#include "graph.hpp"

constexpr const char *folder = "data/";
constexpr const char *match = "NODE_COORD_SECTION";
constexpr const char *files[] = {
    "western_sahara.tsp", "djibouti.tsp", "qatar.tsp", "uruguay.tsp",
    "zimbabwe.tsp", "oman.tsp", "canada.tsp", "tanzania.tsp", 
    "egypt.tsp", "ireland.tsp"};

typedef std::pair<double, double> point;
typedef std::vector<point> point_list;
typedef std::vector<std::size_t> permutation;

uint64_t euclidean(const point x, const point y) {
    double dx = x.first - y.first;
    double dy = x.second - y.second;
    return static_cast<uint64_t>(std::round(std::sqrt(dx * dx + dy * dy)));
}

uint64_t permutation_distance(const point_list &pm, const permutation &perm) {
    if (perm.empty()) return 0;
    uint64_t cumulative_dist = 0;
    for (std::size_t j = 0; j < perm.size() - 1; ++j) {
        cumulative_dist += euclidean(pm[perm[j]], pm[perm[j + 1]]);
    }
    cumulative_dist += euclidean(pm[perm.back()], pm[perm[0]]);
    return cumulative_dist;
}

bool local_search_randomized(const Graph &g, permutation &perm,
                                    uint64_t &current_dist, size_t max_tries,
                                    std::mt19937 &gen, uint64_t &steps) {
    bool improved = false;
    std::uniform_int_distribution<size_t> dist_indices(1, perm.size() - 1);

    for (size_t k = 0; k < max_tries; ++k) {
        size_t i = dist_indices(gen);
        size_t j = dist_indices(gen);
        if (i > j) std::swap(i, j);
        if (j - i < 1) continue;

        size_t a = (i > 0) ? perm[i - 1] : perm[perm.size() - 1];
        size_t b = perm[i];
        size_t c = perm[j];
        size_t d = (j < perm.size() - 1) ? perm[j + 1] : perm[0];

        double old_edges = g.adjacency_matrix[a][b] + g.adjacency_matrix[c][d];
        double new_edges = g.adjacency_matrix[a][c] + g.adjacency_matrix[b][d];

        if (new_edges < old_edges) {
            ++steps;
            std::reverse(perm.begin() + i, perm.begin() + j + 1);
            current_dist -= static_cast<uint64_t>(old_edges - new_edges);
            improved = true;
        }
    }
    return improved;
}

int main() {
    for (std::string_view filename : files) {
        point_list points = {};
        permutation base_perm = {}; // Shared template
        std::ifstream infile(folder + std::string{filename});
        std::string line;
        bool read = false;

        while (std::getline(infile, line)) {
            if (line.starts_with(match)) { read = true; continue; }
            if (!read || line.empty() || line.starts_with("EOF")) continue;

            std::istringstream iss(line);
            std::size_t dummy_idx;
            double x, y;
            if (iss >> dummy_idx >> x >> y) {
                base_perm.push_back(points.size());
                points.push_back({x, y});
            }
        }

        size_t n = points.size();
        if (n == 0) continue;

        Graph full_graph(n);
        for (size_t i = 0; i < n; ++i) {
            for (size_t j = i + 1; j < n; ++j) {
                double d = euclidean(points[i], points[j]);
                full_graph.adjacency_matrix[i][j] = d;
                full_graph.adjacency_matrix[j][i] = d;
            }
        }

        permutation global_best_perm;
        uint64_t global_best_distance = std::numeric_limits<uint64_t>::max();
        std::vector<uint64_t> all_distances;
        std::vector<size_t> all_step_counts;

        std::println("File: {}", filename);

std::atomic<int> progress{0};
int total_iterations = n;

#pragma omp parallel
{
    std::mt19937 thread_gen(std::random_device{}() ^ omp_get_thread_num());
    
    #pragma omp for
    for (std::size_t i = 0; i < n; ++i) {
        permutation local_perm = base_perm;
        std::shuffle(local_perm.begin(), local_perm.end(), thread_gen);
        uint64_t cur_dist = permutation_distance(points, local_perm);
        size_t step_count = 0;

        while (local_search_randomized(full_graph, local_perm, cur_dist, n, thread_gen,step_count)) {}

        #pragma omp critical
        {
            all_distances.push_back(cur_dist);
            all_step_counts.push_back(step_count);
            if (cur_dist < global_best_distance) {
                global_best_distance = cur_dist;
                global_best_perm = local_perm;
            }
        }
        // Progress Bar Update
        int current_val = ++progress;
        if (omp_get_thread_num() == 0 || current_val == total_iterations) {
            float percentage = static_cast<float>(current_val) / total_iterations;
            int width = 40;
            int pos = static_cast<int>(width * percentage);

            std::printf("\r[");
            for (int b = 0; b < width; ++b) {
                if (b < pos) std::printf("=");
                else if (b == pos) std::printf(">");
                else std::printf(" ");
            }
            std::printf( "] %d%% (%d/%d)", static_cast<int>(percentage * 100.0), current_val, total_iterations);
            std::fflush(stdout);
        }
    }
}
std::printf("\n");
        double avg_distance = std::accumulate(all_distances.begin(), all_distances.end(), 0.0) / all_distances.size();
        double avg_step = std::accumulate(all_step_counts.begin(), all_step_counts.end(), 0.0) / all_step_counts.size();

        std::println("mean_distance;mean_step;best_distance");
        std::println("{:.2f};{:.2f};{}", avg_distance, avg_step, global_best_distance);

        for (std::size_t v : global_best_perm) {
            std::println("{};{};{}", v + 1, points[v].first, points[v].second);
        }
        std::fflush(stdout);
    }
    return 0;
}