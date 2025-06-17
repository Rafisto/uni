#ifndef KRUSKAL_HPP
#define KRUSKAL_HPP

#include <vector>
#include <algorithm>
#include <functional>
#include <tuple>

#include "graph.hpp"

static size_t find(size_t i, std::vector<size_t>& parent) {
    if (parent[i] != i) {
        parent[i] = find(parent[i], parent);
    }
    return parent[i];
}

static void treeUnion(size_t x, size_t y, std::vector<size_t>& parent, std::vector<size_t>& rank) {
    size_t xroot = find(x, parent);
    size_t yroot = find(y, parent);
    if (rank[xroot] < rank[yroot]) {
        parent[xroot] = yroot;
    } else if (rank[xroot] > rank[yroot]) {
        parent[yroot] = xroot;
    } else {
        parent[yroot] = xroot;
        rank[xroot]++;
    }
}

static std::tuple<Graph, double> kruskal(const Graph& graph) {
    std::vector<Edge> edges;
    for (size_t i = 0; i < graph.n; ++i) {
        for (size_t j = i + 1; j < graph.n; ++j) {
            if (graph.adjacency_matrix[i][j] > 0) {
                edges.emplace_back(i, j, graph.adjacency_matrix[i][j]);
            }
        }
    }

    std::sort(edges.begin(), edges.end(), [](const Edge& a, const Edge& b) {
        return a.weight < b.weight;
    });

    std::vector<size_t> parent(graph.n);
    std::vector<size_t> rank(graph.n, 0);
    for (size_t i = 0; i < graph.n; ++i) {
        parent[i] = i;
    }

    Graph mst(graph.n);
    mst.adjacency_matrix = AdjacencyMatrix(graph.n, std::vector<double>(graph.n, 0.0));
    double totalCost = 0.0;

    size_t edgeCount = 0;
    for (const auto& edge : edges) {
        if (edgeCount == graph.n - 1) {
            break;
        }
        size_t u = edge.u;
        size_t v = edge.v;
        if (find(u, parent) != find(v, parent)) {
            mst.adjacency_matrix[u][v] = edge.weight;
            mst.adjacency_matrix[v][u] = edge.weight;
            totalCost += edge.weight;
            treeUnion(u, v, parent, rank);
            edgeCount++;
        }
    }

    return {mst, totalCost};
}

#endif