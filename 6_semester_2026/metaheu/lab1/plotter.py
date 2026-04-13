#!/usr/bin/python
import sys
from typing import List
import os
import matplotlib.pyplot as plt

prefix = "task1"
if len(sys.argv) > 1:
    print(f"Using prefix from command line argument: {sys.argv[1]}")
    prefix = sys.argv[1]

def find_lines_with_tsp(lines: List[str]) -> List[int]:
    return [i for i, line in enumerate(lines) if 'tsp' in line]

def find_tsp_name(line: str) -> str:
    if "File: " in line:
        return line[6:-1]
    return ""


os.makedirs("output", exist_ok=True)

if not sys.stdin.isatty():
    lines = sys.stdin.readlines()
    sections = find_lines_with_tsp(lines)
    for i in range(len(sections)):

        start = sections[i] + 1
        end = sections[i + 1] if i + 1 < len(sections) else len(lines)
        section_content = lines[start:end]
        
        graph = []
        for line in section_content[2:]:
            line = line.split(';')
            idx = int(line[0])
            x = float(line[1])
            y = float(line[2])
            graph.append((idx, x, y))


        filename = find_tsp_name(lines[sections[i]])
        plt.figure(figsize=(8, 6))
        x_coords = [coord[1] for coord in graph]
        y_coords = [coord[2] for coord in graph]
        plt.plot(y_coords + [y_coords[0]], x_coords + [x_coords[0]], 'b-o', markersize=1)
        plt.xlabel('X')
        plt.ylabel('Y')
        plt.title(f'TSP Randomized Best Effort file="{filename}"')
        plt.grid(True)
        plt.savefig(f"output/{prefix}_{filename}.png")
