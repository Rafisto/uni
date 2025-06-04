from typing import Dict, List, Tuple
import numpy as np
import networkx as nx

NODES = 20  # |V| = 20
LINKS = 29  # |E| < 20

# N[n(i,j)] - packet flow intensity matrix - abbr. pfi
# n(i,j) is the number of packets v(i)->v(j)
PACKET_MIN = 0
PACKET_MAX = 100

# Rozważmy model sieci $S = <G,H>$. Przez $N=[n(i,j)]$ będziemy oznaczać macierz natężeń strumienia pakietów,
# gdzie element $n(i,j)$ jest liczbą pakietów przesyłanych (wprowadzanych do sieci) w ciągu sekundy od źródła $v(i)$ do ujścia $v(j)$.

CAPACITY_LEVELS = [10, 100, 1000, 2500, 10000]

def generate_pfi(n=NODES) -> np.ndarray:
    """
    Generate n x n packet flow intensity matrix N[n(i,j)] with random integer values in [PACKET_MIN,PACKET_MAX] 
    """
    matrix = np.random.randint(PACKET_MIN, PACKET_MAX + 1, size=(n, n))

    # n(i,i) = 0 -- loopback traffic not allowed
    np.fill_diagonal(matrix, 0)

    return matrix


def generate_topology(n=NODES, links=LINKS) -> np.ndarray:
    """
    Generate N x N link matrix with random integer values in [0,1]
    This topology assumes symmetrical connections - link(i,j) = link(j,i)

    The total number of 1s in the matrix is twice the number of links
    """
    matrix = np.zeros((n, n), dtype=int)

    # Generate random connections
    for i in range(n):
        while np.sum(matrix[i]) == 0:
            j = np.random.randint(0, n)
            if i != j:
                matrix[i][j] = 1
                matrix[j][i] = 1

    # Add links up to the desired number
    current_links = np.sum(matrix) // 2
    while current_links < links:
        i, j = np.random.randint(0, n, size=2)
        if i != j and matrix[i][j] == 0:
            matrix[i][j] = 1
            matrix[j][i] = 1
            current_links += 1

    return matrix


def topology_to_pairs(topology: np.ndarray) -> list:
    """
    Convert a link matrix to a list of pairs
    """
    pairs = []
    for i in range(len(topology)):
        for j in range(i+1, len(topology)):
            if topology[i][j] == 1:
                pairs.append((i, j))
    return pairs


def topology_to_graph(topology: np.ndarray) -> nx.DiGraph:
    """
    Convert a link matrix to a networkx DiGraph
    """
    return nx.from_numpy_array(topology, create_using=nx.DiGraph)


def pathfind(topology: np.ndarray, source: int, target: int) -> list:
    """
    Find a path from source to target using the topology as the link matrix
    """
    G = nx.from_numpy_array(topology, create_using=nx.DiGraph)
    try:
        return nx.shortest_path(G, source=source, target=target)
    except nx.NetworkXNoPath:
        return []


def path_to_pair_list(path: list) -> list:
    """
    Convert a path to a list of pairs
    """
    return [(path[i], path[i+1]) for i in range(len(path)-1)]


def generate_path_dir(topology: np.ndarray) -> dict:
    """
    Generate a dictionary of paths between nodes
    """
    path_dir = {}
    for i in range(NODES):
        for j in range(NODES):
            if i != j:
                path = pathfind(topology, i, j)
                if path:
                    path_dir[(i, j)] = path_to_pair_list(path)
    return path_dir


def generate_link_load_matrix(topology: np.ndarray, pfi_matrix: np.ndarray, path_dir: dict[(int, int), List[int]]) -> np.ndarray:
    """
    Generate a matrix with the link load for each link in the topology

    @param topology: link matrix
    @param pfi_matrix: packet flow intensity matrix
    @param path_dir: dictionary of paths between nodes
    """
    load = np.zeros((NODES, NODES), dtype=int)

    for i in range(NODES):
        for j in range(NODES):
            if i == j:
                continue
            path = path_dir.get((i, j), [])
            for (a, b) in path:
                load[a][b] += pfi_matrix[i][j]

    return load


def generate_link_load_dir(link_load_matrix) -> Dict[Tuple[int, int], int]:
    """
    Generate a dictionary of link loads
    """
    link_load_dir = {}
    for i in range(NODES):
        for j in range(NODES):
            if i != j:
                link_load_dir[(i, j)] = link_load_matrix[i][j]
    return link_load_dir


def generate_link_capacity_matrix(link_load_matrix: np.ndarray, n=NODES) -> np.ndarray:
    """
    Generate a matrix with the link capacity for each link in the topology

    @param n: number of nodes
    @param link_load_matrix: link load matrix
    """
    capacity = np.zeros((n, n), dtype=int)

    for i in range(n):
        for j in range(n):
            if i == j:
                continue
            levels = [c for c in CAPACITY_LEVELS if c > link_load_matrix[i][j]]
            c = np.min(levels) if levels else np.max(CAPACITY_LEVELS)
        
            capacity[i][j] = c

    return capacity

def calculate_reliability(topology: np.ndarray,
                          pfi_matrix: np.ndarray, 
                          link_load_matrix: np.ndarray,
                          link_capacity_matrix: np.ndarray) -> float:
    """
    Calculate T = 1/G * SUM_e( a(e)/(c(e)/m - a(e))
    G - sum of all packet flows - pfi_matrix.sum()
    a(e) - load on link e
    c(e) - capacity of link e
    m - median packet size
    """ 
    G = pfi_matrix.sum()
    m = 1
    SUM_e = 0
    
    for i in range(NODES):
        for j in range(NODES):
            if i != j and topology[i][j] == 1:
                a = link_load_matrix[i][j]
                c = link_capacity_matrix[i][j]
                if (c / m - a) > 0:
                    SUM_e += a / (c / m - a)
                    
    return 1 / G * SUM_e 


def estimate_reliability(topology: np.ndarray, 
                         pfi_matrix: np.ndarray, 
                         link_load_matrix: np.ndarray,
                         link_capacity_matrix: np.ndarray, 
                         p: float, 
                         T_max: float, 
                         iterations: int = 100) -> float:
    """
    Estimate the reliability of the network.  T < T_max,
    """
    reliable_count = 0

    for _ in range(iterations):
        failed_topology = np.copy(topology)
        for i in range(NODES):
            for j in range(i + 1, NODES):
                if topology[i][j] == 1 and np.random.random() > p:
                    failed_topology[i][j] = 0
                    failed_topology[j][i] = 0

        failed_path_dir = generate_path_dir(failed_topology)
        failed_link_load_matrix = generate_link_load_matrix(failed_topology,
                                                            pfi_matrix,
                                                            failed_path_dir)

        T = calculate_reliability(failed_topology, pfi_matrix, failed_link_load_matrix, link_capacity_matrix)
        
        print(T)

        if T < T_max:
            reliable_count += 1

    return reliable_count / iterations