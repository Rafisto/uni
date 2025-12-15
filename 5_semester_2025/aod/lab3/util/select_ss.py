import os
import random
from pathlib import Path

dir = "../ch9-1.1/inputs/"
ss_files = [str(file) for file in Path(dir).rglob('*.ss')]

for file in ss_files:
    with open(file, "r") as f:
        lines = f.readlines()
        lines_with_s = [line for line in lines if line.startswith("s ")]
        
        s_values = [int(line.split()[1]) for line in lines_with_s]
        num_s = len(s_values)
        s_min = min(s_values)        
        s_random = random.sample(s_values, min(5, num_s))
    
        with open(file+"m", "w") as f_out:
            f_out.write(f"p aux sp ss {num_s}\n")
            f_out.write(f"s {s_min}\n")
        
        with open(file+"r", "w") as f_out:
            f_out.write(f"p aux sp ss {num_s}\n")
            for s in s_random:
                f_out.write(f"s {s}\n")
            
        