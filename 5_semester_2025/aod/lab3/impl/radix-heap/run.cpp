#include <iostream>
#include <fstream>
#include <numeric>
#include <string>
#include <vector>
#include <chrono>

#include "graph.hpp"
#include "dijkstra.hpp"

void run_ss(const std::string& gr_file, const std::string& ss_file, const std::string& oss_file) {    
    std::ifstream gr_file_stream(gr_file);
    if (!gr_file_stream.is_open()) {
        std::cerr << "Error: Unable to open graph file: " << gr_file << "\n";
        return;
    }

    std::ifstream ss_file_stream(ss_file);
    if (!ss_file_stream.is_open()) {
        std::cerr << "Error: Unable to open source file: " << ss_file << "\n";
        return;
    }

    std::ofstream oss_file_stream(oss_file);
    if (!oss_file_stream.is_open()) {
        std::cerr << "Error: Unable to open output file: " << oss_file << "\n";
        return;
    }

    Graph graph;
    int nodes, edges;
    long long min_cost = INT_MAX, max_cost = INT_MIN;
    std::vector<int> sources;

    while(!gr_file_stream.eof()) {
        std::string line;
        std::getline(gr_file_stream, line);
        
        if (line.starts_with("c")) {
            continue;
        } else if (line.starts_with("p")) {
            sscanf(line.c_str(), "p sp %d %d", &nodes, &edges);
            graph = Graph(nodes + 1);
        } else if (line.starts_with("a")) {
            int from, to, weight;
            sscanf(line.c_str(), "a %d %d %d", &from, &to, &weight);
            graph[from].push_back({to, weight});
            min_cost = std::min(min_cost, static_cast<long long>(weight));
            max_cost = std::max(max_cost, static_cast<long long>(weight));
        }
    }

    while(!ss_file_stream.eof()) {
        std::string line;
        std::getline(ss_file_stream, line);

        if (line.starts_with("c")) {
            continue;
        } else if (line.starts_with("p")) {
            int sources_count;
            sscanf(line.c_str(), "ss %d", &sources_count);
        } else if (line.starts_with("s")) {
            int source;
            sscanf(line.c_str(), "s %d", &source);
            sources.push_back(source);
        }
    }

    std::vector<double> times;
    times.reserve(sources.size());

    oss_file_stream << "p res sp ss dikstra\n";
    oss_file_stream << "f " << gr_file << " " << ss_file << "\n";

    for (int src : sources) {
        Dijkstra dijkstra(nodes + 1);

        auto t0 = std::chrono::high_resolution_clock::now();
        dijkstra.dijkstra(graph, src);
        auto t1 = std::chrono::high_resolution_clock::now();

        std::chrono::duration<double, std::milli> dt = t1 - t0;
        times.push_back(dt.count());

        oss_file_stream << "s " << src << " t " << dt << "\n";
    }

    double avg_time = std::accumulate(times.begin(), times.end(), 0.0) / times.size();

    oss_file_stream << "g " << nodes << " " << edges << " " << min_cost << " " << max_cost << "\n";
    oss_file_stream << "t " << avg_time << "\n";
}

void run_p2p(const std::string& gr_file, const std::string& p2p_file, const std::string& op2p_file) {
        std::ifstream gr_file_stream(gr_file);
    if (!gr_file_stream.is_open()) {
        std::cerr << "Error: Unable to open graph file: " << gr_file << "\n";
        return;
    }

    std::ifstream p2p_file_stream(p2p_file);
    if (!p2p_file_stream.is_open()) {
        std::cerr << "Error: Unable to open source file: " << p2p_file << "\n";
        return;
    }

    std::ofstream op2p_file_stream(op2p_file);
    if (!op2p_file_stream.is_open()) {
        std::cerr << "Error: Unable to open output file: " << op2p_file << "\n";
        return;
    }

    Graph graph;
    int nodes, edges;
    long long min_cost = INT_MAX, max_cost = INT_MIN;
    long long min_node = INT_MAX, max_node = INT_MIN;
    std::vector<std::tuple<int, int>> pairs;

    while(!gr_file_stream.eof()) {
        std::string line;
        std::getline(gr_file_stream, line);
        
        if (line.starts_with("c")) {
            continue;
        } else if (line.starts_with("p")) {
            sscanf(line.c_str(), "p sp %d %d", &nodes, &edges);
            graph = Graph(nodes + 1);
        } else if (line.starts_with("a")) {
            int from, to, weight;
            sscanf(line.c_str(), "a %d %d %d", &from, &to, &weight);
            graph[from].push_back({to, weight});
            min_cost = std::min(min_cost, static_cast<long long>(weight));
            max_cost = std::max(max_cost, static_cast<long long>(weight));
        }
    }

    while(!p2p_file_stream.eof()) {
        std::string line;
        std::getline(p2p_file_stream, line);

        if (line.starts_with("c")) {
            continue;
        } else if (line.starts_with("p")) {
            int pairs_count;
            sscanf(line.c_str(), "p2p %d", &pairs_count);
        } else if (line.starts_with("q")) {
            long long source, target;
            sscanf(line.c_str(), "q %lld %lld", &source, &target);

            if (source < min_node) min_node = source;
            if (target > max_node) max_node = target;

            pairs.emplace_back(source, target);
        }
    }

    if (pairs.size() == 0) pairs.push_back({1, nodes});

    std::vector<double> times;
    times.reserve(pairs.size());

    op2p_file_stream << "p res sp p2p dikstra\n";
    op2p_file_stream << "f " << gr_file << " " << p2p_file << "\n";

    for (const auto& [src, target] : pairs) {
        Dijkstra dijkstra(nodes + 1);

        auto t0 = std::chrono::high_resolution_clock::now();
        dijkstra.dijkstra(graph, src, target);
        auto t1 = std::chrono::high_resolution_clock::now();

        std::chrono::duration<double, std::milli> dt = t1 - t0;
        times.push_back(dt.count());

        long long distance = dijkstra.getDistance(target);
        if (distance == INT_MAX) distance = -1;

        op2p_file_stream << "q " << src << " " << target << " d " << distance << " t " << dt.count() << "\n";
    }

    double avg_time = std::accumulate(times.begin(), times.end(), 0.0) / times.size();

    op2p_file_stream << "g " << nodes << " " << edges << " " << min_cost << " " << max_cost << " " << min_node << " " << max_node << "\n";
    op2p_file_stream << "t " << avg_time << "\n";
}

int main(int argc, char* argv[]) {
    if (argc < 6) {
        std::cerr << "Usage: radix_heap -d <data_file> -ss <source_file> -oss <output_file>\n";
        std::cerr << "Usage: radix_heap -d <data_file> -p2p <pairs_file> -op2p <output_file>\n";
        return 1;
    }

    std::string mode = argv[3];
    if (mode == "-ss" && argc == 7) {
        std::string dataFile = argv[2];
        std::string sourceFile = argv[4];
        std::string outputFile = argv[6];
        run_ss(dataFile, sourceFile, outputFile);
    } else if (mode == "-p2p" && argc == 7) {
        std::string dataFile = argv[2];
        std::string pairsFile = argv[4];
        std::string outputFile = argv[6];
        run_p2p(dataFile, pairsFile, outputFile);
    } else {
        std::cerr << "Invalid arguments.\n";
        return 1;
    }

    return 0;
}