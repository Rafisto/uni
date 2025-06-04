import time
import random
from libparams import MEDIUM_LENGTH, MAX_ATTEMPTS
from libnode import Node, NodeState
from libcolor import Printer

def propagate_signal(medium, signals, tick):
    new_signals = []
    signal_ages = {}
    
    for signal in signals:
        pos, direction, source, created = signal
        age = tick - created
        signal_ages[(pos, direction, source)] = age
    
    for signal in signals:
        pos, direction, source, created = signal
        new_pos = pos + direction * 1
        if 0 <= new_pos < len(medium):
            if medium[new_pos] is None:
                medium[new_pos] = (source, tick - created)
            else:
                if medium[new_pos][0] != source:
                    medium[new_pos] = ("x", tick - created)
            new_signals.append((new_pos, direction, source, created))
    return new_signals

def is_medium_idle(medium, position):
    return medium[position] is None or medium[position][0] is None

def run_simulation(nodes):
    medium = [None] * MEDIUM_LENGTH
    signals = []
    log = []
    success = 0
    node_states_per_tick = [{node.name: NodeState.IDLE for node in nodes}]
    node_attempts_per_tick = [{node.name: 0 for node in nodes}]
    node_next_transmission = [{node.name: node.backoff for node in nodes}]
    positions = [" " for _ in range(MEDIUM_LENGTH)]
    
    for node in nodes:
        positions[node.position] = node.name

    tick = 0
    while True:
        tick += 1
        log.append("")
        
        signals = propagate_signal(medium, signals, tick)

        for node in nodes:
            if tick == node.transmission_tick and node.state == NodeState.IDLE:
                if is_medium_idle(medium, node.position):
                    medium[node.position] = (node.name, 0)
                    signals.append((node.position, -1, node.name, tick))
                    signals.append((node.position, 1, node.name, tick))
                    node.state = NodeState.TRANSMITTING
                else:
                    node.transmission_tick += 1

            elif node.state == NodeState.TRANSMITTING:
                if medium[node.position] is not None and medium[node.position][0] not in [node.name, None]:
                    node.state = NodeState.BACKOFF
                    if node.attempts < MAX_ATTEMPTS:
                        node.backoff = 2 * MEDIUM_LENGTH * random.randint(0, 2 ** node.attempts)
                        node.transmission_tick = tick + 2 * MEDIUM_LENGTH + 1 + node.backoff
                    node.attempts += 1
                    node.state = NodeState.JAMMING
                    node.jam_start = tick
                    medium[node.position] = ("x", 0)
                    log[-1] += f"{node} collision "
                else:
                    if tick >= node.transmission_tick + 2 * MEDIUM_LENGTH:
                        node.state = NodeState.SUCCESS
                        success += 1
                        log[-1] += f"{node} successful "
                    else:
                        medium[node.position] = (node.name, 0)
                        signals.append((node.position, -1, node.name, tick))
                        signals.append((node.position, 1, node.name, tick))
            elif node.state == NodeState.JAMMING:
                if tick >= node.jam_start + 2 * MEDIUM_LENGTH:
                    node.state = NodeState.IDLE
                else:
                    medium[node.position] = ("x", 0)
                    signals.append((node.position, -1, "x", tick))
                    signals.append((node.position, 1, "x", tick))

        node_attempts_per_tick.append({node.name: node.attempts for node in nodes})
        node_states_per_tick.append({node.name: node.state for node in nodes})
        node_next_transmission.append({node.name: node.transmission_tick for node in nodes})
        colored_medium = Printer.colorize_medium(medium)
        log[-1] = colored_medium + " " + log[-1]

        medium = [None for _ in medium]

        if success == len(nodes):
            print(success)
            break

    print("\nSteps")
    for i in range(len(log) - 1, 0, -1):
        if log[i] == "".join(["_" for _ in range(MEDIUM_LENGTH)]) + " ":
            log.pop(i)
        else:
            break

    with open("output.txt", "w") as f:
        for line in log:
            clean_line = re.sub(r'\033\[[0-9;]*[mK]', '', line)
            f.write(clean_line + "\n")

    for i, line in enumerate(log):
        print("\033[2J\033[H", end="")
        print(f"           {"".join(positions)[:MEDIUM_LENGTH]}")
        for j in range(max(0, i - 20), i + 1):
            print(f"Tick {str(j).zfill(5)} {log[j]}")

        print("\nNode States:")
        for node in nodes:
            print(f"Node {node.name}: Attempt={node_attempts_per_tick[i][node.name]} Next={node_next_transmission[i][node.name]} State={node_states_per_tick[i][node.name]}")
        time.sleep(0.05)

if __name__ == "__main__":
    import re
    nodes = [
        Node(chr(97+i), random.randint(0, MEDIUM_LENGTH - 1), random.randint(0, 100))
        for i in range(random.randint(8, 10))
    ]
    run_simulation(nodes)