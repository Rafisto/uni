#include <cstdio>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <random>
#include <print>

constexpr const char* folder = "data/";
constexpr const char* match = "NODE_COORD_SECTION";
constexpr const char* files[] = {
    // lab 0
    "western_sahara.tsp",
    "djibouti.tsp",
    "qatar.tsp",
    "uruguay.tsp",
    "zimbabwe.tsp",
    // lab 1
    "oman.tsp",
    "canada.tsp",
    "tanzania.tsp",
    "egypt.tsp",
    "ireland.tsp"
};

typedef std::pair<double,double> point;
typedef std::vector<point> point_list;
typedef std::vector<std::size_t> permutation;

uint64_t euclidean(const point x, const point y) {
    double dx = x.first - y.first;
    double dy = x.second - y.second;
    return static_cast<uint64_t>(std::round(std::sqrt(dx*dx + dy*dy)));
}

inline uint64_t permutation_distance(const point_list pm, const permutation perm) {
    if (perm.empty()) return 0;   
    uint64_t cumulative_dist = 0;
    for (std::size_t j = 0; j < perm.size() - 1; ++j) {
        cumulative_dist += euclidean(pm[perm[j]], pm[perm[j+1]]);
    }
    cumulative_dist += euclidean(pm[perm.back()], pm[perm.front()+1]);
    return cumulative_dist;
}

inline uint64_t partial_permutation_distance(const point_list pm, const permutation perm, std::size_t i, std::size_t j) {
    std::size_t n = perm.size();
    point a = pm[perm[(i + n - 1) % n]];
    point b = pm[perm[i]];
    point c = pm[perm[j]];
    point d = pm[perm[(j + 1) % n]];

    return (euclidean(a, c) + euclidean(b, d)) - (euclidean(a, b) + euclidean(c, d));
}

inline bool local_search_randomized(const point_list points, permutation &perm, uint64_t distance) {
    size_t n = perm.size();
    bool improved = false;

    std::vector<std::pair<size_t, size_t>> pairs;
    for (size_t i = 1; i < n - 1; ++i) {
        for (size_t j = i + 1; j < n; ++j) {
            pairs.emplace_back(i, j);
        }
    }

    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(pairs.begin(), pairs.end(), g);

    std::vector<std::pair<size_t, size_t>> selected_pairs(pairs.begin(), pairs.begin() + std::min(n, pairs.size()));

    for (auto p : selected_pairs) {
        size_t i = p.first;
        size_t j = p.second;
        size_t a_idx = perm[i - 1];
        size_t b_idx = perm[i];
        size_t c_idx = perm[j];
        size_t d_idx = perm[(j + 1) % n];

        int64_t current_edges = euclidean(points[a_idx], points[b_idx]) + euclidean(points[c_idx], points[d_idx]);
        int64_t new_edges = euclidean(points[a_idx], points[c_idx]) + euclidean(points[b_idx], points[d_idx]);

        if (new_edges < current_edges) {
            std::reverse(perm.begin() + i, perm.begin() + j + 1);
            distance -= (current_edges - new_edges);
            improved = true;
        }
    }

    return improved;
}

int main() {
    for(std::string_view filename : files) {
        permutation perm = {};
        point_list points;
        points.resize(10000);
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
        points.shrink_to_fit();

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
            while(local_search_randomized(points, perm, dist)) {
                ++step_count;
                dist = permutation_distance(points, perm);
            }
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


        for (std::size_t v : best_perm) {
            std::println("{};{};{}", v,points[v].first,points[v].second);
        }
        std::fflush(stdout);
    }
}
