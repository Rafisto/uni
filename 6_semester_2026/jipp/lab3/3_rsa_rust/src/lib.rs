mod ring;
mod libjpp;
mod rsa;

#[cfg(test)]
mod tests {
    use crate::{ring::Ring, rsa::RSA};

    #[test]
    fn test_rsa() {
        let p : u64 = 10007;
        let q : u64 = 10009;
        let n : u64 = p * q;
        
        let r = RSA::new(p,q);

        let message : u64 = 12345;
        let encrypted = r.encrypt(message.clone());
        let decrypted = r.decrypt(encrypted);
        assert_eq!(Ring::new(message,n), decrypted);
    }
}
