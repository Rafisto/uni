#![allow(dead_code)]
use crate::libjpp;
use std::{fmt::Display, ops};

#[derive(Debug, Clone)]
pub struct Ring<const N: u64> {
    value: u64,
}

impl<const N: u64> Ring<N> {
    const ASSERT: () = {
        assert!(N > 0, "N must be greater than 0");
    };

    pub fn new(value: u64) -> Ring<N> {
        let _ = Self::ASSERT;
        Ring { value: value % N }
    }
}

impl<const N: u64> Into<u64> for Ring<N> {
    fn into(self) -> u64 {
        self.value
    }
}

impl<const N: u64> Display for Ring<N> {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        write!(f, "R<{}>({})", N, self.value)
    }
}

// +
impl<const N: u64> ops::Add for Ring<N> {
    type Output = Ring<N>;

    fn add(self, o: Ring<N>) -> Ring<N> {
        Ring {
            value: (self.value + o.value) % N,
        }
    }
}

// -
impl<const N: u64> ops::Sub for Ring<N> {
    type Output = Ring<N>;

    fn sub(self, o: Ring<N>) -> Ring<N> {
        if self.value >= o.value {
            return Ring {
                value: (self.value - o.value) % N,
            };
        } else {
            return Ring {
                value: (self.value + N - o.value) % N,
            };
        }
    }
}

// *
impl<const N: u64> ops::Mul for Ring<N> {
    type Output = Ring<N>;

    fn mul(self, o: Ring<N>) -> Ring<N> {
        Ring {
            value: (self.value * o.value) % N,
        }
    }
}

// /
impl<const N: u64> ops::Div for Ring<N> {
    type Output = Ring<N>;

    fn div(self, o: Ring<N>) -> Ring<N> {
        let res = libjpp::diophantine(o.value, N, 1);
        if res.err {
            return Ring { value: 0 };
        }
        let inv = res.x % N;
        return self * Ring { value: inv };
    }
}

// ==, !=
impl<const N: u64> PartialEq for Ring<N> {
    fn eq(&self, o: &Ring<N>) -> bool {
        self.value == o.value
    }
}

// >=, <=, >, <
impl<const N: u64> PartialOrd for Ring<N> {
    fn partial_cmp(&self, o: &Ring<N>) -> Option<std::cmp::Ordering> {
        self.value.partial_cmp(&o.value)
    }
}

// +=
impl<const N: u64> ops::AddAssign for Ring<N> {
    fn add_assign(&mut self, o: Ring<N>) {
        self.value = (self.value + o.value) % N;
    }
}

// -=
impl<const N: u64> ops::SubAssign for Ring<N> {
    fn sub_assign(&mut self, o: Ring<N>) {
        if self.value >= o.value {
            self.value = (self.value - o.value) % N;
        } else {
            self.value = (self.value + N - o.value) % N;
        }
    }
}

// *=
impl<const N: u64> ops::MulAssign for Ring<N> {
    fn mul_assign(&mut self, o: Ring<N>) {
        self.value = (self.value * o.value) % N;
    }
}

// /=
impl<const N: u64> ops::DivAssign for Ring<N> {
    fn div_assign(&mut self, o: Ring<N>) {
        let res = libjpp::diophantine(o.value, N, 1);
        if res.err {
            self.value = 0;
            return;
        }
        let inv = res.x % N;
        self.value = (self.value * inv) % N;
    }
}
