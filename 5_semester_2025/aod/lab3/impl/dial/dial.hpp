#ifndef DIAL_HPP
#define DIAL_HPP

#include <limits>
#include <optional>
#include <unordered_set>
#include <vector>

#include "graph.hpp"

#define INT_MAX std::numeric_limits<long long>::max()
#define INT_MIN std::numeric_limits<long long>::min()

class Dial {
  private:
    long long n;
    std::vector<long long> distances;
    std::vector<long long> predecessors;

  public:
    Dial(long long n) : n(n), distances(n, INT_MAX), predecessors(n, -1) {}

    void dial(const Graph &graph, long long source, long long W,
              std::optional<long long> target = std::nullopt) {
        long long bucketCount = W + 1;
        std::vector<std::unordered_set<long long>> buckets(bucketCount);

        buckets[0].insert(source);
        distances[source] = 0;

        long long currentBucket = 0;

        while (true) {
            while (buckets[currentBucket].empty()) {
                currentBucket = (currentBucket + 1) % bucketCount;
                if (currentBucket == 0) {
                    bool allEmpty = true;
                    for (const auto &bucket : buckets) {
                        if (!bucket.empty()) {
                            allEmpty = false;
                            break;
                        }
                    }
                    if (allEmpty)
                        return;
                }
            }

            while (!buckets[currentBucket].empty()) {
                long long u = *buckets[currentBucket].begin();
                buckets[currentBucket].erase(buckets[currentBucket].begin());

                if (currentBucket != distances[u] % bucketCount)
                    continue;

                for (const auto &edge : graph[u]) {
                    long long v = edge.first;
                    long long weight = edge.second;
                    long long newDist = distances[u] + weight;

                    if (newDist < distances[v]) {

                        if (distances[v] != INT_MAX) {
                            buckets[distances[v] % bucketCount].erase(v);
                        }

                        distances[v] = newDist;
                        predecessors[v] = u;

                        buckets[newDist % bucketCount].insert(v);
                    }
                }
            }

            currentBucket = (currentBucket + 1) % bucketCount;
        }
    }
    long long getDistance(long long v) const { return distances[v]; }
    const std::vector<long long> &getDistances() const { return distances; }
    const std::vector<long long> &getPredecessors() const {
        return predecessors;
    }
};

#endif // DIAL_HPP