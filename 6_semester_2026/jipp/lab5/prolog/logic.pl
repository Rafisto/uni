% mergesort(+List, -Sorted)
mergesort([], []).
mergesort([X], [X]).
mergesort(List, Sorted) :-
    length(List, N),
    Mid is N // 2,
    split(List, Mid, Left, Right),
    mergesort(Left, LeftSorted),
    mergesort(Right, RightSorted),
    merge_lists(LeftSorted, RightSorted, Sorted).

% split(+List, +N, -Left, -Right)
split(L, 0, [], L).
split([X|XS], N, [X|Left], Right) :-
    N > 0,
    N1 is N - 1,
    split(XS, N1, Left, Right).

% merge_lists(+ListX, +ListY, -Merged)
merge_lists([], L, L).
merge_lists(L, [], L).
merge_lists([X|XS], [Y|YS], [X|Result]) :-
    X =< Y,
    merge_lists(XS, [Y|YS], Result).
merge_lists([X|XS], [Y|YS], [Y|Result]) :-
    X > Y,
    merge_lists([X|XS], YS, Result).


% de(+A, +B, -X, -Y, -Z) -> AX + BY = gcd(A, B)
de(A, 0, 1, 0, A) :- A > 0.
de(0, B, 0, 1, B) :- B > 0.
de(A, B, X, Y, Z) :-
    A > 0, B > 0,
    Rest is A mod B,
    Div is A // B,
    de(B, Rest, X1, Y1, Z),
    X is Y1,
    Y is X1 - Div * Y1.

% prime_factors(+N, -Factors)
prime_factors(N, Factors) :-
    N > 1,
    prime_factors_helper(N, 2, Factors).

prime_factors_helper(1, _, []).
prime_factors_helper(N, C, [C|Tail]) :-
    N mod C =:= 0,
    N1 is N // C,
    prime_factors_helper(N1, C, Tail).
prime_factors_helper(N, C, Tail) :-
    N mod C =\= 0,
    C1 is C + 1,
    prime_factors_helper(N, C1, Tail).


% totient(+N,-T)
totient(1, 1) :- !.
totient(N, T) :-
    N > 1,
    count_coprime(N, 1, 0, T).

count_coprime(N, N, Acc, Acc) :- !.
count_coprime(N, K, Acc, T) :-
    K < N,
    gcd(N, K, G),
    (G =:= 1 -> Acc1 is Acc + 1 ; Acc1 is Acc),
    K1 is K + 1,
    count_coprime(N, K1, Acc1, T).

gcd(A, 0, A) :- !.
gcd(A, B, G) :-
    B > 0,
    R is A mod B,
    gcd(B, R, G).

% primes(+N, -PrimeList)
primes(N, PrimeList) :-
    N >= 2,
    numlist(2, N, L),
    sieve(L, PrimeList).

sieve([], []).
sieve([X|XS], [X|Result]) :-
    exclude_multiples(X, XS, Filtered),
    sieve(Filtered, Result).

exclude_multiples(_, [], []).
exclude_multiples(P, [X|XS], Result) :-
    X mod P =:= 0, !,
    exclude_multiples(P, XS, Result).
exclude_multiples(P, [X|XS], [X|Result]) :-
    exclude_multiples(P, XS, Result).

main :-
    mergesort([0, 2, 4, 6, 8, 1, 3, 5, 7, 9], Sorted),
    format('Mergesort: ~w~n', [Sorted]),
    
    de(7, 3, X, Y, G),
    format('Extended Euclidean (7, 3): x=~w, y=~w, gcd=~w~n', [X, Y, G]),
    
    prime_factors(60, Factors),
    format('Prime Factors of 60: ~w~n', [Factors]),
    
    totient(1000, T),
    format('Totient of 1000: ~w~n', [T]),
    
    primes(30, P),
    format('Primes up to 30: ~w~n', [P]).
