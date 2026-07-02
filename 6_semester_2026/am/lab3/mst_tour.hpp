#ifndef MST_TOUR
#define MST_TOUR

#include <vector>
#include <stack>
#include <limits>

#include "graph.hpp"

inline std::vector<std::vector<size_t>> get_mst_adj_list(const Graph &g)
{
    std::vector<double> min_edge(g.n, std::numeric_limits<double>::max());
    std::vector<int> parent(g.n, -1);
    std::vector<bool> in_mst(g.n, false);
    std::vector<std::vector<size_t>> mst_adj(g.n);

    min_edge[0] = 0;
    for (size_t i = 0; i < g.n; ++i)
    {
        int u = -1;
        for (size_t v = 0; v < g.n; ++v)
        {
            if (!in_mst[v] && (u == -1 || min_edge[v] < min_edge[u]))
                u = v;
        }

        if (u == -1 || min_edge[u] == std::numeric_limits<double>::max())
            break;

        in_mst[u] = true;
        if (parent[u] != -1)
        {
            mst_adj[parent[u]].push_back(u);
            mst_adj[u].push_back(parent[u]);
        }

        for (size_t v = 0; v < g.n; ++v)
        {
            double weight = g.am[u][v];
            if (!in_mst[v] && weight < min_edge[v])
            {
                parent[v] = u;
                min_edge[v] = weight;
            }
        }
    }
    return mst_adj;
}

inline permutation_t get_initial_mst_tour(const Graph &g, size_t start_node = 0)
{
    auto mst_adj = get_mst_adj_list(g);
    permutation_t tour;
    std::vector<bool> visited(g.n, false);
    std::stack<size_t> s;

    s.push(start_node);
    while (!s.empty())
    {
        size_t curr = s.top();
        s.pop();
        if (!visited[curr])
        {
            visited[curr] = true;
            tour.push_back(curr);
            for (size_t neighbor : mst_adj[curr])
                if (!visited[neighbor])
                    s.push(neighbor);
        }
    }
    return tour;
}

#endif
