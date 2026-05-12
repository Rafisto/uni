#include <cmath>
#include <fstream>
#include <iostream>
#include <print>
#include <sstream>
#include <string>
#include <vector>

#include "graph.hpp"
#include "tabu.hpp"
#include "tsp_utils.hpp"
typedef std::pair<double, double> point;

double euclidean(point x, point y) {
  return std::sqrt((x.first - y.first) * (x.first - y.first) +
                   (x.second - y.second) * (x.second - y.second));
}

constexpr const char *filepath = "data/qatar.tsp";
constexpr const char *match = "NODE_COORD_SECTION";

struct Parameters {
  size_t max_iterations;
  size_t tabu_size;
};

int main() {
  std::vector<point> coords;
  std::ifstream infile(filepath);
  std::string line;
  bool read_section = false;

  while (std::getline(infile, line)) {
    if (line.starts_with(match)) {
      read_section = true;
      continue;
    }

    if (!read_section || line.empty() || line.starts_with("EOF"))
      continue;

    std::istringstream iss(line);

    size_t idx;
    double x, y;

    if (iss >> idx >> x >> y) {
      coords.push_back({x, y});
    }
  }

  size_t n = coords.size();

  Graph g;
  g.n = n;
  g.adjacency_matrix = AdjacencyMatrix(n, std::vector<double>(n, 0.0));

  for (size_t i = 0; i < n; ++i) {
    for (size_t j = i + 1; j < n; ++j) {
      double dist = euclidean(coords[i], coords[j]);
      g.adjacency_matrix[i][j] = g.adjacency_matrix[j][i] = dist;
    }
  }

  double best_overall = std::numeric_limits<double>::max();

  std::vector<std::size_t> max_iter = {10, 20, 50, 100, 200};
  std::vector<std::size_t> tabu_size = {g.n / 10, g.n / 4, g.n / 2, g.n * 3 / 4, g.n};

  auto test = std::ranges::views::cartesian_product(max_iter, tabu_size);
  const size_t iter = 5;
  Parameters best_params;

  for (const auto& [max_it, tabu_s] : test) {
    std::println("Testing Max Iterations: {}, Tabu Size: {}", max_it, tabu_s);
    double best_case_cost = std::numeric_limits<double>::max();

    for (size_t i = 0; i < iter; ++i) {
      auto tour = tabu_search(g, max_it, tabu_s);
      double cost = calculate_tour_cost(g, tour);
      if (cost < best_case_cost)
        best_case_cost = cost;
    }

    if (best_case_cost < best_overall) {
      best_overall = best_case_cost;
      best_params.max_iterations = max_it;
      best_params.tabu_size = tabu_s;
    }
  }

  for (size_t i = 0; i < iter; ++i) {
    auto tour = tabu_search(g, 20, g.n / 4);
    double cost = calculate_tour_cost(g, tour);
    if (cost < best_overall)
      best_overall = cost;
  }

  std::println("\n================ BEST PARAMETERS ================");
  std::println("Max Iterations     : {}", best_params.max_iterations);
  std::println("Tabu Size           : {}", best_params.tabu_size);
  return 0;
}