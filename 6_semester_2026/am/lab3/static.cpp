#include <vector>
#include <print>

#include "random.hpp"
#include "loader.hpp"
#include "tsp_utils.hpp"

class Best
{
public:
    const std::string name;
    const uint64_t best;
    const uint64_t n;
};

const std::vector<Best> best = {
    {"western_sahara.tsp", 27603, 29},
    {"djibouti.tsp", 6656, 38},
    {"qatar.tsp", 9352, 194},
    {"uruguay.tsp", 79114, 734},
    {"zimbabwe.tsp", 95345, 929},
    {"oman.tsp", 86891, 1979},
    {"canada.tsp", 1290319, 4663},
    {"tanzania.tsp", 394718, 6117},
    {"egypt.tsp", 172387, 7146},
    {"ireland.tsp", 206171, 8246}};

int main()
{
    std::vector<GraphProblem> graphs = load_graphs();
    std::println("name;n;cost_random;cost_best");
    for (const GraphProblem &problem : graphs)
    {
        permutation_t tour = random_tour(problem.graph.n);
        uint64_t cost_random = calculate_tour_cost(problem.graph, tour);
        uint64_t cost_best = best[&problem - &graphs[0]].best;
        std::println("{};{};{};{}", problem.name, problem.graph.n, cost_random, cost_best);
    }

    return 0;
}
