#![allow(dead_code)]
use crate::libjpp;
use std::{fmt::Display, ops};

#[derive(Debug, Clone)]
pub struct Ring {
    value: u64,
    n: u64,
}

impl Ring {
    fn assert(n: u64) {
        assert!(n > 0, "self.n must be greater than 0");
    }

    pub fn new(value: u64, n : u64) -> Ring {
        let _ = Self::assert(n);
        Ring { value: value % n, n: n }
    }
}

impl Into<u64> for Ring {
    fn into(self) -> u64 {
        self.value
    }
}

impl Display for Ring {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        write!(f, "R<{}>({})", self.n, self.value)
    }
}

// +
impl ops::Add for Ring {
    type Output = Ring;

    fn add(self, o: Ring) -> Ring {
        Ring {
            value: (self.value + o.value) % self.n, n: self.n
        }
    }
}

// -
impl ops::Sub for Ring {
    type Output = Ring;

    fn sub(self, o: Ring) -> Ring {
        if self.value >= o.value {
            return Ring {
                value: (self.value - o.value) % self.n, n: self.n
            };
        } else {
            return Ring {
                value: (self.value + self.n - o.value) % self.n, n: self.n
            };
        }
    }
}

// *
impl ops::Mul for Ring {
    type Output = Ring;

    fn mul(self, o: Ring) -> Ring {
        Ring {
            value: (self.value * o.value) % self.n, n: self.n
        }
    }
}

// /
impl ops::Div for Ring {
    type Output = Ring;

    fn div(self, o: Ring) -> Ring {
        let res = libjpp::diophantine(o.value, self.n, 1);
        if res.err {
            return Ring { value: 0, n: self.n};
        }
        let inv = res.x % self.n;
        return Ring {
            value: (self.value * inv) % self.n, n: self.n
        };
    }
}

// ^
impl ops::BitXor<u64> for Ring {
    type Output = Ring;

    fn bitxor(self, mut exp: u64) -> Ring {
        let mut res = Ring::new(1,self.n);
        let mut base = self.value % self.n;

        while exp > 0 {
            if exp & 1 == 1 {
                res.value = (res.value * base) % self.n;
            }
            base = (base * base) % self.n;
            exp >>= 1;
        }

        res
    }
}

// ==, !=
impl PartialEq for Ring {
    fn eq(&self, o: &Ring) -> bool {
        self.value == o.value
    }
}

// >=, <=, >, <
impl PartialOrd for Ring {
    fn partial_cmp(&self, o: &Ring) -> Option<std::cmp::Ordering> {
        self.value.partial_cmp(&o.value)
    }
}

// +=
impl ops::AddAssign for Ring {
    fn add_assign(&mut self, o: Ring) {
        self.value = (self.value + o.value) % self.n;
    }
}

// -=
impl ops::SubAssign for Ring {
    fn sub_assign(&mut self, o: Ring) {
        if self.value >= o.value {
            self.value = (self.value - o.value) % self.n;
        } else {
            self.value = (self.value + self.n - o.value) % self.n;
        }
    }
}

// *=
impl ops::MulAssign for Ring {
    fn mul_assign(&mut self, o: Ring) {
        self.value = (self.value * o.value) % self.n;
    }
}

// /=
impl ops::DivAssign for Ring {
    fn div_assign(&mut self, o: Ring) {
        let res = libjpp::diophantine(o.value, self.n, 1);
        if res.err {
            self.value = 0;
            return;
        }
        let inv = res.x % self.n;
        self.value = (self.value * inv) % self.n;
    }
}
