import Graph from "./graph";
import Info from "./info";
import { useEffect, useState } from "react";
import { fetchSimulation } from "./api/api";
import { nodeLoadToColor, nodeLoadToSize } from "./plot";
import { SimulationData } from "./model";
import "./app.css";

const App = () => {
    const [simulation, setSimulation] = useState<SimulationData>();
    const [nodeID, setNodeID] = useState<number>(-1);
    const [linkID, setLinkID] = useState<[number, number]>([-1, -1]);

    useEffect(() => {
        fetchSimulation().then((data) => {
            setSimulation(data);
        });
    }, []);

    const handleNodeClick = (nodeID: number) => {
        setNodeID(nodeID);
    }

    const handleLinkClick = (linkID: [number, number]) => {
        setLinkID(linkID);
    }

    return (
        <>
            <Info nodeID={nodeID} linkID={linkID} />
            {simulation && (
                <Graph
                    simulation={simulation}
                    nodeLoad={simulation.node_load.map((load, index) => ({
                        load,
                        displaySize: nodeLoadToSize(simulation.node_load)[
                            index
                        ],
                        color: nodeLoadToColor(simulation.node_load)[index],
                    }))}
                    setNodeID={handleNodeClick}
                    setLinkID={handleLinkClick}
                />
            )}
        </>
    );
};

export default App;
