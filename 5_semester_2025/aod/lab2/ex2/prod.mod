# Rafał Włodarczyk 279762
# Zadanie 2 - Model

# --- Parameters Declaration ---

# set of machines and set of products
set Machines;
set Products;

# max production per product
# cost of manufacturing product p on machine m 
# machine cost per hour, and total worktime
# material cost per product p
# revenue per product

param max_production{Products} >= 0;
param prod{Products, Machines} >= 0;
param machine_cost{Machines} >= 0;
param max_machine_time;
param cost{Products} >= 0;
param revenue{Products} >= 0;

# --- Decision Variables ---

# production per product p
var x{Products} >= 0;

# for each machine machine time cannot exceed max_machine_time
s.t. machine_time{m in Machines}:
    sum{p in Products} prod[p, m] * x[p] <= max_machine_time * 60; # convert to minutes

# for each product cannot exceed maximum production count
s.t. max_prod{p in Products}:
    x[p] <= max_production[p];


# --- Objective Function ----

maximize profit:
    sum{p in Products} (revenue[p] - cost[p]) * x[p] -
    sum{m in Machines} machine_cost[m] * (sum{p in Products} prod[p, m] * x[p]) / 60;

# --- Results ---

solve; 

# optimal production quantities
printf "\nOptimal production quantities:\n";
for {p in Products} {
    printf "Product %s: %8.2f\n", p, x[p];
}

# production cost
printf "\nProduction cost per product:\n";
for {p in Products} {
    printf "Product %s: %8.2f\n", p, cost[p] * x[p];
}

# machine usage and cost
printf "\nMachine usage and cost:\n";
for {m in Machines} {
    printf "Machine %s: %8.2f minutes, cost: %8.2f\n", 
        m, 
        sum{p in Products} prod[p, m] * x[p], 
        machine_cost[m] * (sum{p in Products} prod[p, m] * x[p]) / 60;
}

# total profit
printf "\nTotal profit: %g\n", profit;

end;
