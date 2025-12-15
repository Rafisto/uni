# Rafal Wlodarczyk 279762
# Exercise 3 - Model

# --- Parameters Declaration ---

# time ranges when the production happens
set Times;

# - standard singular production cost
# - standard production cap 
# - additional singular production cost
# - additional production cap
# - demand

param cost{Times} >= 0;
param production_cap >= 0;
param additional_cost{Times} >= 0;
param additional_production_cap{Times} >= 0;
param demand{Times} >= 0;

# - max storage capacity (we can offload products when demand is less than production)
# - singular item storage cost per time range
# - initial storage (inventory) product count

param storage_capacity >= 0;
param additional_storage_cost >= 0;
param initial_inventory >= 0;

# --- Decision Variables ---

# - inventory, to track previous operations
# - production in each time range
# - additional production in each time range

var inventory{Times} >= 0;
var production{Times} >= 0;
var additional_production{Times} >= 0;

# --- Constraints ---

# ensure first time range inventory is modified by initial inventory 
s.t. inventory_balance_first:
    inventory[1] = initial_inventory + production[1] + additional_production[1] - demand[1];

# ensure every other inventory is set to 
s.t. inventory_balance_next {k in Times: k > 1}:
    inventory[k] = inventory[k-1] + production[k] + additional_production[k] - demand[k];

# standard production cannot exceed standard production cap 
s.t. production_capacity {k in Times}:
    production[k] <= production_cap;

# excess production cannot exceed excess production cap
s.t. additional_production_capacity {k in Times}:
    additional_production[k] <= additional_production_cap[k];

# inventory cannot be larger than storage capacity
s.t. inventory_cap {k in Times}:
    inventory[k] <= storage_capacity;

# --- Objective Function ---

minimize total_cost:
    sum {k in Times} (
        cost[k] * production[k]
      + additional_cost[k] * additional_production[k]
      + additional_storage_cost * inventory[k]
    );

# --- Results ---

solve;
display production, additional_production, inventory, total_cost;

end;
