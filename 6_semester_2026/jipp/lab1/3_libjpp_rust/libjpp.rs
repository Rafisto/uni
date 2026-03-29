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
        (x,y) = (y, x % y);
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
pub extern "C" fn diophantine(m: u64, n: u64, z: u64) -> DiophantineResult {
    if m == 0 && n == 0 {
        return DiophantineResult { x: 0, y: 0, err: z != 0 };
    }

    if n == 0 {
        if z % m != 0 {
            return DiophantineResult { x: 0, y: 0, err: true };
        }
        return DiophantineResult { x: z / m, y: 0, err: false };
    }

    if m == 0 {
        return DiophantineResult { x: 0, y: 0, err: true };
    }
    
    if gcd(m, n) != z {
        return DiophantineResult { x: 0, y: 0, err: true };
    }

    let mut a: u64 = m;
    let mut b: u64 = n;
    let mut x: u64 = 1;
    let mut y: u64 = 0;
    let mut r: u64 = n;
    let mut s: u64 = m - 1;
    let (mut rr, mut ss, mut rem, mut quot, mut tmp);

    while b > 0 {
        rem = a % b;
        quot = a / b;
        a = b;
        b = rem;
        rr = r;
        tmp = quot * r;
        if x < tmp {
            r = n * quot;
        } 
        else {
            r = 0;
        }

        r = r + x;
        r = r - tmp;
        ss = s;
        tmp = quot * s;
        if y < tmp {
            s = m * quot;
        } else {
            s = 0;
        }
        s = s + y;
        x = rr;
        y = ss;
        s = s - tmp;
    }

    return DiophantineResult { x: x, y: y, err: false };
}
