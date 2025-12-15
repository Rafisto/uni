# Rafal Wlodarczyk 279762
# Exercise 4 - Model, remove R_ij integer restriction

# --- Parameters Declaration ---
# define graph vertices - cities
set Cities;

# define graph edges via matrix representation
# - cost (minimize over)
# - time (must not exceed)
param cost{Cities, Cities} >= 0, default 9999;
param time{Cities, Cities} >= 0, default 9999;

# must not exceed the following time
param max_time >= 0;

# where we start and where we end
param start_city symbolic, in Cities;
param end_city symbolic, in Cities;

# --- Decision Variables ---

# for each edge we either take it to our route or we don't
# its union will hopefully yield the shortest path

# here it is not an binary variable anymore
var route{Cities, Cities} >= 0;

# --- Constraints ---

# at least one edge must connect to the start city
s.t. leave_start_city:
    sum {j in Cities} route[start_city, j] = 1;

# at least one edge must connect to the end city
s.t. enter_end_city:
    sum {i in Cities} route[i, end_city] = 1;

# for every other vertex if we enter, we also must exit
s.t. flow_conservation {k in Cities: k != start_city and k != end_city}:
    sum {i in Cities} route[i, k] = sum {j in Cities} route[k, j];

# cumulative route time (sum of cost by edges) must not be greater than max_time
s.t. time_limit:
    sum {i in Cities, j in Cities} time[i,j] * route[i,j] <= max_time;

# --- Objective Function ---

minimize total_cost:
    sum {i in Cities, j in Cities} cost[i,j] * route[i,j];

# --- Result ---

solve;

for {i in Cities, j in Cities: route[i,j] >= 0.01} {
    printf "%8.2f %s -> %s\n", route[i,j], i, j;
}

printf "Total cost: %d\n", total_cost;
printf "Total time: %d\n", sum {i in Cities, j in Cities} time[i,j] * route[i,j];

end;
