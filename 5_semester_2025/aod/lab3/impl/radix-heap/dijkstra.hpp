#ifndef DIJKSTRA_HPP
#define DIJKSTRA_HPP

#include <optional>
#include <vector>
#include <limits>
#include "graph.hpp"
#include "radix_heap.hpp"

#define INT_MAX std::numeric_limits<long long>::max()
#define INT_MIN std::numeric_limits<long long>::min()

class Dijkstra {
private:
    long long n;
    std::vector<long long> distances;
    std::vector<long long> predecessors;

public:
    Dijkstra(long long n) : n(n) {
        distances.resize(n, std::numeric_limits<long long>::max());
        predecessors.resize(n, -1);
    }

    void dijkstra(const Graph& graph, long long source, std::optional<long long> target = std::nullopt) {
        distances[source] = 0;
        predecessors[source] = source;

        RadixHeap pq;
        pq.insert(0, source);

        while (!pq.empty()) {
            auto [currentDistance, u] = pq.extract_min();
            pq.pop();

            if (currentDistance > distances[u])
                continue;

            if (target.has_value() && u == target.value())
                return;

            for (auto& [v, weight] : graph[u]) {
                long long nd = currentDistance + weight;

                if (nd < distances[v]) {
                    distances[v] = nd;
                    predecessors[v] = u;
                    pq.insert(nd, v);
                }
            }
        }
    }

    long long getDistance(long long v) const { return distances[v]; }
    const std::vector<long long>& getDistances() const { return distances; }
    const std::vector<long long>& getPredecessors() const { return predecessors; }
};

#endif // DIJKSTRA_HPP
