# Rafal Wlodarczyk 279762
# Exercise 1 - Model

# --- Parameters Declaration ---

# lists of suppliers and end users
set SUPPLIERS;
set AIRPORTS;

# maximum sell-capacity of each supplier
param supply{SUPPLIERS} >= 0;

# demand of each end user
param demand{AIRPORTS} >= 0;

# fuel and transport cost matrix (how much from supplier s to airport a)
param cost{SUPPLIERS, AIRPORTS} >= 0;

# --- Decision Variables --- 

# volume-count matrix for each supplier->airport combination
var x{SUPPLIERS, AIRPORTS} >= 0;

# --- Constraints ---

# for each supplier sell volume cannot exceed its maximum sell-capacity
s.t. supply_constraint{s in SUPPLIERS}:
    sum{a in AIRPORTS} x[s, a] <= supply[s];

# for each end user buy volume must be at least its demand
s.t. demand_constraint{a in AIRPORTS}:
    sum{s in SUPPLIERS} x[s, a] >= demand[a];

# --- Objective Function ---

minimize total_cost:
    sum{s in SUPPLIERS, a in AIRPORTS} cost[s, a] * x[s, a];

# --- Results ---

solve;

# volume-count matrix, each supplier->airport combination
printf "\nOptimal shipment quantities:\n";
for {s in SUPPLIERS, a in AIRPORTS} {
    printf "x[%s,%s] = %8.2f\n", s, a, x[s,a];
}

# how much fuel did each supplier sell
printf "\nTotal shipped per supplier:\n";
for {s in SUPPLIERS} {
    printf "%s: %8.2f\n", s, sum{a in AIRPORTS} x[s,a];
}

printf "\nTotal cost: %d\n", total_cost;

end;
