#include "graph.hpp"

#include <chrono>
#include <fstream>
#include <iostream>
#include <stdexcept>

#include <algorithm>
#include <stack>

namespace {
void dfs(const Graph &g, std::size_t vertex, std::vector<bool> &visited,
         std::stack<std::size_t> &stack, std::vector<std::size_t> path) {
    path.push_back(vertex);
    visited[vertex] = true;

    for (std::size_t w : adjacent(g, vertex)) {
        if (std::find(path.begin(), path.end(), w) != path.end()) {
            if (g.size() <= 200) {
                std::cout << "path: ";
                for (std::size_t p : path) {
                    std::cout << p << " ";
                }
                std::cout << "and now " << w << "." << std::endl;
            }

            throw std::runtime_error{"cycle has been found"};
        }
        if (not visited[w]) {
            dfs(g, w, visited, stack, path);
        }
    }

    stack.push(vertex);
}

void topological_sort(const Graph &g) {
    std::vector<bool> visited(g.size() + 1, false);
    std::stack<std::size_t> stack;

    for (std::size_t i = 1; i < g.size(); ++i) {
        std::vector<std::size_t> path = {};
        if (not visited[i]) {
            dfs(g, i, visited, stack, path);
        }
    }

    std::cout << "graph is acyclic." << std::endl;

    if (g.size() <= 200) {
        while (not stack.empty()) {
            std::size_t c = stack.top();
            std::cout << c << " ";
            stack.pop();
        }
        std::cout << std::endl;
    }
}
} // namespace

int main(const int argc, const char *const argv[]) {
    if (argc != 2) {
        std::cout << "Usage " << argv[0] << " [filename]" << std::endl;
        return 1;
    }

    std::string filename = argv[1];
    std::ifstream file(filename);

    std::cout << "File: " << filename << ": ";

    char d;
    std::size_t e_count;
    std::size_t v_count;

    file >> d;
    file >> v_count;
    file >> e_count;

    Graph g(v_count + 1);

    bool directed = d == 'D';

    std::size_t count = 0;
    while (1) {
        std::size_t v, w;
        file >> v >> w;
        if (file.eof())
            break;
        g[v].push_back(w);
        if (not directed)
            g[w].push_back(v);
        ++count;
    }

    if (count != e_count) {
        std::cout << "edge count improper " << count << "!=" << e_count
                  << std::endl;
        return 1;
    }

    auto start = std::chrono::steady_clock::now();
    try {
        topological_sort(g);

    } catch (const std::runtime_error &e) {
        std::cout << e.what() << "\n";
    }

    auto stop = std::chrono::steady_clock::now();

    auto duration_ns =
        std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start)
            .count();
    auto duration_ms =
        std::chrono::duration_cast<std::chrono::milliseconds>(stop - start)
            .count();
    auto duration_s =
        std::chrono::duration_cast<std::chrono::seconds>(stop - start).count();

    std::cout << "Time: " << duration_ns << " ns (" << duration_ms << " ms, "
              << duration_s << " s)\n";

    return 0;
}