#ifndef GRAPH_HPP
#define GRAPH_HPP

/*
    Podany headerfile zawiera definicje grafu pełnego o losowych wagach krawędzi.

    Założenia:
    - graf pełny to graf nieskierowany, w którym każda para wierzchołków jest połączona krawędzią
    - każda krawędź ma losową wagę z przedziału (0, 1)

    Biorąc pod uwagę gęstość grafu, w pamięci powinien być reprezentowany jako macierz sąsiedztwa.
    * Wykład XVI, sekcja "Macierz sąsiedztwa" dostępny z moich osobistych notatek:
    https://github.com/Rafisto/uni/blob/master/4_semester_2025/aisd/lecture.pdf
*/

#include <stack>
#include <vector>
#include <random>
#include <iostream>

// W C++ można wykorzystać using zamiast typedef.
// typedef std::vector<std::vector<double>> AdjacencyMatrix;
using AdjacencyMatrix = std::vector<std::vector<double>>;

struct Edge
{
    size_t u, v;
    double weight;
    Edge(size_t u, size_t v, double weight) : u(u), v(v), weight(weight) {}
};

struct Graph
{
    size_t n;
    AdjacencyMatrix adjacency_matrix;

    Graph() : n(0), adjacency_matrix(0, std::vector<double>(0, 0.0)) {}
    Graph(size_t vertices) : n(vertices), adjacency_matrix(vertices, std::vector<double>(vertices, 0.0))
    {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<double> dist(0.0, 1.0);

        for (size_t i = 0; i < n; ++i)
        {
            for (size_t j = i + 1; j < n; ++j)
            {
                double weight = dist(gen);

                // AM[i][j] = AM[j][i] ponieważ graf jest nieskierowany.
                adjacency_matrix[i][j] = weight;
                adjacency_matrix[j][i] = weight;
            }
        }
    }

    std::vector<size_t> get_dfs_tour() const {
        std::vector<size_t> tour;
        std::vector<bool> visited(n, false);
        std::stack<size_t> s;

        s.push(0);

        while (!s.empty()) {
            size_t curr = s.top();
            s.pop();

            if (!visited[curr]) {
                visited[curr] = true;
                tour.push_back(curr);

                for (int next = static_cast<int>(n) - 1; next >= 0; --next) {
                    if (adjacency_matrix[curr][next] > 0 && !visited[next]) {
                        s.push(next);
                    }
                }
            }
        }
        return tour;
    }
};

inline void print_edge_list(const Graph &graph)
{
    for (size_t i = 0; i < graph.n; ++i)
    {
        for (size_t j = i + 1; j < graph.n; ++j)
        {
            double w = graph.adjacency_matrix[i][j];
            if (w != 0.0) std::cout << i << " " << j << " " << w << std::endl;
        }
    }
}

#endif
