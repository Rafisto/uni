#![allow(dead_code)]
use crate::{ring::Ring, dh::DHSetup};
use rand::{RngExt};

pub struct User<'a> {
    setup: &'a DHSetup,
    secret: u64,
    shared_key: Option<Ring>,
}

impl<'a> User<'a> {
    pub fn new(setup: &'a DHSetup, n: u64) -> Self {
        let mut rng = rand::rng();
        let secret = rng.random_range(2..n);
        
        Self {
            setup,
            secret,
            shared_key: None,
        }
    }

    pub fn get_public_key(&self) -> Ring {
        self.setup.power(self.setup.get_generator(), self.secret)
    }

    pub fn set_key(&mut self, a: Ring) {
        self.shared_key = Some(self.setup.power(a, self.secret));
    }

    pub fn encrypt(&self, m: Ring) -> Ring {
        // Use expect() to handle the "key not set" error
        let key = self.shared_key.as_ref().expect("Key not set");
        m * key.clone()
    }

    pub fn decrypt(&self, c: Ring) -> Ring {
        let key = self.shared_key.as_ref().expect("Key not set");
        c / key.clone()
    }
}