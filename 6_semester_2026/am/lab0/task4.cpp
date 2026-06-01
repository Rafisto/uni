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

constexpr std::size_t perm_count = 1000;

typedef std::pair<double,double> point;

double euclidean(point x, point y) {
    return std::sqrt((x.first - y.first) * (x.first - y.first) + (x.second - y.second) * (x.second - y.second));
}

int main() {
    for (std::string_view filename : files) {
        std::vector<std::size_t> node_ids;
        std::unordered_map<std::size_t, point> points;
        std::ifstream infile(folder + std::string{filename});
        
        if (!infile) continue;

        std::string line;
        bool read = false;
        while (std::getline(infile, line)) {
            if (line.starts_with(match)) { read = true; continue; }
            if (!read || line.starts_with("EOF")) continue;
            
            std::istringstream iss(line);
            std::size_t idx; double x, y;
            if (iss >> idx >> x >> y) {
                node_ids.push_back(idx);
                points[idx] = {x, y};
            }
        }

        size_t n = node_ids.size();
        Graph full_graph(n);

        for (size_t i = 0; i < n; ++i) {
            for (size_t j = i + 1; j < n; ++j) {
                double d = euclidean(points[node_ids[i]], points[node_ids[j]]);
                full_graph.adjacency_matrix[i][j] = d;
                full_graph.adjacency_matrix[j][i] = d;
            }
        }

        auto [mst, mst_weight] = kruskal(full_graph);

        std::vector<size_t> tour_indices = mst.get_dfs_tour();
        
        double tour_weight = 0;
        for (size_t i = 0; i < tour_indices.size(); ++i) {
            size_t u = tour_indices[i];
            size_t v = tour_indices[(i + 1) % tour_indices.size()];
            tour_weight += euclidean(points[node_ids[u]], points[node_ids[v]]);
        }

        std::println("({}) total_weight={}, mst_weight={}, ratio={:.2f}", filename, tour_weight, mst_weight, tour_weight/mst_weight);
        std::println(stderr, "({}) total_weight={}, mst_weight={}, ratio={:.2f}", filename, tour_weight, mst_weight, tour_weight/mst_weight);
  
        
        for (size_t idx : tour_indices) {
            size_t original_id = node_ids[idx];
            std::println("{};{};{}", original_id, points[original_id].first, points[original_id].second);
        }
        size_t first_id = node_ids[tour_indices[0]];
        std::println("{};{};{}", first_id, points[first_id].first, points[first_id].second);
    }
    return 0;
}
