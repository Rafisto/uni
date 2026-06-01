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

#include <vector>
#include <cstdint>
#include <cmath>

typedef std::pair<double, double> point_t;
typedef std::vector<point_t> point_list_t;
typedef std::vector<std::size_t> permutation_t;

inline int euclidean(const point_t x, const point_t y)
{
    double dx = x.first - y.first;
    double dy = x.second - y.second;
    return static_cast<int>(std::round(std::sqrt(dx * dx + dy * dy)));
}

// W C++ można wykorzystać using zamiast typedef.
// typedef std::vector<std::vector<double>> AdjacencyMatrix;
using AM = std::vector<std::vector<double>>;

struct Edge
{
    size_t u, v;
    double weight;
    Edge(size_t u, size_t v, uint64_t weight) : u(u), v(v), weight(weight) {}
};

struct Graph
{
    size_t n;
    AM am;
    Graph() : n(0), am(0, std::vector<double>(0, 0.0)) {}

    void matrix(const std::vector<std::pair<double, double>> &coords)
    {
        this->n = coords.size();
        am.assign(n, std::vector<double>(n, 0.0));

        for (size_t i = 0; i < n; ++i)
        {
            for (size_t j = 0; j < n; ++j)
            {
                am[i][j] = static_cast<double>(euclidean(coords[i], coords[j]));
            }
        }
    }
};

#endif
