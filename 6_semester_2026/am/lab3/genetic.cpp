#include <vector>
#include <print>

#include "loader.hpp"
#include "graph.hpp"
#include "genetic.hpp"

void print_permutation(const permutation_t &perm) {
    for (size_t i = 0; i < perm.size(); ++i) {
        std::print("{}{}", perm[i], (i == perm.size() - 1) ? "" : ":");
    }
    std::println("");
}

int main()
{
    std::vector<GraphProblem> graphs = load_graphs();
    std::println("name;n;algorithm;distance|permutation...");
    for (const GraphProblem &problem : graphs)
    {
        size_t population_size = 20;
        size_t generations = 100;

        GeneticConfiguration pmx_config = {
            .population_size = population_size,
            .generations = generations,
            .icount = 1,
            .interval = 0,
            .crossover = pmx,
            .enable_mutation = true,
            .enable_ts = false};

        GeneticStats pmx_stats = genetic_algorithm(problem.graph, pmx_config);
        
        std::print("{};{};pmx;{}|", problem.name, problem.graph.n, pmx_stats.best_distance);
        print_permutation(pmx_stats.best_permutation);

        GeneticConfiguration ox_config = {
            .population_size = population_size,
            .generations = generations,
            .icount = 1,
            .interval = 0,
            .crossover = ox,
            .enable_mutation = true,
            .enable_ts = false};

        GeneticStats ox_stats = genetic_algorithm(problem.graph, ox_config);
        
        std::print("{};{};ox;{}|", problem.name, problem.graph.n, ox_stats.best_distance);
        print_permutation(ox_stats.best_permutation);

        GeneticConfiguration memetic_config = {
            .population_size = population_size,
            .generations = generations,
            .icount = 1,
            .interval = 0,
            .crossover = ox,
            .enable_mutation = true,
            .enable_ts = true};

        GeneticStats memetic_stats = genetic_algorithm(problem.graph, memetic_config);

        std::print("{};{};memetic;{}|", problem.name, problem.graph.n, memetic_stats.best_distance);
        print_permutation(memetic_stats.best_permutation);

        GeneticConfiguration island_config = {
            .population_size = population_size,
            .generations = generations,
            .icount = 10,
            .interval = 20,
            .crossover = ox,
            .enable_mutation = true,
            .enable_ts = true};

        GeneticStats island_stats = genetic_algorithm(problem.graph, island_config);

        std::print("{};{};island;{}|", problem.name, problem.graph.n, island_stats.best_distance);
        print_permutation(island_stats.best_permutation);
    }

    return 0;
}
