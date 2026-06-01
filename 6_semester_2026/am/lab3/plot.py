import matplotlib.pyplot as plt
import re

def read_tsp_file(filename):
    coords = {}
    dimension = 0
    reading_coords = False
    
    with open(filename, 'r') as f:
        for line in f:
            line = line.strip()
            
            if line.startswith('DIMENSION'):
                dimension = int(re.findall(r'\d+', line)[0])
            
            if line.startswith('NODE_COORD_SECTION'):
                reading_coords = True
                continue
            
            if reading_coords and line and not line.startswith('EOF'):
                parts = line.split()
                if len(parts) >= 3:
                    node_id = int(parts[0])
                    x = float(parts[1])
                    y = float(parts[2])
                    coords[node_id] = (x, y)
            
            if line == 'EOF':
                break
    
    return coords, dimension

def plot_tsp_tour(coords, permutation, title, distance, ax=None):
    if ax is None:
        fig, ax = plt.subplots(figsize=(10, 8))
    
    tour_coords = [coords[node+1] for node in permutation]
    
    tour_coords.append(tour_coords[0])
    
    x_coords = [p[0] for p in tour_coords]
    y_coords = [p[1] for p in tour_coords]
    
    ax.plot(x_coords, y_coords, 'b-', linewidth=1.5, alpha=0.7, label=f'Tour (Distance: {distance:.0f})')
    
    ax.set_xlabel('X Coordinate')
    ax.set_ylabel('Y Coordinate')
    ax.set_title(title)
    ax.grid(True, alpha=0.3)
    ax.legend()
    ax.set_aspect('equal')
    
    return ax

def main():
    outfile = open('out','r').read().strip().split('\n')
    for l, line in enumerate(outfile):
        if l == 0:
            continue
        line = line.split('|')
        permutation = [int(i) for i in line[1].split(':')]
        line = line[0].split(';')
        filename = line[0]
        n = int(line[1])
        algorithm = line[2]
        distance = int(line[3])
                
        coords, dimension = read_tsp_file("data/"+filename)
        plot_tsp_tour(coords, permutation, f"{filename} ({algorithm}) n={n}", distance)
        plt.savefig(f"results/{filename}_{algorithm}.png")

if __name__ == "__main__":
    main()