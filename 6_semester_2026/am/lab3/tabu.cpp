#include <vector>
#include <print>

#include "loader.hpp"
#include "graph.hpp"
#include "tabu.hpp"

int main()
{
    std::vector<GraphProblem> graphs = load_graphs();
    std::println("name;n;tabu");
    for (const GraphProblem &problem : graphs)
    {
        TabuStats stats = tabu_search(problem.graph, 10);

        std::println("{};{};{}", problem.name, problem.graph.n, stats.best_distance);
    }

    return 0;
}
