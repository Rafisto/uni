let rec gcd = function
  | x,y when x == 0 -> y
  | x,y when y == 0 -> x
  | x,y when x > y -> gcd (y, x mod y)
  | x,y when x < y -> gcd (x, y mod x)
  | x,_ -> x

let () = print_int (gcd (121, 44))
