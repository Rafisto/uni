#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <utility>
#include <random>
#include <climits>

#include "graph.hpp"
#include "prims.hpp"

const int MAXN = 100005;

std::vector<int> tree[MAXN];
std::vector<int> informOrder[MAXN];
int minRounds[MAXN];

void dfs(int v, int parent) {
    std::vector<std::pair<int, int>> childTimes;

    for (int child : tree[v]) {
        if (child == parent) continue;
        dfs(child, v);
        childTimes.push_back({minRounds[child], child});
    }

    std::sort(childTimes.rbegin(), childTimes.rend());

    int maxTime = 0;
    for (size_t i = 0; i < childTimes.size(); ++i) {
        int t = childTimes[i].first;
        int child = childTimes[i].second;
        informOrder[v].push_back(child);
        maxTime = std::max(maxTime, t + static_cast<int>(i) + 1);
    }

    minRounds[v] = maxTime;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <number_of_vertices>" << std::endl;
        return 1;
    }

    size_t n = std::stoul(argv[1]);
    if (n <= 1) {
        std::cerr << "Number of vertices must be greater than 1." << std::endl;
        return 1;
    }

    std::fill(minRounds, minRounds + MAXN, 0);

    Graph g(n);
    auto [mst, totalCost] = prims(g);

    for (size_t i = 0; i < n; ++i) {
        for (size_t j = i + 1; j < n; ++j) {
            if (mst.adjacency_matrix[i][j] != 0.0) {
                tree[static_cast<int>(i)].push_back(static_cast<int>(j));
                tree[static_cast<int>(j)].push_back(static_cast<int>(i));
            }
        }
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, static_cast<int>(n) - 1);
    int root = dist(gen);

    dfs(root, -1);

    int maxReceive = 0;
    for (int i = 0; i < static_cast<int>(n); ++i) {
        maxReceive = std::max(maxReceive, minRounds[i]);
    }

    std::cout << "Tree size (n): " << n << std::endl;
    std::cout << "Number of rounds: " << maxReceive << std::endl;

    for (int v = 0; v < static_cast<int>(n); ++v) {
        std::cout << "Node " << v << " informs children in order: ";
        for (int child : informOrder[v]) {
            std::cout << child << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}
