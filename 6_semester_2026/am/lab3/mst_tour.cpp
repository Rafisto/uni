#include <vector>
#include <print>

#include "loader.hpp"
#include "graph.hpp"
#include "mst_tour.hpp"
#include "tsp_utils.hpp"

int main()
{
    std::vector<GraphProblem> graphs = load_graphs();
    std::println("name;n;cost_mst_tour");
    for (const GraphProblem &problem : graphs)
    {
        permutation_t mst_tour = get_initial_mst_tour(problem.graph);
        uint64_t cost_mst_tour = calculate_tour_cost(problem.graph, mst_tour);
        std::println("{};{};{}", problem.name, problem.graph.n, cost_mst_tour);
    }

    return 0;
}
