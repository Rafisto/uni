# Rafal Wlodarczyk 279762
# Exercise 5 - Model

# https://iuuk.mff.cuni.cz/~bohm/texts/mathprog_intro.html

# --- Parameters ---

# define time and region
set time;
set region;

# define min, max cars per time and region
param min_radiowozy{time, region} >= 0;
param max_radiowozy{time, region} >= 0;

# define min total per time, and min total per region
param min_radiowozy_time{time} >= 0;
param min_radiowozy_region{region} >= 0;

# --- Decision Variables ---

var occupancy{time, region};

# --- Constraints ----

# ensure min per time and region is set
s.t. constraint_bazowy_dolny{z in time, d in region}:
    occupancy[z,d] >= min_radiowozy[z,d];

# ensure max time per region is set
s.t. constraint_bazowy_gorny{z in time, d in region}:
    occupancy[z,d] <= max_radiowozy[z,d];

# ensure min sum per region is set
s.t. min_radiowozy_na_dzielnice{d in region}:
    sum {z in time} occupancy[z,d] >= min_radiowozy_region[d];

# ensure min sum per time is set
s.t. min_radiowozy_na_zmiane{z in time}:
    sum {d in region} occupancy[z,d] >= min_radiowozy_time[z]; 

# --- Objective Function ---

minimize zestaw_radiowozow: 
    sum {z in time, d in region} occupancy[z,d];

# --- Results ---

solve;
printf "Occupancy Matrix:\n";
for {z in time} {
    for {d in region} {
        printf "%d ", occupancy[z, d];
    }
    printf "\n";
}

display sum {z in time, d in region} occupancy[z,d];

end;
