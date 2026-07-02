#![allow(dead_code)]
use crate::{ring::Ring};

pub struct DHSetup {
    g: Ring,
}

impl DHSetup {
    pub fn new(n: u64) -> Self {
        Self {
            g: Ring::g(n),
        }
    }

    pub fn get_generator(&self) -> Ring {
        self.g.clone()
    }

    pub fn power(&self, a: Ring, b: u64) -> Ring {
        a ^ b
    }
}