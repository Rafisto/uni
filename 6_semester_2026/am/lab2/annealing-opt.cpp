#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <limits>
#include <print>
#include <sstream>
#include <string>
#include <vector>

#include "annealing.hpp"
#include "graph.hpp"
#include "tsp_utils.hpp"

typedef std::pair<double, double> point;

double euclidean(point x, point y) {
  return std::sqrt((x.first - y.first) * (x.first - y.first) +
                   (x.second - y.second) * (x.second - y.second));
}

constexpr const char *filepath = "data/uruguay.tsp";
constexpr const char *match = "NODE_COORD_SECTION";

struct Parameters {
  double temperature;
  double alpha;
  size_t epochs;
  size_t tries_per_epoch;
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

  std::vector<double> temperatures = {10.0, 50.0, 100.0, 250.0, 500.0, 1000.0};
  std::vector<double> alphas = {0.90, 0.95, 0.97, 0.99, 0.995};
  std::vector<size_t> epochs_values = {100, 250, 500, 1000};
  std::vector<size_t> tries_values = {5, 10, 25, 50};

  constexpr size_t runs_per_case = 10;

  double best_cost = std::numeric_limits<double>::max();
  Parameters best_params{};

  auto experiments = std::views::cartesian_product(temperatures, alphas,
                                                   epochs_values, tries_values);

  for (const auto &[temperature, alpha, epochs, tries] : experiments) {
    double best_local = std::numeric_limits<double>::max();
    double sum_costs = 0.0;

    for (size_t run = 0; run < runs_per_case; ++run) {
      auto tour = simulated_annealing(g, temperature, alpha, epochs, tries);
      double cost = calculate_tour_cost(g, tour);
      sum_costs += cost;
      best_local = std::min(best_local, cost);
    }

    double avg_cost = sum_costs / runs_per_case;

    std::println("T={} | alpha={} | epochs={} | tries={} | best={} | avg={}",
                 temperature, alpha, epochs, tries, best_local, avg_cost);

    if (best_local < best_cost) {
      best_cost = best_local;

      best_params = {temperature, alpha, epochs, tries};
    }
  }

  std::println("\n================ BEST PARAMETERS ================");
  std::println("Temperature     : {}", best_params.temperature);
  std::println("Alpha           : {}", best_params.alpha);
  std::println("Epochs          : {}", best_params.epochs);
  std::println("Tries per epoch : {}", best_params.tries_per_epoch);
  std::println("Best cost       : {}", best_cost);

  return 0;
}
