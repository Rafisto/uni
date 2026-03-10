#include <limits>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <print>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <random>
#include <numeric>

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
    
    for(std::string_view filename : files) {
        std::vector<std::size_t> perm = {};
        std::unordered_map<std::size_t,std::pair<double,double>> points;
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

        std::vector<double> distances = {};
        std::vector<size_t> best_effort;
        double min_dist = std::numeric_limits<double>::max();
        for (std::size_t i = 0; i < perm_count; ++i) {
            std::random_device rd;
            std::mt19937 g(rd());
            std::shuffle(perm.begin(), perm.end(), g);
            
            double cumulative_dist = 0;
            for (std::size_t j = 0; j < perm.size() - 1; ++j) {
                double dist = euclidean(points[perm[j]], points[perm[j+1]]);
                cumulative_dist += dist;
            }

            if (cumulative_dist < min_dist) 
            {
                min_dist = cumulative_dist;
                best_effort = std::vector<size_t>(perm);
            }

            distances.push_back(cumulative_dist);            
        }

        std::vector<double> min10 = {};
        std::vector<double> min50 = {};
        for (std::size_t i = 1; i < distances.size(); ++i) {
            if (i % 10 == 0) {
                double min_el = *std::min_element(distances.begin() + i - 10 - 1, distances.begin() + i);
                min10.push_back(min_el);
            }
            if (i % 50 == 0) {
                double min_el = *std::min_element(distances.begin() + i - 50 - 1, distances.begin() + i);
                min50.push_back(min_el);
            }
        }

        double sum10 = std::accumulate(min10.begin(), min10.end(), 0.0);
        double mean10 = sum10 / min10.size();

        double sum50 = std::accumulate(min50.begin(), min50.end(), 0.0);
        double mean50 = sum50 / min50.size();

        std::println("({}) min={}, mean_min10={}, mean_min50={}", filename, min_dist, mean10, mean50);
        for (std::size_t v : best_effort) {
            std::println("{};{};{}", v,points[v].first,points[v].second);
        }
    }
}