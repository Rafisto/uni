parameters

projects=['A','B','C']
year=[1,2,3]
cost[year][project]
profit[project]
budget[year]

decision variables

do[year][project]

subject to

do[year] <= budget[year] for year in years
do[year][A] + do[year][B] <= 1 for year in years
budget[year=3] = budget[3] + do[year][D] * profit[D] 

objective function

sum over year and project without D of do[year][project] * (profit[project]-cost[project]) - sum over year of do[year[D]] cost[year[D]][D]