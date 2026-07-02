#include <vector>
#include <print>

#include "loader.hpp"
#include "graph.hpp"
#include "local_search.hpp"

int main()
{
    std::vector<GraphProblem> graphs = load_graphs();
    std::println("name;n;local_all;local_random;local_mst");
    for (const GraphProblem &problem : graphs)
    {
        LocalSearchStats stats = local_search(problem.graph, START_RANDOM, local_search_full_step);
        uint64_t cost_local_search_tour = stats.best_distance;

        LocalSearchStats stats_random = local_search(problem.graph, START_MST, local_search_best_n_step);
        uint64_t cost_random_search_tour = stats_random.best_distance;

        LocalSearchStats stats_mst = local_search(problem.graph, START_MST, local_search_full_step);
        uint64_t cost_mst_search_tour = stats_mst.best_distance;

        std::println("{};{};{};{};{}", problem.name, problem.graph.n, cost_local_search_tour, cost_random_search_tour, cost_mst_search_tour);
    }

    return 0;
}
