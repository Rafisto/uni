# Rafal Wlodarczyk 279762
# Exercise 6 - Model

param m;
param n;
param range;

param containers{1..m, 1..n} >= 0;

# --- Decision Variables ---

var cameras{1..m, 1..n} >= 0, integer;

# --- Constraints ---

# camera not lie on a container
s.t. camera_not_on_container{i in 1..m, j in 1..n: containers[i,j] = 1}:
    cameras[i,j] = 0;

# at least camera sees a container
s.t. at_least_a_camera_per_container{i in 1..m, j in 1..n: containers[i,j] = 1}:
    (
        sum {di in -range..range: di != 0 and 1 <= i+di and i+di <= m and containers[i+di, j] == 0} cameras[i+di, j]
        +
        sum {dj in -range..range: dj != 0 and 1 <= j+dj and j+dj <= n and containers[i, j+dj] == 0} cameras[i, j+dj]
    ) >= 1;

# --- Objective Function ---

minimize total_cameras:
    sum {i in 1..m, j in 1..n} cameras[i,j];


# --- Results ---

solve;
display total_cameras;
printf "\n";
for {i in 1..m} {
    for {j in 1..n} {
        printf
            (if containers[i,j] = 1 then "x "
             else if cameras[i,j] = 1 then "* "
             else ". ");
    }
    printf "\n";
}
printf "\nLegend:\n";
printf "x - container\n";
printf "* - camera\n";
printf ". - empty space\n";

end;
