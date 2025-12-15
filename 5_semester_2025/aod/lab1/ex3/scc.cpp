#include "graph.hpp"

#include <chrono>
#include <fstream>
#include <iostream>

#include <stack>

namespace {
// Too much creativity can be a dangerous thing
std::vector<std::size_t> post_order_dfs(const Graph &g) noexcept {
    std::vector<std::size_t> order;
    std::vector<bool> visited(g.size(), false);
    std::stack<std::pair<std::size_t, std::size_t>> st;

    for (std::size_t start = 1; start < g.size(); ++start) {
        if (visited[start])
            continue;

        st.emplace(start, 0);

        while (!st.empty()) {
            auto &[v, i] = st.top();

            if (!visited[v]) {
                visited[v] = true;
            }

            const auto &adj = g[v];

            if (i < adj.size()) {
                std::size_t u = adj[i++];
                if (!visited[u]) {
                    st.emplace(u, 0);
                }
            } else {
                order.push_back(v);
                st.pop();
            }
        }
    }

    return order;
}

Graph reverse_graph(const Graph &g) noexcept {
    Graph g_rev(g.size());

    for (std::size_t v = 1; v < g.size(); ++v) {
        for (std::size_t w : adjacent(g, v)) {
            g_rev[w].push_back(v);
        }
    }

    return g_rev;
}

Components scc_dfs(const Graph &gt,
                   const std::vector<std::size_t> &order) noexcept {
    std::vector<bool> visited(gt.size() + 1, false);
    Components components;

    for (auto it = order.rbegin(); it != order.rend(); ++it) {
        std::size_t v = *it;
        if (!visited[v]) {
            std::vector<std::size_t> component;
            std::stack<std::size_t> stack;
            stack.push(v);

            while (!stack.empty()) {
                std::size_t u = stack.top();
                stack.pop();
                if (!visited[u]) {
                    visited[u] = true;
                    component.push_back(u);
                    for (std::size_t w : adjacent(gt, u)) {
                        if (!visited[w]) {
                            stack.push(w);
                        }
                    }
                }
            }

            components.push_back(component);
        }
    }

    return components;
}

// CLRS 22.5 Strongly Connected Components p. 616-621

// 1 compute post-order vertices via dfs on G
// 2 compute G^T (reverse all edges)
// 3 compute dfs(G^T), but in the main loop of DFS, consider the vertices in
// order of decreasing post-order numbers 
// 4 output the vertices of each tree in the depth-first forest formed in 3rd point
void strongly_connected_components(const Graph &g) {
    std::vector<std::size_t> post_order = post_order_dfs(g);
    Graph g_rev = reverse_graph(g);
    Components components = scc_dfs(g_rev, post_order);

    std::cout << "SCC Count: " << components.size() << "\n";
    for (const auto &component : components) {
        std::cout << "- SCC of size " << component.size() << "\n";
        if (g.size() <= 200) {
            std::cout << "{ ";
            for (const auto &v : component) {
                std::cout << v << " ";
            }
            std::cout << "}\n";
        }
    }
}
} // namespace

int main(const int argc, const char *const argv[]) {
    if (argc != 2) {
        std::cout << "Usage " << argv[0] << " [filename]\n";
        return 1;
    }

    std::string filename = argv[1];
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
        std::cout << "edge count improper " << count << "!=" << e_count << "\n";
        return 1;
    }

    auto start = std::chrono::steady_clock::now();
    strongly_connected_components(g);
    auto stop = std::chrono::steady_clock::now();

    auto duration_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start).count();
    auto duration_ms = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start).count();
    auto duration_s = std::chrono::duration_cast<std::chrono::seconds>(stop - start).count();

    std::cout << "Time: " << duration_ns << " ns (" 
              << duration_ms << " ms, " 
              << duration_s << " s)\n";

    return 0;
}