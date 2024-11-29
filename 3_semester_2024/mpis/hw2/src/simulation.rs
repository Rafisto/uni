use super::random;

/// Create bins for the balls to be placed in
///
/// Arguments
/// - n: u32 - number of bins to create
pub fn create_bins(n: u32) -> Box<[u32]> {
    // Create a heap-allocated array of size n
    vec![0; n as usize].into_boxed_slice()
}

/// Place a ball in one of the bins, randomly
///
/// Arguments
/// - bins: &mut Box<[u32]> - pointer to the bins to place the ball in
/// - bins_length: u32 - number of bins
///
/// Returns
/// - u32 - the bin the ball was placed in
pub fn randomly_place_ball(bins: &mut Box<[u32]>, bins_length: u32) -> usize {
    let generate_random_integer = random::generate_random_unsigned_integer(0, bins_length - 1);
    bins[generate_random_integer as usize] += 1;

    return generate_random_integer as usize;
}
