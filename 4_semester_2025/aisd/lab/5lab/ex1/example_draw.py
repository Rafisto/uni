import sys
import networkx as nx
import matplotlib.pyplot as plt
import numpy as np


def read_graphs_from_pipe():
    lines = sys.stdin.read().splitlines()
    sections = {"ORIGINAL": [], "MST": []}
    current = None
    total_cost = None

    for line in lines:
        if line.startswith("# COST"):
            current = "COST"
        elif line.startswith("# ORIGINAL"):
            current = "ORIGINAL"
        elif line.startswith("# MST"):
            current = "MST"
        elif line.strip():
            if current == "COST":
                total_cost = float(line.strip())
            elif current in sections:
                u, v, w = line.strip().split()
                sections[current].append((int(u), int(v), float(w)))

    return total_cost, sections["ORIGINAL"], sections["MST"]


def build_graph(edge_list):
    G = nx.Graph()
    for u, v, w in edge_list:
        G.add_edge(u, v, weight=w)
    return G


def draw_adjacency_heatmap(G, title, vmin=None, vmax=None, subplot=None):
    if subplot:
        ax = plt.subplot(*subplot)
    else:
        ax = plt.gca()

    nodes = sorted(G.nodes())
    adj_matrix = nx.to_numpy_array(G, nodelist=nodes, weight='weight')

    im = ax.imshow(adj_matrix, cmap='viridis', interpolation='nearest', vmin=vmin, vmax=vmax)
    ax.set_title(title, fontsize=14, fontweight='bold') 

    ax.set_xticks(np.arange(len(nodes)))
    ax.set_xticklabels(nodes, rotation=90)
    ax.set_yticks(np.arange(len(nodes)))
    ax.set_yticklabels(nodes)
    ax.set_xlabel("Node")
    ax.set_ylabel("Node")

    plt.colorbar(im, ax=ax, fraction=0.046, pad=0.04)

    return adj_matrix


def draw_graph(G, title, pos=None, subplot=None):
    if subplot:
        plt.subplot(*subplot)
        plt.text(
            0.95, 0.05, f"Total Cost {total_cost:.2f}",
            transform=plt.gca().transAxes,
            fontsize=10, fontweight='bold',
            color='darkred', ha='right', va='bottom',
            bbox=dict(facecolor='white', alpha=0.8, edgecolor='gray')
        )
    if not pos:
        pos = nx.spring_layout(G)

    degrees = dict(G.degree())
    node_sizes = [100 + degrees[n]*300 for n in G.nodes()]

    nx.draw_networkx_nodes(
        G, pos, node_size=node_sizes,
        node_color='skyblue', edgecolors='navy', linewidths=1.5
    )

    nx.draw_networkx_edges(
        G, pos,
        edge_color='gray', alpha=0.7, width=2,
        arrows=True, arrowsize=20
    )

    nx.draw_networkx_labels(
        G, pos,
        font_size=12,
        font_weight='bold',
        font_color='darkblue'
    )

    plt.title(title, fontsize=16, fontweight='bold')
    plt.axis('off')
    return pos


if __name__ == "__main__":
    total_cost, original_edges, mst_edges = read_graphs_from_pipe()
    print(f"Total Cost: {total_cost}")

    G_original = build_graph(original_edges)
    G_mst = build_graph(mst_edges)

    plt.figure(figsize=(18, 6))
    draw_adjacency_heatmap(G_original, "Original Graph Adjacency Matrix",
                           vmin=0, vmax=1, subplot=(1, 3, 1))
    draw_adjacency_heatmap(G_mst, "Minimum Spanning Tree Adjacency Matrix",
                           vmin=0, vmax=1, subplot=(1, 3, 2))
    pos = draw_graph(G_mst, "Minimum Spanning Tree Graph", subplot=(1, 3, 3))

    plt.tight_layout()
    
    plt.savefig("example_visualization.png", dpi=300)
