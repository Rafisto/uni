// API Binding

interface Topology {
    vertices: number[];
    edges: [number, number][];
}

interface SimulationData {
    topology: Topology;
    pfi: number[][];
    path_dir: { key: string; value: string }[];
    link_load: number[][];
    link_capacity: number[][];
    node_load: number[];
}

interface BaseReliability {
    base: number;
}

interface EstimatedReliability {
    estimate: number;
}

// Frontend Model

interface NodeLoad {
    load: number;
    displaySize: number;
    color: string;
}

// NodeInfo

interface NodeInfo {
    id: number;
    connections: number[];
    incoming: number[];
    outgoing: number[];
}

interface LinkInfo {
    id: [number, number];
    capacity: number;
    load: number;
}

export type { Topology, SimulationData, BaseReliability, EstimatedReliability};
export type { NodeLoad, NodeInfo, LinkInfo };
