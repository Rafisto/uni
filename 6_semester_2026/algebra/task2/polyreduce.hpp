#ifndef POLY_REDUCE_HPP
#define POLY_REDUCE_HPP

#include <unordered_map>
#include <vector>
#include <string>
#include <tuple>
#include <algorithm>
#include <boost/container_hash/hash.hpp>

// https://stackoverflow.com/questions/10405030/c-unordered-map-fail-when-used-with-a-vector-as-key
template <typename Container> 
struct container_hash {
    std::size_t operator()(Container const& c) const {
        return boost::hash_range(c.begin(), c.end());
    }
};

using monomian_t = std::vector<int64_t>;
using poly_t = std::unordered_map<monomian_t, int64_t, container_hash<monomian_t>>;

inline char get_var_name(size_t index) {
    static const char vars[] = {'x', 'y', 'z', 'w', 'u', 'v'};
    return index < sizeof(vars) ? vars[index] : '?';
}

inline std::string poly_fmt(const poly_t& poly, bool (*compare)(const monomian_t&, const monomian_t&)) {
    if (poly.empty()) return "0";

    std::vector<std::pair<monomian_t, int64_t>> terms(poly.begin(), poly.end());
    
    std::sort(terms.begin(), terms.end(), [compare](const auto& a, const auto& b) {
        return compare(a.first, b.first); 
    });

    std::string result;
    bool first = true;
    for (const auto& [monomian, coeff] : terms) {
        if (coeff == 0) continue;

        if (first) {
            if (coeff < 0) result += "-";
            first = false;
        } else {
            if (coeff > 0) result += " + ";
            else result += " - ";
        }

        int64_t abs_c = std::abs(coeff);
        
        bool is_constant = true;
        for (int64_t exp : monomian) {
            if (exp > 0) { is_constant = false; break; }
        }

        if (is_constant) {
            result += std::to_string(abs_c);
        } else {
            if (abs_c != 1) { 
                result += std::to_string(abs_c);
            }
            for (size_t i = 0; i < monomian.size(); ++i) {
                if (monomian[i] > 0) {
                    result += "(";
                    result += get_var_name(i);
                    if (monomian[i] > 1) {
                        result += "^" + std::to_string(monomian[i]);
                    }
                    result += ")";
                }
            }
        }
    }
    
    if (result.empty()) return "0";
    return result;
}

// lex order: x_1 > x_2 > ... > x_n
inline bool compare_lex(const monomian_t& lhs, const monomian_t& rhs)
{
    for (size_t i = 0; i < lhs.size(); ++i) {
        if (lhs[i] > rhs[i]) return true; 
        else if (lhs[i] < rhs[i]) return false; 
    }
    return false; 
}

// ordered lex order: x_{pi(1)} > x_{pi(2)} > ... > x_{pi(n)}
inline bool compare_ordered_lex(const monomian_t& lhs, const monomian_t& rhs, const std::vector<size_t>& pi)
{
    for (size_t i = 0; i < pi.size(); ++i) {
        size_t idx = pi[i];
        if (lhs[idx] > rhs[idx]) return true; 
        else if (lhs[idx] < rhs[idx]) return false; 
    }
    return false; 
}

inline std::vector<size_t> g_pi;
inline bool compare_ordered_wrapper(const monomian_t& lhs, const monomian_t& rhs) {
    return compare_ordered_lex(lhs, rhs, g_pi);
}

// graded lex order: total degree first, then lex order
inline bool compare_graded_lex(const monomian_t& lhs, const monomian_t& rhs)
{
    size_t total_degree_lhs = 0;
    size_t total_degree_rhs = 0;
    for (size_t i = 0; i < lhs.size(); ++i) {
        total_degree_lhs += lhs[i];
        total_degree_rhs += rhs[i];
    }

    if (total_degree_lhs > total_degree_rhs) return true; 
    else if (total_degree_lhs < total_degree_rhs) return false; 
    else return compare_lex(lhs, rhs);
}

inline poly_t::const_iterator get_lt(const poly_t& poly, 
    bool (*compare)(const monomian_t&, const monomian_t&)) 
{
    auto lt_it = poly.begin();
    for (auto it = std::next(poly.begin()); it != poly.end(); ++it) {
        if (compare(it->first, lt_it->first)) { 
            lt_it = it;
        }
    }
    return lt_it;
}

inline std::tuple<std::vector<poly_t>, poly_t> poly_reduce(const poly_t& f, const std::vector<poly_t>& G, 
    bool (*compare)(const monomian_t&, const monomian_t&))
{
    size_t n = G.size();
    std::vector<poly_t> q(n); 
    poly_t r;
    poly_t p = f; 

    while (!p.empty()) {
        auto lt_p_it = get_lt(p, compare);
        const monomian_t lm_p = lt_p_it->first; 
        int64_t lc_p = lt_p_it->second; 
        
        bool divided = false;
        for (size_t i = 0; i < n; ++i) {
            if (G[i].empty()) continue;
            
            auto lt_g_it = get_lt(G[i], compare);
            const auto& lm_g = lt_g_it->first; 
            int64_t lc_g = lt_g_it->second; 
            
            bool divisible = true;
            for (size_t j = 0; j < lm_p.size(); ++j) {
                if (lm_p[j] < lm_g[j]) {
                    divisible = false;
                    break;
                }
            }
            
            if (divisible) {
                monomian_t q_mon;
                for (size_t j = 0; j < lm_p.size(); ++j) {
                    q_mon.push_back(lm_p[j] - lm_g[j]);
                }
                
                int64_t q_coef = lc_p / lc_g;
                q[i][q_mon] += q_coef;
                
                for (const auto& [mon_g, coef_g] : G[i]) {
                    monomian_t new_mon;
                    for (size_t j = 0; j < mon_g.size(); ++j) {
                        new_mon.push_back(q_mon[j] + mon_g[j]);
                    }
                    p[new_mon] -= coef_g * q_coef;
                    if (p[new_mon] == 0) p.erase(new_mon);
                }
                
                divided = true;
                break;
            }
        }
        
        if (!divided) {
            r[lm_p] += lc_p;
            p.erase(lm_p); 
        }
    }

    return {q, r}; 
}

#endif