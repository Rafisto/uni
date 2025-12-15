import os
import random
from pathlib import Path

dir = "../ch9-1.1/inputs/"
p2p_files = [str(file) for file in Path(dir).rglob('*.p2p')]

for file in p2p_files:
    with open(file, "r") as f:
        lines = f.readlines()
        lines_with_q = [line for line in lines if line.startswith("q ")]

        q_pairs = [(int(line.split()[1]), int(line.split()[2])) for line in lines_with_q]
        num_q = len(q_pairs)
        
        rand_pairs = random.sample(q_pairs, min(4, num_q))
        
        with open(file+"lohi", "w") as f_out:
            f_out.write(f"p aux sp p2p {num_q}\n")
        
        with open(file+"rand", "w") as f_out:
            f_out.write(f"p aux sp p2p {num_q}\n")
            for u, v in rand_pairs:
                f_out.write(f"q {u} {v}\n")
            
        