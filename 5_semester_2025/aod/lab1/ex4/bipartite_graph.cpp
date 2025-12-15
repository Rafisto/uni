#include "graph.hpp"

#include <chrono>
#include <fstream>
#include <iostream>
#include <sys/types.h>

#include <queue>

namespace {
// Try to color using bfs or fail and return an odd-length cycle
// https://en.wikipedia.org/wiki/Bipartite_graph#Testing_bipartiteness
bool bipartite_bfs(const Graph &g) {
    std::vector<short> color(g.size(), -1);
    std::queue<std::size_t> q;

    for (std::size_t start = 1; start < g.size(); ++start) {
        if (color[start] != -1)
            continue;

        color[start] = 0;
        q.push(start);

        while (not q.empty()) {
            size_t u = q.front();
            q.pop();

            for (std::size_t v : adjacent(g, u)) {
                if (color[v] == -1) {
                    color[v] = 1 - color[u];
                    q.push(v);
                } else if (color[v] == color[u]) {
                    std::cout << "Graph is not bipartite\n";
                    return false;
                }
            }
        }
    }

    std::cout << "Graph is bipartite\n";
    if (g.size() <= 200) {
        std::vector<std::size_t> red;
        std::vector<std::size_t> black;
        for (std::size_t v = 1; v < g.size(); ++v) {
            if (color[v] == 0) {
                red.push_back(v);
            } else {
                black.push_back(v);
            }
        }
        std::cout << "Red: { ";
        for (const auto &v : red) {
            std::cout << v << " ";
        }
        std::cout << "}\nBlack: { ";
        for (const auto &v : black) {
            std::cout << v << " ";
        }
        std::cout << "}\n";
    }

    return true;
}
} // namespace

int main(const int argc, const char *const argv[]) {
    if (argc != 2) {
        std::cout << "Usage " << argv[0] << " [filename]" << std::endl;
        return 1;
    }

    std::string filename = argv[1];
    std::ifstream file(filename);

    std::cout << "File: " << filename << ":";

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
    bipartite_bfs(g);
    auto stop = std::chrono::steady_clock::now();

    auto duration_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start).count();
    auto duration_ms = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start).count();
    auto duration_s = std::chrono::duration_cast<std::chrono::seconds>(stop - start).count();

    std::cout << "Time: " << duration_ns << " ns (" 
              << duration_ms << " ms, " 
              << duration_s << " s)\n";

    return 0;
}