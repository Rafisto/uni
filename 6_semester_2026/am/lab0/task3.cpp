#include <limits>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <print>
#include <vector>
#include <unordered_map>
#include <cmath>

#include "kruskal.hpp"

constexpr const char* folder = "data/";
constexpr const char* match = "NODE_COORD_SECTION";
constexpr const char* files[] = {
    "western_sahara.tsp",
    "djibouti.tsp",
    "qatar.tsp",
    "uruguay.tsp",
    "zimbabwe.tsp"
};

typedef std::pair<double,double> point;

double euclidean(point x, point y) {
    return std::sqrt((x.first - y.first) * (x.first - y.first) + (x.second - y.second) * (x.second - y.second));
}

int main() {
    for(std::string_view filename : files) {
        std::vector<std::size_t> node_ids = {};
        std::unordered_map<std::size_t, point> points;
        std::ifstream infile(folder + std::string{filename});
        
        if (!infile.is_open()) {
            std::println(stderr, "Error: Could not open {}", filename);
            continue;
        }

        std::string line;
        bool read = false;
        while (std::getline(infile, line)) {
            if (line.starts_with(match)) {
                read = true;
                continue;
            }
            if (line.starts_with("EOF")) break;
            if (!read) continue;

            std::istringstream iss(line);
            std::size_t idx;
            double x, y;
            if (!(iss >> idx >> x >> y)) continue;

            node_ids.push_back(idx);
            points[idx] = {x, y};
        }

        size_t n = node_ids.size();
        Graph g(n);
        std::unordered_map<std::size_t, size_t> id_to_idx;
        for(size_t i = 0; i < n; ++i) id_to_idx[node_ids[i]] = i;

        g.adjacency_matrix = AdjacencyMatrix(n, std::vector<double>(n, 0.0));
        for (size_t i = 0; i < n; ++i) {
            for (size_t j = i + 1; j < n; ++j) {
                double dist = euclidean(points[node_ids[i]], points[node_ids[j]]);
                g.adjacency_matrix[i][j] = dist;
                g.adjacency_matrix[j][i] = dist;
            }
        }

        auto [mst_graph, mst_weight] = kruskal(g);

        std::println("file={} n={} mst_weight={:.2f}", filename, n, mst_weight);
    }
    return 0;
}
