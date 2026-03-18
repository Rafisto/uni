#[repr(C)]
pub struct DiophantineResult {
    pub x: u64,
    pub y: u64,
    pub err: bool,
}

#[unsafe(no_mangle)]
pub extern "C" fn gcd(mut x: u64, mut y: u64) -> u64 {
    if y == 0 { return x; }
    if x == 0 { return y; }
    if x == y { return x; }
    if x < y { return gcd(y, x); }

    while y != 0 {
        let t = y;
        y = x % y;
        x = t;
    }

    x
}

#[unsafe(no_mangle)]
pub extern "C" fn first_prime_div(n: u64) -> u64 {
    if n <= 1 { return 0; }

    let mut i = 2;
    while i * i <= n {
        if n % i == 0 {
            return i;
        }
        i += 1;
    }
    n
}

#[unsafe(no_mangle)]
pub extern "C" fn phi(n: u64) -> u64 {
    let mut res = 0;
    for i in 1..=n {
        if gcd(i, n) == 1 {
            res += 1;
        }
    }
    res
}

#[unsafe(no_mangle)]
pub extern "C" fn diophantine(mut a: u64, mut b: u64, c: u64) -> DiophantineResult {
    if c % gcd(a, b) != 0 {
        return DiophantineResult { x: 0, y: 0, err: true };
    }

    let mut x = 1;
    let mut y = 0;
    let mut r = b;
    let mut s = a - 1;

    while b > 0 {
        let quotient = a / b;
        let remainder = a % b;
        a = b;
        b = remainder;

        let rr = r;
        let tmp_r = quotient.wrapping_mul(r);
        r = if x < tmp_r { 0 } else { x }.wrapping_add(r.wrapping_mul(b)).wrapping_sub(tmp_r);

        let ss = s;
        let tmp_s = quotient.wrapping_mul(s);
        s = if y < tmp_s { 0 } else { y }.wrapping_add(s.wrapping_mul(a)).wrapping_sub(tmp_s);

        x = rr;
        y = ss;
    }

    DiophantineResult {
        x: x.wrapping_mul(c),
        y: y.wrapping_mul(c),
        err: false,
    }
}
