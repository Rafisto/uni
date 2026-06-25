#ifndef BUCHBERGER_HPP
#define BUCHBERGER_HPP

#include <queue>
#include <vector>
#include <print>

#include "polyreduce.hpp"

// https://en.wikipedia.org/wiki/Buchberger%27s_algorithm#Algorithm

inline monomian_t monomial_lcm(const monomian_t &a, const monomian_t &b)
{
    monomian_t res(std::max(a.size(), b.size()), 0);
    for (size_t i = 0; i < res.size(); ++i)
    {
        double_t ae = (i < a.size()) ? a[i] : 0;
        double_t be = (i < b.size()) ? b[i] : 0;
        res[i] = std::max(ae, be);
    }
    return res;
}

inline std::vector<poly_t> buchberger(const std::vector<poly_t> &F, poly_order_t order)
{
    // 1. G := F (Keep whole polynomials, filter out empty ones)
    std::vector<poly_t> G;
    for (const auto &f : F)
    {
        if (!f.empty())
            G.push_back(f);
    }

    using index_pair_t = std::pair<size_t, size_t>;
    std::queue<index_pair_t> pairs;

    // 2. Initialize pairs for unique combinations (i < j)
    for (size_t i = 0; i < G.size(); ++i)
    {
        for (size_t j = i + 1; j < G.size(); ++j)
        {
            pairs.push({i, j});
        }
    }

    while (!pairs.empty())
    {
        auto [i, j] = pairs.front();
        pairs.pop();

        poly_t fi = G[i];
        poly_t fj = G[j];

        auto lt_i = get_lt(fi, order);
        auto lt_j = get_lt(fj, order);

        monomian_t lcm = monomial_lcm(lt_i->first, lt_j->first);

        double_t lc_i = lt_i->second;
        double_t lc_j = lt_j->second;

        // 3. Complete Syzygy (S-Polynomial) over all terms
        poly_t syzygy;

        // Component 1: (LCM / LT(f_i)) * f_i * lc_j
        for (const auto &[mon, coeff] : fi)
        {
            monomian_t target_mon = lcm;
            for (size_t k = 0; k < mon.size(); ++k)
            {
                target_mon[k] += (mon[k] - lt_i->first[k]);
            }
            syzygy[target_mon] += coeff * lc_j;
        }

        // Component 2: Subtract (LCM / LT(f_j)) * f_j * lc_i
        for (const auto &[mon, coeff] : fj)
        {
            monomian_t target_mon = lcm;
            for (size_t k = 0; k < mon.size(); ++k)
            {
                target_mon[k] += (mon[k] - lt_j->first[k]);
            }
            syzygy[target_mon] -= coeff * lc_i;
            if (syzygy[target_mon] == 0)
            {
                syzygy.erase(target_mon);
            }
        }

        if (syzygy.empty())
            continue;

        // 4. Reduce S_ij by our current set G
        auto [quotients, remainder] = poly_reduce(syzygy, G, order);

        // 5. If remainder != 0, expand G and track new pairs
        if (!remainder.empty())
        {
            size_t new_index = G.size();
            for (size_t k = 0; k < new_index; ++k)
            {
                pairs.push({k, new_index});
            }
            G.push_back(remainder);
        }
    }

    // 6. Reduce Grobner Basis
    std::vector<poly_t> reduced_G;

    for (size_t i = 0; i < G.size(); ++i)
    {
        if (G[i].empty())
            continue;

        std::vector<poly_t> others;
        for (size_t j = 0; j < G.size(); ++j)
        {
            if (i != j && !G[j].empty())
            {
                others.push_back(G[j]);
            }
        }

        auto [quotients, remainder] = poly_reduce(G[i], others, order);

        if (!remainder.empty())
        {
            auto lt = get_lt(remainder, order);
            double_t lc = lt->second;

            if (lc != 1)
            {
                poly_t monic_remainder;
                for (const auto &[mon, coeff] : remainder)
                {
                    monic_remainder[mon] = coeff / lc;
                }
                remainder = std::move(monic_remainder);
            }

            if (std::find(reduced_G.begin(), reduced_G.end(), remainder) == reduced_G.end())
            {
                reduced_G.push_back(remainder);
            }
        }
    }

    return reduced_G;
}

#endif
