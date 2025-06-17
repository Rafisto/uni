#ifndef PRIMS_HPP
#define PRIMS_HPP

#include <stdexcept>
#include <queue>
#include <tuple>
#include <limits>

#include "graph.hpp"

// (4:23:00) Prim's Minimum Spanning Tree Algorithm
// https://www.youtube.com/watch?v=09_LlHjoEiY&t=15780s

std::tuple<Graph, double> prims(const Graph& graph) {
    size_t n = graph.n;
    std::vector<bool> inMST(n, false);
    std::vector<double> minEdge(n, std::numeric_limits<double>::max());
    std::vector<size_t> parent(n, std::numeric_limits<size_t>::max());
    minEdge[0] = 0.0;

    using Edge = std::pair<double, size_t>;
    std::priority_queue<Edge, std::vector<Edge>, std::greater<Edge>> pq;

    // ps.push(Edge(0.0, 0)); -- Emplace means construct and insert in one step.
    pq.emplace(0.0, 0);
    double totalCost = 0.0;

    while (!pq.empty()) {
        auto [weight, u] = pq.top();
        pq.pop();

        if (inMST[u]) continue;
        inMST[u] = true;
        totalCost += weight;

        for (size_t v = 0; v < n; ++v) {
            double w = graph.adjacency_matrix[u][v];
            if (!inMST[v] && w < minEdge[v]) {
                minEdge[v] = w;
                parent[v] = u;
                pq.emplace(w, v);
            }
        }
    }

    Graph mst(n);
    mst.adjacency_matrix = AdjacencyMatrix(n, std::vector<double>(n, 0.0));

    for (size_t v = 1; v < n; ++v) {
        size_t u = parent[v];
        mst.adjacency_matrix[u][v] = minEdge[v];
        mst.adjacency_matrix[v][u] = minEdge[v]; 
    }

    return {mst, totalCost};
}

#endif
