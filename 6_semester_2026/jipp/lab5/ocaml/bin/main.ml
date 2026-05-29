(* binomial *)

let rec binomial (n : int) (k : int) =
  match (n, k) with
  | n, 0 -> 1
  | n, k when k > n -> 0
  | n, k when k = n -> 1
  | n, k -> binomial (n - 1) k + binomial (n - 1) (k - 1)

(* binomial2 *)

let rec ptr (x : int) = 
  match x with
  | 0 -> [1]
  | 1 -> [1; 1]
  | x -> let prev = ptr (x - 1) in 
  (* Haskell Equivalent *)
  (* zip === List.combine *)
  (* zipWith === List.map2 *)
        List.map2 (fun a b -> a + b) (prev @ [0]) ([0] @ prev)

let rec binomial2 (n : int) (k : int) =
  match (n, k) with
  | n, 0 -> 1
  | n, k when k > n -> 0
  | n, k when k = n -> 1
  | n, k -> List.nth (ptr n) k

(* mergesort *)

let rec merge l a b = 
  match (a,b) with
  | ([],_) -> b
  | (_,[]) -> a
  | (x::xs, y::ys) ->
    if l x y 
      then x::(merge l xs (y::ys))
      else y::(merge l (x::xs) ys)

let rec take n lst =
  match (n, lst) with
  | (0, _) -> []
  | (_, []) -> []
  | (n, x::xs) -> x :: take (n-1) xs

let rec drop n lst =
  match (n, lst) with
  | (0, _) -> lst
  | (_, []) -> []
  | (n, _::xs) -> drop (n-1) xs

let rec mergesort xs =
  match xs with
  | [] -> []
  | [_] -> xs
  | _ ->
    let l = (List.length xs) / 2 in
    merge (fun a b -> compare a b <= 0) (take l xs) (drop l xs)

(* de *)

let rec gcd (x : int) (y : int) =
  match (x, y) with
  | 0, y -> y
  | x, 0 -> x
  | x, y when x > y -> gcd y (x mod y)
  | x, y when x < y -> gcd x (y mod x)
  | x, _ -> x

let rec de (a : int) (b : int) =
  match (a, b) with
  | (a, 0) -> (1, 0, a)
  | (0, b) -> (0, 1, b)
  | _ ->
    let (x, y, g) = de b (a mod b) in
    (y, x - (a / b) * y, g)

(* prime_factors *)

let prime_factors n =
  let rec dv acc c n =
    if n = 1 then List.rev acc
    else if n mod c = 0 then dv (c::acc) 2 (n / c)
    else dv acc (c + 1) n
  in
  if n <= 1 then [] else dv [] 2 n

(* totient *)

let totient n =
  if n <= 1 then n
  else
    let rec aux k acc =
      if k > n then acc
      else if gcd k n = 1 then aux (k+1) (acc+1)
      else aux (k+1) acc
    in aux 1 0

(* totient2 *)

let totient2 n =
  if n <= 1 then 1
  else
    let pf = prime_factors n in
    let so = List.sort_uniq compare pf in
    let s1 = List.map (fun x -> x - 1) so in
    let rec remove_once lst x =
      match lst with
      | [] -> []
      | y::ys -> if y = x then ys else y :: remove_once ys x
    in
    let rec diff a b =
      match b with
      | [] -> a
      | x::xs -> diff (remove_once a x) xs
    in
    let s2 = diff pf so in
    List.fold_left ( * ) 1 (s1 @ s2)

(* primes *)

let range a b =
  let rec aux i acc = if i < a then acc else aux (i-1) (i::acc) in
  if b < a then [] else aux b []

let primes n =
  if n <= 1 then []
  else
    let rec eval lst =
      match lst with
      | [] -> []
      | x::xs -> x :: eval (List.filter (fun i -> i mod x <> 0) xs)
    in
    eval (range 2 n)

let () = print_int (binomial 4 2); print_newline ();
         print_int (binomial2 4 2); print_newline ();
         print_int (gcd 24 18); print_newline ();
         mergesort [0;2;4;6;8;1;3;5;7;9] |> List.iter (fun x -> print_int x; print_string " "); print_newline ();
         de 7 3 |> (fun (x, y, g) -> print_string "x: "; print_int x; print_string " y: "; print_int y; print_string " mod: "; print_int g; print_newline ());
         prime_factors 60 |> List.iter (fun x -> print_int x; print_string " "); print_newline ();
         totient 1000 |> print_int; print_newline ();
         totient2 1000 |> print_int; print_newline ();
         primes 30 |> List.iter (fun x -> print_int x; print_string " "); print_newline ()
