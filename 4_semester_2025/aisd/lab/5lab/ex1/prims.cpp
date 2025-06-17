#include <iostream>

#include "graph.hpp"
#include "prims.hpp"

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        std::cerr << "Usage: " << argv[0] << " <number_of_vertices> [--no-print]" << std::endl;
        return 1;
    }

    size_t vertices = std::stoul(argv[1]);

    if (vertices <= 0)
    {
        std::cerr << "Error: Number of vertices must be positive." << std::endl;
        return 1;
    }

    bool noPrint = (argc > 2 && std::string(argv[2]) == "--no-print");

    Graph g(vertices);

    if (!noPrint)
    {
        std::cout << "PRIM'S ALGORITHM" << std::endl;
        std::cout << "===================" << std::endl;
    }

    auto [mst, totalCost] = prims(g);

    if (!noPrint)
    {
        std::cout << "# COST" << std::endl;
        std::cout << totalCost << std::endl;

        std::cout << "# ORIGINAL" << std::endl;
        print_edge_list(g);

        std::cout << "# MST" << std::endl;
        print_edge_list(mst);
    }
}