mod dh;
mod libjpp;
mod ring;
mod user;

#[cfg(test)]
mod tests {
    use crate::{dh::DHSetup, ring::Ring, user::User};

    #[test]
    fn test_dh() {
        let n = 1234567891;
        let setup = DHSetup::new(n);

        let mut alice = User::new(&setup, n);
        let mut bob = User::new(&setup, n);

        let pub_alice = alice.get_public_key();
        let pub_bob = bob.get_public_key();

        alice.set_key(pub_bob);
        bob.set_key(pub_alice);

        let message = Ring::new(12345, n);
        let encrypted = alice.encrypt(message.clone());
        let decrypted = bob.decrypt(encrypted);

        assert_eq!(message, decrypted);

        let message2 = Ring::new(54321, n);
        let encrypted2 = alice.encrypt(message2.clone());
        let decrypted2 = bob.decrypt(encrypted2);

        assert_eq!(message2, decrypted2);
    }
}
