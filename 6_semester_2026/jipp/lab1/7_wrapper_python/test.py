import libjpp

def test_gcd(lib: libjpp.LibJPP):
    # zero case
    assert lib.gcd(0, 0) == 0

    # base
    assert lib.gcd(48, 18) == 6
    assert lib.gcd(101, 103) == 1

    # one is a zero
    assert lib.gcd(0, 5) == 5
    assert lib.gcd(5, 0) == 5

    # max value (Equivalent to 0xFFFFFFFFFFFFFFFFULL)
    max_val = (1 << 64) - 1
    assert lib.gcd(max_val, max_val) == max_val
    assert lib.gcd(max_val, 1) == 1

    # large co-prime numbers
    assert lib.gcd(7540113804746346429, 4660046610375530309) == 1

    print("test_gcd pass")

def test_first_prime_div(lib: libjpp.LibJPP):
    # zero case
    assert lib.first_prime_div(0) == 0

    # base case
    assert lib.first_prime_div(31) == 31
    assert lib.first_prime_div(29) == 29
    assert lib.first_prime_div(4) == 2

    # large primes
    assert lib.first_prime_div(104729) == 104729

    # square factors
    assert lib.first_prime_div(121) == 11
    assert lib.first_prime_div(961) == 31

    print("test_first_prime_div pass")

def test_phi(lib: libjpp.LibJPP):
    # zero case
    assert lib.phi(0) == 0

    # base case
    assert lib.phi(1) == 1
    assert lib.phi(2) == 1
    assert lib.phi(3) == 2
    assert lib.phi(9) == 6
    assert lib.phi(10) == 4

    # larger composites
    assert lib.phi(100) == 40
    assert lib.phi(1000) == 400

    # co-prime phi(pq) = phi(p) * phi(q)
    assert lib.phi(37) * lib.phi(39) == lib.phi(37 * 39)
    assert lib.phi(101) * lib.phi(103) == 100 * 102

    print("test_phi pass")

def test_diophantine(lib: libjpp.LibJPP):
    # ax - by = c
    
    # 15x - 10y = 5
    res = lib.diophantine(15, 10, 5)
    assert not res.err
    assert 15 * res.x - 10 * res.y == 5

    # 29x - 10y = gcd(29,10)
    g = lib.gcd(29, 10)
    res = lib.diophantine(29, 10, g)
    assert not res.err
    assert 29 * res.x - 10 * res.y == g

    # error case
    res = lib.diophantine(29, 10, lib.gcd(29, 10) + 1)
    assert res.err

    # a is zero
    res = lib.diophantine(0, 10, 10)
    assert res.err

    # b is zero
    res = lib.diophantine(10, 0, 10)
    assert not res.err
    assert res.x == 1

    # c is zero
    res = lib.diophantine(10, 10, 0)
    assert res.err
    assert 10 * res.x - 10 * res.y == 0

    print("test_diophantine pass")
