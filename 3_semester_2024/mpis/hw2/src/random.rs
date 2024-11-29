use rand::{Rng, SeedableRng};
use rand_mt::Mt19937GenRand64;

/// Generate a random integer between s and e
/// Uses Mersenne Twister (MT19937) to generate the random number
///
/// Arguments
/// - s: u32 - start of the range
/// - e: u32 - end of the range
pub fn generate_random_unsigned_integer(s: u32, e: u32) -> usize {
    let mut rng = Mt19937GenRand64::from_entropy();
    return rng.gen_range(s..=e) as usize;
}
