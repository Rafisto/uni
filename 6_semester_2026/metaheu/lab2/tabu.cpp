#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>
#include <random>
#include <chrono>
#include <print>

#include "graph.hpp"
#include "tsp_utils.hpp"
#include "tabu.hpp"

typedef std::pair<double, double> point;

double euclidean(point x, point y) {
    return std::sqrt((x.first - y.first) * (x.first - y.first) + (x.second - y.second) * (x.second - y.second));
}

constexpr const char *folder = "data/";
constexpr const char *match = "NODE_COORD_SECTION";
constexpr const char *files[] = {
    "western_sahara.tsp", "djibouti.tsp", "qatar.tsp", "uruguay.tsp",
    "zimbabwe.tsp", "oman.tsp", "canada.tsp", "tanzania.tsp", 
    "egypt.tsp", "ireland.tsp"};

int main() {
    for (const std::string& filename : files) {
        std::vector<point> coords;
        std::ifstream infile(folder + filename);
        std::string line;
        bool read_section = false;

        while (std::getline(infile, line)) {
            if (line.starts_with(match)) {
                read_section = true;
                continue;
            }
            if (!read_section || line.empty() || line.starts_with("EOF")) continue;
            
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
        double sum_costs = 0;

        const size_t iter = 100;

        for (size_t i = 0; i < iter; ++i) {
            auto tour = tabu_search(g, 200, 100); 
            double cost = calculate_tour_cost(g, tour);
            sum_costs += cost;
            if (cost < best_overall) best_overall = cost;
        }

        std::println("File: {} | TS Best: {} | TS Avg: {}", filename, best_overall, sum_costs / iter);
    }
    return 0;
}