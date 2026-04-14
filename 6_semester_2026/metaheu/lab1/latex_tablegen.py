#!/usr/bin/python
import sys

opt_values = {
    "western_sahara.tsp": 27603,
    "djibouti.tsp": 6656,
    "qatar.tsp": 9352,
    "uruguay.tsp": 79114,
    "zimbabwe.tsp": 95345,
    "oman.tsp": 86891,
    "canada.tsp": 1290319,
    "tanzania.tsp": 394718,
    "egypt.tsp": 172386,
    "ireland.tsp": 206171
}

city_counts = {
    "western_sahara.tsp": 29,
    "djibouti.tsp": 38,
    "qatar.tsp": 194,
    "uruguay.tsp": 734,
    "zimbabwe.tsp": 929,
    "oman.tsp": 1979,
    "canada.tsp": 4663,
    "tanzania.tsp": 6117,
    "egypt.tsp": 7146,
    "ireland.tsp": 8246
}

def generate_latex_table(file_path, opt_values, city_counts, title="TSP Results"):
    rows = []
    
    with open(file_path, 'r') as f:
        lines = [line.strip() for line in f if line.strip()]
    
    i = 0
    while i < len(lines):
        if lines[i].endswith('.tsp'):
            filename = lines[i]
            
            if i + 2 < len(lines):
                data_parts = lines[i+2].split(';')
                
                if len(data_parts) == 3:
                    mean_dist = data_parts[0]
                    mean_step = data_parts[1]
                    best_dist = data_parts[2]

                    cities = city_counts.get(filename, city_counts.get(filename[6:], "??"))
                    opt = opt_values.get(filename, opt_values.get(filename[6:], "??"))
                    
                    safe_filename = filename.replace('_', r'\_')
                    err = f"{round((abs(float(opt)-float(best_dist)))/float(opt)*100,2)}\\%"
                    
                    row = f"        {safe_filename:<20} & {cities:<4} & {mean_dist:<9} & {mean_step:<8} & {best_dist:<10} & {opt} & {err} \\\\"
                    rows.append(row)
            
            i += 3
        else:
            i += 1

    print(r"\begin{table}[H]")
    print(r"    \centering")
    print(rf"    \caption{{{title}}}")
    print(r"    \begin{tabular}{lcccccc}")
    print(r"        \toprule")
    print(r"        Plik & Liczba Miast & Średni dystans & Średnia liczba kroków & Najlepszy dystans & OPT & Błąd Względny \\")
    print(r"        \midrule")
    
    for r in rows:
        print(r)
        
    print(r"        \bottomrule")
    print(r"    \end{tabular}")
    print(r"\end{table}")

if __name__ == "__main__":
    title = "TSP Results"
    if len(sys.argv) > 1:
        file_path = sys.argv[1]
    if len(sys.argv) > 2:
        title = sys.argv[2]
    generate_latex_table(file_path, opt_values, city_counts, title)