#include "graph.hpp"

#include <chrono>
#include <cstring>
#include <fstream>
#include <functional>
#include <iostream>
#include <queue>
#include <stack>

namespace {

void bfs(const Graph &g, bool print_tree) noexcept {
    std::vector<bool> visited(g.size() + 1, false);
    std::queue<std::pair<std::size_t, std::size_t>> queue;
    std::vector<std::size_t> order;

    visited[1] = true;
    queue.push(std::make_pair(1, 0));
    while (not queue.empty()) {
        std::size_t v = queue.front().first;
        std::size_t d = queue.front().second;
        queue.pop();

        if (print_tree) {
            for (std::size_t s = 1; s < d; ++s) {
                std::cout << "   ";
            }
            if (d > 0)
                std::cout << "|- ";
            std::cout << v << "\n";
        }

        order.push_back(v);

        for (std::size_t w : adjacent(g, v)) {
            if (not visited[w]) {
                visited[w] = true;
                queue.push(std::make_pair(w, d + 1));
            }
        }
    }

    std::cout << "Traversal: ";

    for (auto v : order) {
        std::cout << v << " ";
    }

    std::cout << "\n";
}

void dfs(const Graph &g, bool print_tree) noexcept {
    std::vector<bool> visited(g.size() + 1, false);
    std::stack<std::pair<std::size_t, std::size_t>> stack;
    std::vector<std::size_t> order;

    if (print_tree)
        std::cout << "DFS Tree:\n";

    for (std::size_t node = 1; node < g.size(); ++node) {
        if (visited[node])
            continue;

        stack.push(std::make_pair(node, 0));
        while (not stack.empty()) {
            std::size_t v = stack.top().first;
            std::size_t d = stack.top().second;
            stack.pop();
            if (not visited[v]) {
                visited[v] = true;

                if (print_tree) {
                    for (std::size_t s = 1; s < d; ++s) {
                        std::cout << "   ";
                    }
                    if (d > 0)
                        std::cout << "|- ";
                    std::cout << v << "\n";
                }

                order.push_back(v);

                for (std::size_t w : adjacent(g, v)) {
                    if (not visited[w]) {
                        stack.push(std::make_pair(w, d + 1));
                    }
                }
            }
        }
    }

    std::cout << "Traversal: ";

    for (auto v : order) {
        std::cout << v << " ";
    }

    std::cout << "\n";
}
} // namespace

int main(const int argc, const char *const argv[]) {
    if (argc < 3) {
        std::cout << "Usage " << argv[0] << " [dfs|bfs] " << "[filename]"
                  << "--tree (optional)" << std::endl;
        return 1;
    }

    std::string mode = argv[1];
    std::string filename = argv[2];
    bool tree = false;

    if (argc > 3 && std::strcmp(argv[3], "--tree") == 0) {
        tree = true;
    }

    if (not(mode == "dfs" or mode == "bfs")) {
        std::cout << "Mode must be either dfs or bfs." << std::endl;
    }

    std::ifstream file(filename);

    std::cout << "File: " << filename << ":\n";

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

    std::function<void(const Graph &g, bool tree)> traversal =
        mode == "dfs" ? dfs : bfs;

    auto start = std::chrono::steady_clock::now();
    traversal(g, tree);
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
