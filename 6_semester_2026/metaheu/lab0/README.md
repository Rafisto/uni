## Traveling Salesman Problem 

https://cs.pwr.edu.pl/gebala/dyd/am2026/labor0.pdf

Full Graph $G=(V,E)$ with $n$ vertices and $|E|=\frac{n^2-n}{2}$ edges. 
Graphs are symmetric and complete. Each edge $(x,y)\in e$ has a weight $w(x,y)$, 
which is the cost of traveling from vertex $x$ to vertex $y$.

The goal is to find a minimal Hamiltonian cycle in $G$, which is a cycle that visits each vertex exactly once and returns to the starting vertex.

There exists $(n-1)!$ possible Hamiltonian cycles in a complete graph with $n$ vertices.

There can be multiple optimal solutions.

Permutation $(1,2,3,4,5,6)$ may represent the cycle $1 \to 2 \to 3 \to 4 \to 5 \to 6 \to 1$, as it is space efficient.

