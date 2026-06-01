#include <vector>
#include <print>

#include "loader.hpp"
#include "graph.hpp"
#include "annealing.hpp"

int main()
{
    std::vector<GraphProblem> graphs = load_graphs();
    std::println("name;n;annealing");
    for (const GraphProblem &problem : graphs)
    {
        AnnealingStats stats = best_annealing(problem.graph, 100);

        std::println("{};{};{}", problem.name, problem.graph.n, stats.best_distance);
    }

    return 0;
}
