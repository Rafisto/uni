pub fn gcd(mut x: u64, mut y: u64) -> u64 {
    if y == 0 {
        return x;
    }
    if x == 0 {
        return y;
    }
    if x == y {
        return x;
    }
    if x < y {
        return gcd(y, x);
    }

    while y != 0 {
        let t: u64 = y;
        y = x % y;
        x = t;
    }

    x
}

pub fn first_prime_div(n: u64) -> u64 {
    if n <= 1 {
        return 0;
    }

    for i in 2..=((n as f64).sqrt() as u64) {
        if n % i == 0 {
            return i;
        }
    }

    n
}

pub fn phi(n: u64) -> u64 {
    let mut res = 0;
    for i in 1..=n {
        if gcd(i, n) == 1 {
            res += 1;
        }
    }

    res
}

struct pair64 {
    x: i64,
    y: i64,
}

pub fn diophantine(a: i64, b: i64, c: i64) -> pair64 {
    let mut x: i64 = 1;
    let mut y: i64 = 0;
    let mut r: i64 = b;
    let mut s: i64 = a - 1;
    let mut a = a;
    let mut b = b;

    while b > 0 {
        let remainder = a % b;
        let quotient = a / b;
        a = b;
        b = remainder;

        let rr = r;
        let tmp = quotient * r;
        if x < tmp {
            r = b * quotient;
        } else {
            r = 0;
        }
        r = r + x;
        r = r - tmp;

        let ss = s;
        let tmp = quotient * s;
        if y < tmp {
            s = a * quotient;
        } else {
            s = 0;
        }
        s = s + y;
        s = s - tmp;

        x = rr;
        y = ss;
    }

    pair64 { x: x * c, y: y * c }
}
