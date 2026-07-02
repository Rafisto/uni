#ifndef GENETIC_HPP
#define GENETIC_HPP

#include <algorithm>
#include <functional>
#include <random>
#include <vector>
#include <cstdint>
#include <limits>
#include <thread>
#include <omp.h>

#include "graph.hpp"
#include "tsp_utils.hpp"
#include "mst_tour.hpp"
#include "tabu.hpp"

struct Tour
{
    permutation_t permutation;
    uint64_t cost;

    Tour() : cost(std::numeric_limits<uint64_t>::max()) {}
    Tour(permutation_t p, uint64_t c) : permutation(std::move(p)), cost(c) {}

    static Tour create(const Graph &g, permutation_t p)
    {
        uint64_t c = calculate_tour_cost(g, p);
        return Tour(std::move(p), c);
    }
};

class GeneticStats
{
public:
    uint64_t best_distance;
    permutation_t best_permutation;
};

inline const Tour &tournament_selection(const std::vector<Tour> &population, std::mt19937 &gen)
{
    std::uniform_int_distribution<size_t> dist(0, population.size() - 1);
    const Tour &a = population[dist(gen)];
    const Tour &b = population[dist(gen)];
    return (a.cost < b.cost) ? a : b;
}

inline std::mt19937 &thread_rng()
{
    thread_local std::mt19937 gen([]()
                                  {
        std::random_device rd;
        auto seed = rd();
        seed ^= std::hash<std::thread::id>()(std::this_thread::get_id());
        return std::mt19937(seed); }());
    return gen;
}

inline permutation_t mutate(const permutation_t &parent, std::mt19937 &gen)
{
    size_t n = parent.size();
    std::uniform_int_distribution<size_t> dist(0, n - 1);
    size_t p1 = dist(gen);
    size_t p2 = dist(gen);
    if (p1 > p2)
        std::swap(p1, p2);

    permutation_t child = parent;
    std::reverse(child.begin() + p1, child.begin() + p2 + 1);
    return child;
}

inline permutation_t pmx(const permutation_t &p1, const permutation_t &p2, std::mt19937 &gen)
{
    size_t n = p1.size();
    permutation_t child(n, -1);
    std::vector<size_t> pos_in_p2(n);
    for (size_t i = 0; i < n; ++i)
        pos_in_p2[p2[i]] = i;

    std::uniform_int_distribution<size_t> dist(0, n - 1);
    size_t pt1 = dist(gen), pt2 = dist(gen);
    if (pt1 > pt2)
        std::swap(pt1, pt2);

    std::vector<char> in_segment(n, 0);
    for (size_t i = pt1; i <= pt2; ++i)
    {
        child[i] = p1[i];
        in_segment[p1[i]] = 1;
    }

    for (size_t i = pt1; i <= pt2; ++i)
    {
        int val = p2[i];
        if (in_segment[val])
            continue;
        size_t curr_pos = i;
        size_t next = pos_in_p2[p1[curr_pos]];
        while (next >= pt1 && next <= pt2)
        {
            next = pos_in_p2[p1[next]];
        }
        child[next] = val;
        in_segment[val] = 1;
    }

    for (size_t i = 0; i < n; ++i)
    {
        if (child[i] == -1)
            child[i] = p2[i];
    }
    return child;
}

inline permutation_t ox(const permutation_t &p1, const permutation_t &p2, std::mt19937 &gen)
{
    size_t n = p1.size();
    permutation_t child(n, -1);
    std::vector<char> mapping(n, 0);

    std::uniform_int_distribution<size_t> dist(0, n - 1);
    size_t pt1 = dist(gen), pt2 = dist(gen);
    if (pt1 > pt2)
        std::swap(pt1, pt2);

    for (size_t i = pt1; i <= pt2; ++i)
    {
        child[i] = p1[i];
        mapping[p1[i]] = 1;
    }

    size_t current = (pt2 + 1) % n;
    for (size_t i = 0; i < n; ++i)
    {
        size_t p2_idx = (pt2 + 1 + i) % n;
        if (!mapping[p2[p2_idx]])
        {
            child[current] = p2[p2_idx];
            mapping[p2[p2_idx]] = 1;
            current = (current + 1) % n;
        }
    }
    return child;
}

class GeneticConfiguration
{
public:
    size_t population_size;
    size_t generations;
    size_t icount = 1;
    size_t interval = 10;
    std::function<permutation_t(const permutation_t &, const permutation_t &, std::mt19937 &)> crossover;
    bool enable_mutation;
    bool enable_ts;
};

inline GeneticStats genetic_algorithm(const Graph &g, const GeneticConfiguration &c)
{
    int max_threads = omp_get_max_threads();
    std::vector<std::mt19937> thread_gens(max_threads);
    std::random_device rd;
    for (int t = 0; t < max_threads; ++t)
        thread_gens[t].seed(rd() ^ t);

    size_t island_pop_size = c.population_size / c.icount;
    std::vector<std::vector<Tour>> islands(c.icount, std::vector<Tour>(island_pop_size));

#pragma omp parallel for collapse(2)
    for (size_t i = 0; i < c.icount; ++i)
    {
        for (size_t j = 0; j < island_pop_size; ++j)
        {
            permutation_t p = get_initial_mst_tour(g, (i * island_pop_size + j) % g.n);
            islands[i][j] = Tour::create(g, std::move(p));
        }
    }

    for (size_t gen_idx = 0; gen_idx < c.generations; ++gen_idx)
    {
        std::vector<std::vector<Tour>> next_gen_islands(c.icount, std::vector<Tour>(island_pop_size));

#pragma omp parallel for collapse(2) schedule(dynamic)
        for (size_t is = 0; is < c.icount; ++is)
        {
            for (size_t j = 0; j < island_pop_size; ++j)
            {
                auto &local_gen = thread_gens[omp_get_thread_num()];

                const Tour &p1 = tournament_selection(islands[is], local_gen);
                const Tour &p2 = tournament_selection(islands[is], local_gen);

                permutation_t child_p = c.crossover(p1.permutation, p2.permutation, local_gen);

                if (c.enable_mutation)
                    child_p = mutate(child_p, local_gen);
                if (c.enable_ts)
                    child_p = tabu_search_step(g, child_p, 10, 2);

                next_gen_islands[is][j] = Tour::create(g, std::move(child_p));
            }
        }
        islands = std::move(next_gen_islands);

        if (c.icount > 1 && (gen_idx + 1) % c.interval == 0)
        {
            for (size_t is = 0; is < c.icount; ++is)
            {
                size_t next_is = (is + 1) % c.icount;
                const Tour &immigrant = tournament_selection(islands[is], thread_gens[0]);
                islands[next_is][thread_gens[0]() % island_pop_size] = immigrant;
            }
        }
    }

    Tour best_overall = islands[0][0];
    for (const auto &island : islands)
    {
        for (const auto &t : island)
        {
            if (t.cost < best_overall.cost)
                best_overall = t;
        }
    }

    return {best_overall.cost, std::move(best_overall.permutation)};
}

#endif
