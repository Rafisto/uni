import React, { useEffect, useState } from "react";
import { fetchNode } from "./api/node";
import { NodeInfo } from "./model";
import {
    EstimatedReliabilityQuery,
    fetchBaseReliability,
    fetchReliability,
} from "./api/api";

const divStyle: React.CSSProperties = {
    position: "absolute",
    top: 0,
    right: 0,
    color: "white",
    marginInline: "20px",
    zIndex: 1,
};

interface InfoProps {
    nodeID: number;
    linkID: [number, number];
}

const Info = (p: InfoProps) => {
    const [nodeInfo, setNodeInfo] = useState<NodeInfo>();
    const [baseReliability, setBaseReliability] = useState<number>();
    const [estimatedReliability, setEstimatedReliability] = useState<number>();

    const [query, setQuery] = useState<EstimatedReliabilityQuery>({
        p: 0.9,
        tmax: 0.1,
        iterations: 100,
    });

    useEffect(() => {
        fetchNode(p.nodeID).then((data) => {
            setNodeInfo(data);
        });

        fetchBaseReliability().then((data) => {
            setBaseReliability(data.base);
        });

        fetchReliability(query).then((data) => {
            setEstimatedReliability(data.estimate);
        });
    }, [p.nodeID]);

    const estimateReliability = async () => {
        fetchReliability(query).then((data) => {
            console.log(data);
            setEstimatedReliability(data.estimate);
        });
    }

    const processConnections = (connections: number[]) => {
        return connections
            .map((v, i) => ({ value: v, index: i }))
            .filter((conn) => conn.value !== 0)
            .sort((a, b) => b.value - a.value)
            .map((conn) => (
                <li key={conn.index}>
                    {conn.index}: {conn.value}
                </li>
            ));
    };

    return (
        <div style={divStyle}>
            <p>
                <a href="https://github.com/Rafisto/netsim">@Rafisto</a>
            </p>
            <p>Base {baseReliability}</p>
            <p>Estimated {estimatedReliability}</p>

            <form
                onSubmit={(e) => {
                    e.preventDefault();
                    estimateReliability();
                }}
            >
                <label>
                    Probability (p):
                    <input
                        type="number"
                        step="0.01"
                        value={query.p}
                        onChange={(e) =>
                            setQuery({
                                ...query,
                                p: parseFloat(e.target.value),
                            })
                        }
                    />
                </label>
                <br />
                <label>
                    Tmax:
                    <input
                        type="number"
                        step="0.001"
                        value={query.tmax}
                        onChange={(e) =>
                            setQuery({
                                ...query,
                                tmax: parseFloat(e.target.value),
                            })
                        }
                    />
                </label>
                <br />
                <label>
                    Iterations:
                    <input
                        type="number"
                        value={query.iterations}
                        onChange={(e) =>
                            setQuery({
                                ...query,
                                iterations: parseInt(e.target.value, 10),
                            })
                        }
                    />
                </label>
                <br />
                <button type="submit">Submit</button>
            </form>

            {nodeInfo && (
                <>
                    <p>Node ID: {p.nodeID}</p>
                    <div>
                        Connected to:{" "}
                        <ul>
                            {nodeInfo.connections.map((conn, i) => (
                                <li key={i}>{conn}</li>
                            ))}
                        </ul>
                    </div>
                    <div>
                        Incoming:{" "}
                        <ul>{processConnections(nodeInfo.incoming)}</ul>
                    </div>
                    <div>
                        Outgoing:{" "}
                        <ul>{processConnections(nodeInfo.outgoing)}</ul>
                    </div>
                </>
            )}
        </div>
    );
};

export default Info;
