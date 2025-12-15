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

    void dial(const Graph &graph, long long source, long long C,
              std::optional<long long> target = std::nullopt) {
        long long bucketCount = C + 1;
        std::vector<std::unordered_set<long long>> buckets(bucketCount);

        buckets[0].insert(source);
        distances[source] = 0;

        long long currentBucket = 0;

        while (true) {
            // szukamy niepustego kubełka
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
                    // wszystkie kubełki puste
                    if (allEmpty)
                        return;
                }
            }

            // przeszukujemy niepusty kubełek
            while (!buckets[currentBucket].empty()) {
                // u to nasz wierzchołek do rozpatrzenia
                long long u = *buckets[currentBucket].begin();

                // wyciągamy u z kubełka
                buckets[currentBucket].erase(buckets[currentBucket].begin());

                if (currentBucket != distances[u] % bucketCount)
                    continue;

                // patrzymy na sąsiadów u
                for (const auto &edge : graph[u]) {
                    long long v = edge.first;
                    long long weight = edge.second;
                    long long newDist = distances[u] + weight;

                    // krótsza ścieżka do v przez u
                    if (newDist < distances[v]) {
                        // usuwamy v ze starego kubełka
                        if (distances[v] != INT_MAX) {
                            buckets[distances[v] % bucketCount].erase(v);
                        }

                        // nowa odległość
                        distances[v] = newDist;
                        predecessors[v] = u;

                        // dodajemy v do nowego kubełka
                        buckets[newDist % bucketCount].insert(v);
                    }
                }
            }

            // kolejny kubełek
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