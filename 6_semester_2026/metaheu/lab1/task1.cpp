#include <cstdio>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <random>
#include <print>

constexpr const char* folder = "data/";
constexpr const char* match = "NODE_COORD_SECTION";
constexpr const char* files[] = {
    // list 0
    "western_sahara.tsp",
    "djibouti.tsp",
    "qatar.tsp",
    "uruguay.tsp",
    "zimbabwe.tsp",
    // list 1
    "oman.tsp",
    "canada.tsp",
    "tanzania.tsp",
    "egypt.tsp",
    "ireland.tsp"
};

typedef std::pair<double,double> point;
typedef std::unordered_map<std::size_t,point> point_map;
typedef std::vector<std::size_t> permutation;

uint64_t euclidean(const point x, const point y) {
    double dx = x.first - y.first;
    double dy = x.second - y.second;
    return static_cast<uint64_t>(std::round(std::sqrt(dx*dx + dy*dy)));
}

inline uint64_t permutation_distance(const point_map pm, const permutation perm) {
    if (perm.empty()) return 0;   
    uint64_t cumulative_dist = 0;
    for (std::size_t j = 0; j < perm.size() - 1; ++j) {
        cumulative_dist += euclidean(pm.at(perm[j]), pm.at(perm[j+1]));
    }
    cumulative_dist += euclidean(pm.at(perm.back()), pm.at(perm.front()));  
    return cumulative_dist;
}

inline uint64_t local_search(const point_map pm, permutation &perm, uint64_t current_dist) {
    size_t n = perm.size();
    bool improved = true;

    while (improved) {
        improved = false;
        for (size_t i = 1; i < n - 1; ++i) {
            for (size_t j = i + 1; j < n; ++j) {
                const point& a = pm.at(perm[i - 1]);
                const point& b = pm.at(perm[i]);
                const point& c = pm.at(perm[j]);
                const point& d = pm.at(perm[(j + 1) % n]);

                double delta = (euclidean(a, c) + euclidean(b, d)) - 
                               (euclidean(a, b) + euclidean(c, d));

                if (delta < -1e-9) { 
                    std::reverse(perm.begin() + i, perm.begin() + j + 1);
                    current_dist += delta;
                    improved = true;
                }
            }
        }
    }
    return current_dist;
}

int main() {
    for(std::string_view filename : files) {
        permutation perm = {};
        point_map points;
        std::ifstream infile(folder+std::string{filename});
        std::string line;
        bool read = false;

        while (std::getline(infile, line))
        {
            std::istringstream iss(line);
            std::string line = iss.str();
            if (line.starts_with(match)) {
                read = true;
                continue;
            }
            if (not read) continue;
            std::size_t idx;
            double x,y;
            iss >> idx >> x >> y;

            perm.push_back(idx);
            points[idx] = std::make_pair(x,y);
        }

        std::random_device rd;
        std::mt19937 g(rd());

        permutation best_perm = perm;
        std::vector<uint64_t> distances = {};
        std::vector<size_t> step_counts = {};
        uint64_t best_distance = permutation_distance(points, perm);
        std::println("File: {}", filename);

        for (std::size_t i = 0; i < perm.size(); ++i) {
            std::shuffle(perm.begin(), perm.end(), g);
            uint64_t dist, new_dist;
            uint64_t step_count = 0;
            do {
                ++step_count;
                dist = permutation_distance(points, perm);
                new_dist = local_search(points, perm, dist);
            } while (dist != new_dist);

            distances.push_back(dist);
            step_counts.push_back(step_count);
            if(dist < best_distance) {
                best_distance = dist;
                best_perm = perm;
            }
        }

        // avg distance
        double avg_distance = std::accumulate(distances.begin(), distances.end(), 0.0) / distances.size();
        double avg_step = std::accumulate(step_counts.begin(), step_counts.end(), 0.0) / step_counts.size();
        std::println("mean_distance;mean_step;best_distance");
        std::println("{};{};{}", avg_distance, avg_step, best_distance);


        for (size_t v = 1; v <= best_perm.size(); ++v) {
            std::println("{};{};{}", v, points.at(best_perm[v-1]).first, points.at(best_perm[v-1]).second);
        }
    }
}
