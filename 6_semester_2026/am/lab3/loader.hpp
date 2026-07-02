#ifndef LOADER_HPP
#define LOADER_HPP

#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include "graph.hpp"

constexpr const char *folder = "data/";
constexpr const char *match = "NODE_COORD_SECTION";
constexpr const char *files[] = {
    "western_sahara.tsp", "djibouti.tsp", "qatar.tsp", "uruguay.tsp",
    "zimbabwe.tsp", "oman.tsp", "canada.tsp", "tanzania.tsp",
    "egypt.tsp", "ireland.tsp"};

class GraphProblem
{
public:
    std::string name;
    Graph graph;
};

inline std::vector<GraphProblem> load_graphs()
{
    std::vector<GraphProblem> graphs = {};
    for (const std::string &filename : files)
    {
        std::vector<point_t> coords;
        std::ifstream infile(folder + filename);
        std::string line;
        bool read_section = false;

        while (std::getline(infile, line))
        {
            if (line.starts_with(match))
            {
                read_section = true;
                continue;
            }
            if (!read_section || line.empty() || line.starts_with("EOF"))
                continue;

            std::istringstream iss(line);
            size_t idx;
            double x, y;
            if (iss >> idx >> x >> y)
            {
                coords.push_back({x, y});
            }
        }

        size_t n = coords.size();
        Graph g;
        g.n = n;
        g.matrix(coords);

        graphs.push_back({filename.c_str(), g});
    }

    return graphs;
}

#endif
