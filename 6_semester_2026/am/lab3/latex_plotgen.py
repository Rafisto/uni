#!/usr/bin/python
names = [
    "western_sahara",
    "djibouti",
    "qatar",
    "uruguay",
    "zimbabwe",
    "oman",
    "canada",
    "tanzania",
    "egypt",
    "ireland",
]

methods = [
    "pmx",
    "ox",
    "memetic",
    "island"
]

for n in names:
    name = n.replace("_", " ").title()
    print(f"\\subsection{{{name}}}")
    print(f"\\begin{{figure}}[H]")
    print(f"    \\centering")
    for m in methods:
        print(f"    \\begin{{minipage}}{{0.24\\textwidth}}")
        print(f"        \\centering")
        print(
            f"        \\includegraphics[width=\\textwidth]{{results/{n}.tsp_{m}.png}}")
        print(f"        \\caption*{{{name}({m})}}")
        print(f"        \\label{{fig:{name}_{m}}}")
        print(f"    \\end{{minipage}}")
    print(f"\\end{{figure}}")
