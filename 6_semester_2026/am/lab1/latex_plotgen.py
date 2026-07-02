#!/usr/bin/python
prefixes = ["task1", "task2", "task3"]
endings = ["western_sahara.tsp", "djibouti.tsp", "qatar.tsp", "uruguay.tsp",
           "zimbabwe.tsp", "oman.tsp", "canada.tsp", "tanzania.tsp", "egypt.tsp", "ireland.tsp"]

for e in endings:
    print(f"\\subsection{{{e}}}")
    print(f"\\begin{{figure}}[H]")
    print(f"    \\centering")
    for p in prefixes:
        print(f"    \\begin{{minipage}}{{0.32\\textwidth}}")
        print(f"        \\centering")
        print(f"        \\includegraphics[width=\\textwidth]{{output/{p}_{e}.png}}")
        print(f"        \\caption*{{{p}({e})}}")
        print(f"        \\label{{fig:{p}_{e}}}")
        print(f"    \\end{{minipage}}")
    print(f"\\end{{figure}}")