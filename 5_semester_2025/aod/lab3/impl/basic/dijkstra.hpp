#ifndef DIJKSTRA_HPP
#define DIJKSTRA_HPP

#include <vector>
#include <limits>
#include <utility>
#include <queue>

#include "graph.hpp"

#define INT_MAX std::numeric_limits<long long>::max()
#define INT_MIN std::numeric_limits<long long>::min()

class Dijkstra {
private:
    long long n;
    std::vector<long long> distances; 
    std::vector<long long> predecessors;
public:
    Dijkstra(long long n) {
        this->n = n;
        distances.resize(n, INT_MAX);
        predecessors.resize(n, -1);
    }

    void dijkstra(const Graph& graph, long long source, std::optional<long long> target = std::nullopt) {
        distances[source] = 0;
        predecessors[source] = source;

        std::priority_queue<std::pair<long long, long long>, std::vector<std::pair<long long, long long>>, std::greater<>> pq;
        pq.emplace(0, source);

        while (!pq.empty()) {
            long long currentDistance = pq.top().first;
            long long currentNode = pq.top().second;
            pq.pop();

            if (target.has_value() && currentNode == target.value()) return;

            if (currentDistance > distances[currentNode]) continue;

            for (const auto& [neighbor, weight] : graph[currentNode]) {
                if (distances[currentNode] + weight < distances[neighbor]) {
                    distances[neighbor] = distances[currentNode] + weight;
                    predecessors[neighbor] = currentNode;
                    pq.emplace(distances[neighbor], neighbor);
                }
            }
        }
    }

    long long getDistance(long long v) const { return distances[v]; }
    const std::vector<long long>& getDistances() const { return distances; }
    const std::vector<long long>& getPredecessors() const { return predecessors; }
};

#endif // DIJKSTRA_HPP
