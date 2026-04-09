mod ring;
mod libjpp;

#[cfg(test)]
mod tests {
    use crate::ring::Ring;

    #[test]
    fn test_op_add() {
        let op1 = Ring::<17>::new(8);
        let op2 = Ring::<17>::new(10);
        assert_eq!(op1 + op2, Ring::new(1));

        let oq1 = Ring::<15>::new(4);
        let oq2 = Ring::<15>::new(9);

        // 4 + 9 = 13 (mod 15)
        assert_eq!(oq1.clone() + oq2.clone(), Ring::new(13));

        // 4 + 4 + 9 = 17 = 2 (mod 15)
        assert_eq!(oq1.clone() + oq1 + oq2, Ring::new(2));
    }

    #[test]
    fn test_op_sub() {
        let op1 = Ring::<17>::new(9);
        let op2 = Ring::<17>::new(13);

        // 13 - 9 = 4 (mod 17)
        assert_eq!(op2.clone() - op1.clone(), Ring::new(4));

        // 9 - 13 = -4 -> 17 - 4 = 13 (mod 17)
        assert_eq!(op1 - op2, Ring::new(13));

        let oq1 = Ring::<15>::new(9);
        let oq2 = Ring::<15>::new(13);

        // 13 - 9 = 4 (mod 15)
        assert_eq!(oq2.clone() - oq1.clone(), Ring::new(4));

        // 9 - 13 = -4 -> 15-4 = 11 (mod 15)
        assert_eq!(oq1 - oq2, Ring::new(11));
    }

    #[test]
    fn test_op_mul() {
        let op1 = Ring::<17>::new(9);
        let op2 = Ring::<17>::new(13);

        // 9 * 13 = 117 = 15 (mod 17)
        assert_eq!(op1 * op2, Ring::new(15));

        let oq1 = Ring::<15>::new(9);
        let oq2 = Ring::<15>::new(13);

        assert_eq!(oq1 * oq2, Ring::new(12));
    }

    #[test]
    fn test_op_div_prime() {
        let op1 = Ring::<17>::new(9);
        let op2 = Ring::<17>::new(13);

        // op1 / op2 = op1 * inv(op2) = 9 * 4 = 36 mod 17 = 2
        assert_eq!(op1 / op2, Ring::new(2));
    }

    #[test]
    fn test_op_div_composite() {
        let oq1 = Ring::<15>::new(9);
        let oq2 = Ring::<15>::new(13);

        // oq1 / oq2 = oq1 * inv(oq2) = 9 * 7 = 63 mod 15 = 3
        assert_eq!(oq1.clone() / oq2, Ring::new(3));

        let thr = Ring::<15>::new(12);
        // Based on your impl: if diophantine fails, it returns value 0
        let res = oq1 / thr;
        assert_eq!(res, Ring::new(0)); 
    }

    #[test]
    fn test_comparisons() {
        let a = Ring::<15>::new(9);
        let b = Ring::<15>::new(13);
        let c = Ring::<15>::new(14);
        let d = Ring::<15>::new(9);

        assert!(a != b);
        assert!(a != c);
        assert!(a == d);

        assert!(a <= b);
        assert!(a <= c);
        assert!(a <= d);

        assert!(!(a >= b));
        assert!(!(a >= c));
        assert!(a >= d);

        assert!(a < b);
        assert!(a < c);
        assert!(!(a < d));
    }

    #[test]
    fn test_subst_eq() {
        let a = Ring::<15>::new(5);
        let b = a.clone();

        assert_eq!(b, Ring::new(5));
    }

    #[test]
    fn test_subst_add() {
        let mut a = Ring::<15>::new(5);
        let b = Ring::<15>::new(10);

        a += b;
        assert_eq!(a, Ring::new(0));
    }

    #[test]
    fn test_subst_sub() {
        let mut a = Ring::<15>::new(6);
        let b = Ring::<15>::new(8);

        a -= b;
        assert_eq!(a, Ring::new(13));
    }

    #[test]
    fn test_subst_mul() {
        let mut a = Ring::<15>::new(6);
        let b = Ring::<15>::new(8);

        a *= b;
        assert_eq!(a, Ring::new(3));
    }

    #[test]
    fn test_subst_div() {
        let mut a = Ring::<17>::new(9);
        let b = Ring::<17>::new(13);

        a /= b;
        // op1 / op2 = op1 * inv(op2) = 9 * 4 = 36 mod 17 = 2
        assert_eq!(a, Ring::new(2));
    }

    #[test]
    fn test_streams() {
        let a = Ring::<17>::new(10);
        let output = format!("{}", a);
        assert_eq!(output, "R<17>(10)");
        println!("{}", a);
    }
}
