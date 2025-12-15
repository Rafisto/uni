# Rafal Wlodarczyk 279762
# Exercise 1

# This language is called AMPL - A Mathematical Programming Language
# See: https://en.wikipedia.org/wiki/AMPL, feels like a c/bash mashup.

# Intial specific-case solution, a sanity check

# --- Decision Variables --- 

var x11, >= 0;
var x12, >= 0;
var x13, >= 0;
var x14, >= 0;

var x21, >= 0;
var x22, >= 0;
var x23, >= 0;
var x24, >= 0;

var x31, >= 0;
var x32, >= 0;
var x33, >= 0;
var x34, >= 0;

# --- Constraints ---

s.t. supply1: x11 + x12 + x13 + x14 <= 275000;
s.t. supply2: x21 + x22 + x23 + x24 <= 550000;
s.t. supply3: x31 + x32 + x33 + x34 <= 660000;

s.t. demand1: x11 + x21 + x31 >= 110000;
s.t. demand2: x12 + x22 + x32 >= 220000;
s.t. demand3: x13 + x23 + x33 >= 330000;
s.t. demand4: x14 + x24 + x34 >= 440000;

# --- Objective Function ---

minimize cost:
    10*x11 + 10*x12 + 9*x13 + 11*x14
  + 7*x21 + 11*x22 + 12*x23 + 13*x24
  + 8*x31 + 14*x32 + 4*x33 + 9*x34;

# --- Solution ---

solve;

# --- Print Solution ---

display x11,x12,x13,x14,
        x21,x22,x23,x24,
        x31,x32,x33,x34;

display x11+x12+x13+x14,
        x21+x22+x23+x24,
        x31+x32+x33+x34;

display cost;

end;
