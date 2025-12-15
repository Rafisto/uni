#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <vector>

using Graph = std::vector<std::vector<std::size_t>>;

inline std::vector<std::size_t> adjacent(const Graph &g, std::size_t v) {
    return g[v];
}

#endif