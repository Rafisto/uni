import { useRef, useEffect } from "react";
import ReactECharts from "echarts-for-react";
import { NodeLoad, SimulationData } from "./model";
import { linkLoadToColor, linkLoadToWidth } from "./plot";

interface IGraph {
    simulation: SimulationData;
    nodeLoad: NodeLoad[];
    setNodeID: (nodeID: number) => void;
    setLinkID: (linkID: [number, number]) => void;
}

const GraphTooltip = (
    nmatrix: number[][],
    cmatrix: number[][],
    name: string
) => {
    let [a, b] = name.split(" > ").map((x) => parseInt(x));
    return `Link ${a}->${b}: <b>${nmatrix[a][b]} packets/s</b> 
  <br/>Link ${b}->${a}: <b>${nmatrix[b][a]} packets/s</b>
  <br/>Link Capacity ${a}->${b}: <b>${cmatrix[a][b]}</b>
  <br/>Link Capacity ${b}->${a}: <b>${cmatrix[b][a]}</b>`;
};

const Graph = ({ simulation, nodeLoad, setNodeID, setLinkID }: IGraph) => {
    // https://github.com/hustcc/echarts-for-react/issues/285 -- ECharts for React does not support event binding
    const chartRef = useRef<any>(null);

    useEffect(() => {
        const instance = chartRef.current.getEchartsInstance();
        instance.on("click", (params: any) => {
            if (params.dataType === "node") {
                console.log(`Clicked on node: ${params.data.name}`);
                setNodeID(parseInt(params.data.name.split(" ")[1]));
            } else if (params.dataType === "edge") {
                console.log(
                    `Clicked on edge: ${params.data.source} > ${params.data.target}`
                );
                let [a, b] = params.data.name
                    .split(" > ")
                    .map((x: string) => parseInt(x));
                setLinkID([a, b]);
            }
        });
    }, [setNodeID]);

    const option = {
        tooltip: {
            trigger: "item",
        },
        series: [
            {
                type: "graph",
                layout: "force",
                roam: true,
                draggable: true,
                force: {
                    repulsion: 1500,
                    edgeLength: 100,
                },
                label: {
                    show: true,
                    position: "right",
                    formatter: "{b}",
                    fontSize: 12,
                },
                lineStyle: {
                    color: "#aaa",
                    width: 2,
                },
                itemStyle: {
                    color: "#000",
                    borderColor: "#000",
                    borderWidth: 1,
                },
                data: simulation.topology.vertices.map((vertex) => ({
                    name: `Host ${vertex}`,
                    value: `${nodeLoad[vertex].load} packets/s`,
                    symbolSize: nodeLoad[vertex].displaySize,
                    itemStyle: {
                        color: nodeLoad[vertex].color,
                    },
                    label: {
                        show: true,
                        textStyle: {
                            color: "#fff",
                            textBorderColor: "transparent",
                            textBorderWidth: 0,
                        },
                    },
                })),
                links: [
                    ...simulation.topology.edges.map(([from, to]) => ({
                        source: `Host ${from.toString()}`,
                        target: `Host ${to.toString()}`,
                        lineStyle: {
                            width: linkLoadToWidth(
                                Number(
                                    (simulation.link_load[from][to] +
                                        simulation.link_load[to][from]) /
                                        2
                                )
                            ),
                            color: linkLoadToColor(
                                Number(
                                    (simulation.link_load[from][to] +
                                        simulation.link_load[to][from]) /
                                        2
                                )
                            ),
                            type: "solid",
                        },
                        tooltip: {
                            formatter: () =>
                                GraphTooltip(
                                    simulation.link_load,
                                    simulation.link_capacity,
                                    `${from} > ${to}`
                                ),
                        },
                    })),
                ],
            },
        ],
    };

    return (
        <ReactECharts
            option={option}
            style={{ height: "100vh", width: "100vw" }}
            ref={chartRef}
        />
    );
};

export default Graph;
