#![allow(dead_code)]
use crate::{libjpp::diophantine, ring::Ring};
use rand::{RngExt};

pub struct RSA {
    e: u64,
    d: u64,
    n: u64,
}

impl RSA {
    pub fn new(p: u64, q: u64) -> Self {
        let n = p * q;
        let phi = (p - 1) * (q - 1);
        let mut rng = rand::rng();
        
        let e = loop {
            let temp_e = rng.random_range(2..phi);
            if crate::libjpp::gcd(temp_e, phi) == 1 {
                break temp_e;
            }
        };

        let res = diophantine(e, phi, 1);
        
        RSA { e, d: res.x, n }
    }

    pub fn encrypt(&self, m: u64) -> Ring {
        let r = Ring::new(m, self.n);
        r ^ self.e
    }

    pub fn decrypt(&self, s: Ring) -> Ring {
        s ^ self.d
    }

    pub fn get_modulo(&self) -> u64 { self.n }
    pub fn get_public_key(&self) -> u64 { self.e }
}