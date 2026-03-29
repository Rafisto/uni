#[repr(C)]
pub struct DiophantineResult {
    pub x: u64,
    pub y: u64,
    pub err: bool,
}

extern "C" {
    fn gcd(x: u64, y: u64) -> u64;
    fn first_prime_div(n: u64) -> u64;
    fn phi(n: u64) -> u64;
    fn diophantine(m: u64, n: u64, z: u64) -> DiophantineResult;
}

fn main() {
    unsafe {
        test_gcd();
        test_first_prime_div();
        test_phi();
        test_diophantine();
    }
}

unsafe fn test_gcd() {
    assert_eq!(gcd(0, 0), 0);
    assert_eq!(gcd(48, 18), 6);
    assert_eq!(gcd(101, 103), 1);
    assert_eq!(gcd(0, 5), 5);
    assert_eq!(gcd(5, 0), 5);

    let max_val = u64::MAX;
    assert_eq!(gcd(max_val, max_val), max_val);
    assert_eq!(gcd(max_val, 1), 1);

    assert_eq!(gcd(7540113804746346429, 4660046610375530309), 1);
    println!("test_gcd pass");
}

unsafe fn test_first_prime_div() {
    assert_eq!(first_prime_div(0), 0);
    assert_eq!(first_prime_div(31), 31);
    assert_eq!(first_prime_div(29), 29);
    assert_eq!(first_prime_div(4), 2);
    assert_eq!(first_prime_div(104729), 104729);
    assert_eq!(first_prime_div(121), 11);
    assert_eq!(first_prime_div(961), 31);
    println!("test_first_prime_div pass");
}

unsafe fn test_phi() {
    assert_eq!(phi(0), 0);
    assert_eq!(phi(1), 1);
    assert_eq!(phi(2), 1);
    assert_eq!(phi(3), 2);
    assert_eq!(phi(9), 6);
    assert_eq!(phi(10), 4);
    assert_eq!(phi(100), 40);
    assert_eq!(phi(1000), 400);

    assert_eq!(phi(37) * phi(39), phi(37 * 39));
    assert_eq!(phi(101) * phi(103), 100 * 102);
    println!("test_phi pass");
}

unsafe fn test_diophantine() {
    // 15x - 10y = 5
    let res = diophantine(15, 10, 5);
    assert!(!res.err);
    assert_eq!(15 * res.x - 10 * res.y, 5);

    // 29x - 10y = gcd(29, 10)
    let g = gcd(29, 10);
    let res = diophantine(29, 10, g);
    assert!(!res.err);
    assert_eq!(29 * res.x - 10 * res.y, g);

    // error case
    let res = diophantine(29, 10, g + 1);
    assert!(res.err);

    // a is zero
    let res = diophantine(0, 10, 10);
    assert!(res.err);

    // b is zero
    let res = diophantine(10, 0, 10);
    assert!(!res.err);
    assert_eq!(res.x, 1);

    // c is zero
    let res = diophantine(10, 10, 0);
    assert!(res.err);
    
    println!("test_diophantine pass");
}