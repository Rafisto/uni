from flask import Flask, jsonify, request
from logic import *
from flask_cors import CORS

app = Flask(__name__)
CORS(app, resources={r"/*": {"origins": "*"}})

topology = generate_topology()

packet_flow_intensity_matrix = generate_pfi()
path_dir = generate_path_dir(topology)
link_load_matrix = generate_link_load_matrix(
    topology, packet_flow_intensity_matrix, path_dir)

link_capacity_matrix = generate_link_capacity_matrix(link_load_matrix)


@app.route('/simulation', methods=['GET'])
def get_simulation():
    return {
        "topology": {
            "vertices": [i for i in range(len(topology))],
            "edges": topology_to_pairs(topology)
        },
        "pfi": packet_flow_intensity_matrix.tolist(),
        "path_dir": [{"key": key, "value": value} for key, value in path_dir.items()],
        "link_load": link_load_matrix.tolist(),
        "link_capacity": link_capacity_matrix.tolist(),
        "node_load": link_load_matrix.sum(axis=1).tolist()
    }, 200
    

@app.route('/reliability/base', methods=['GET'])
def get_base_reliablity():
    return {
        "base": calculate_reliability(topology=topology,
                                      pfi_matrix=packet_flow_intensity_matrix,
                                      link_load_matrix=link_load_matrix,
                                      link_capacity_matrix=link_capacity_matrix)
    }, 200

@app.route('/reliability/estimate', methods=['GET'])
def get_estimate_reliablity():
    return {
        "estimate": estimate_reliability(topology=topology,
                                         pfi_matrix=packet_flow_intensity_matrix,
                                         link_load_matrix=link_load_matrix,
                                         link_capacity_matrix=link_capacity_matrix,
                                         p=request.args.get('p', type=float, default=0.9),
                                         T_max=request.args.get('tmax', type=float, default=100.0),
                                         iterations=request.args.get('iterations', type=int, default=100))
    }, 200

@app.route('/nodes/<id>', methods=['GET'])
def get_node(id):
    return {
        "id": id,
        "connections": [i for i in range(len(topology)) if topology[int(id)][i] == 1],
        "incoming": link_load_matrix[:, int(id)].tolist(),
        "outgoing": link_load_matrix[int(id), :].tolist()
    }, 200


@app.route('/links/<fm>/<to>', methods=['GET'])
def get_link(fm, to):
    return {
        "id": f"{fm} > {to}",
        "capacity": link_capacity_matrix[int(fm)][int(to)],
        "load": link_load_matrix[int(fm)][int(to)]
    }, 200


@app.route('/topology', methods=['GET'])
def get_topology():
    return {
        "vertices": [i for i in range(len(topology))],
        "edges": topology_to_pairs(topology)
    }, 200


@app.route('/pfi', methods=['GET'])
def get_pfi():
    return jsonify(packet_flow_intensity_matrix.tolist())


@app.route('/path_dir', methods=['GET'])
def get_path_dir():
    pdir = []
    for key, value in path_dir.items():
        pdir.append({"key": key, "value": value})

    return jsonify(pdir)


@app.route('/link_load_matrix', methods=['GET'])
def get_link_load_matrix():
    return jsonify(link_load_matrix.tolist())


if __name__ == '__main__':
    app.run(debug=True)
