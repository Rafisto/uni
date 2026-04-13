#include <algorithm>
#include <atomic>
#include <cmath>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <numeric>
#include <omp.h>
#include <print>
#include <random>
#include <sstream>
#include <string>
#include <vector>

#include "graph.hpp"
#include "kruskal.hpp"

constexpr const char *folder = "data/";
constexpr const char *match = "NODE_COORD_SECTION";
constexpr const char *files[] = {
    // Lab 0
    "western_sahara.tsp", "djibouti.tsp", "qatar.tsp", "uruguay.tsp",
    "zimbabwe.tsp",
    // Lab 1
    "oman.tsp", "canada.tsp", "tanzania.tsp", "egypt.tsp", "ireland.tsp"};

typedef std::pair<double, double> point;
typedef std::vector<point> point_list;
typedef std::vector<std::size_t> permutation;

inline uint64_t euclidean(const point x, const point y) {
  double dx = x.first - y.first;
  double dy = x.second - y.second;
  return static_cast<uint64_t>(std::round(std::sqrt(dx * dx + dy * dy)));
}

inline uint64_t permutation_distance(const point_list &pm,
                                     const permutation &perm) {
  if (perm.empty())
    return 0;
  uint64_t cumulative_dist = 0;
  for (std::size_t j = 0; j < perm.size() - 1; ++j) {
    cumulative_dist += euclidean(pm[perm[j]], pm[perm[j + 1]]);
  }
  cumulative_dist += euclidean(pm[perm.back()], pm[perm[0]]);
  return cumulative_dist;
}

bool local_search(const Graph &g, permutation &perm, uint64_t &current_dist) {
  size_t n = perm.size();
  for (size_t i = 1; i < n; ++i) {
    for (size_t j = i + 1; j < n - 1; ++j) {
      size_t a = perm[i - 1];
      size_t b = perm[i];
      size_t c = perm[j];
      size_t d = perm[(j + 1) % n];

      double old_edges = g.adjacency_matrix[a][b] + g.adjacency_matrix[c][d];
      double new_edges = g.adjacency_matrix[a][c] + g.adjacency_matrix[b][d];

      if (new_edges < old_edges) {
        std::reverse(perm.begin() + i, perm.begin() + j + 1);
        current_dist -= static_cast<uint64_t>(old_edges - new_edges);
        return true;
      }
    }
  }
  return false;
}

int main() {
  for (std::string_view filename : files) {
    std::vector<std::size_t> node_ids;
    point_list points(10000);
    std::ifstream infile(folder + std::string{filename});
    if (!infile)
      continue;

    std::string line;
    bool read = false;
    while (std::getline(infile, line)) {
      if (line.starts_with(match)) {
        read = true;
        continue;
      }
      if (!read || line.empty() || line.starts_with("EOF"))
        continue;
      std::istringstream iss(line);
      std::size_t idx;
      double x, y;
      if (iss >> idx >> x >> y) {
        node_ids.push_back(idx);
        points[idx] = {x, y};
      }
    }

    size_t n = node_ids.size();
    if (n == 0)
      continue;
    Graph full_graph(n);

    for (size_t i = 0; i < n; ++i) {
      for (size_t j = i + 1; j < n; ++j) {
        double d = euclidean(points[node_ids[i]], points[node_ids[j]]);
        full_graph.adjacency_matrix[i][j] = d;
        full_graph.adjacency_matrix[j][i] = d;
      }
    }

    Graph mst;
    double mst_res;
    std::tie(mst,mst_res) = kruskal(full_graph);

    permutation global_best_perm;
    uint64_t global_best_distance = std::numeric_limits<uint64_t>::max();
    std::vector<uint64_t> all_distances;
    std::vector<size_t> all_step_counts;
    std::atomic<int> progress{0};

    std::println("File: {}", filename);
    std::println("MST weight: {}", mst_res);

#pragma omp parallel
    {
      std::mt19937 thread_gen(std::random_device{}() ^ omp_get_thread_num());

#pragma omp for
      for (int i = 0; i < (int)n; ++i) {
        uint64_t starting_node = thread_gen() % n;
        permutation local_perm = mst.get_dfs_tour(starting_node);
        uint64_t dist = permutation_distance(points, local_perm);
        size_t step_count = 0;

        while (local_search(full_graph, local_perm, dist)) {
          ++step_count;
        }

#pragma omp critical
        {
          all_distances.push_back(dist);
          all_step_counts.push_back(step_count);
          if (dist < global_best_distance) {
            global_best_distance = dist;
            global_best_perm = local_perm;
          }
        }

        // Progress Bar
        int current_val = ++progress;
        if (omp_get_thread_num() == 0 || current_val == (int)n) {
          float percentage = static_cast<float>(current_val) / n;
          int width = 30;
          int pos = width * percentage;
          std::printf("\rProgress: [");
          for (int b = 0; b < width; ++b) {
            if (b < pos)
              std::printf("=");
            else if (b == pos)
              std::printf(">");
            else
              std::printf(" ");
          }
          std::printf("] %d%%", static_cast<int>(percentage * 100));
          std::fflush(stdout);
        }
      }
    }
    std::printf("\n");

    double avg_distance =
        std::accumulate(all_distances.begin(), all_distances.end(), 0.0) /
        all_distances.size();
    double avg_step =
        std::accumulate(all_step_counts.begin(), all_step_counts.end(), 0.0) /
        all_step_counts.size();

    std::println("mean_distance;mean_step;best_distance");
    std::println("{:.2f};{:.2f};{}", avg_distance, avg_step,
                 global_best_distance);

    for (std::size_t v : global_best_perm) {
      std::println("{};{};{}", v, points[v].first, points[v].second);
    }
    std::fflush(stdout);
  }
  return 0;
}