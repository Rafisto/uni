set PROJECTS;
set YEARS;

param cost {YEARS, PROJECTS} >= 0;
param profit {PROJECTS} >= 0;
param budget {YEARS} >= 0;

var do {YEARS, PROJECTS} binary;

set YEARS_NO3 := {y in YEARS: y != 3};

s.t. BudgetLimit {y in YEARS_NO3}:
    sum {p in PROJECTS} cost[y,p] * do[y,p] <= budget[y];

s.t. BudgetLimit_Year3:
    sum {p in PROJECTS} cost[3,p] * do[3,p] <= budget[3] + (do[1,4] + do[2,4] + do[3,4]) * profit[4];

s.t. ABLimit {y in YEARS}:
    do[y,1] + do[y,2] <= 1;


maximize TotalProfit:
    sum {y in YEARS, p in PROJECTS: p != 4} do[y,p] * profit[p];
solve;

printf {y in YEARS, p in PROJECTS: do[y,p] == 1} "Year: %s, Project: %s\n", y, p;
printf "Total Profit: %f\n", TotalProfit;

end;
