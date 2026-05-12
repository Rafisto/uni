./plotter.py "task2" "Full Local Search" < tabu.res
# ./plotter.py "task2" "n-Randomized Local Search" < task2.res
# ./plotter.py "task3" "MST Local Search" < task3.res
./latex_plotgen.py > task_plots.tex

./latex_tablegen.py tabu.res "Tabu Search" > task2_table.tex
# ./latex_tablegen.py task2.res "n-Randomized Local Search" > task2_table.tex
# ./latex_tablegen.py task3.res "MST Local Search" > task3_table.tex