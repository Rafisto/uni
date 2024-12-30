use rand::seq::SliceRandom;
use rand::thread_rng;
use std::fs::File;
use std::io::{self, Write};

const SIM_START_N: usize = 100;
const SIM_END_N: usize = 10_000;
const SIM_STEP: usize = 100;
const REPETITIONS: usize = 50;

#[derive(Debug, Default)]
struct Stats {
    comparisons: usize,
    swaps: usize,
}

fn insertion_sort(arr: &mut Vec<usize>, stats: &mut Stats) {
    let n = arr.len();
    for i in 1..n {
        let key = arr[i];
        let mut j = i;

        while j > 0 && arr[j - 1] > key {
            stats.comparisons += 1;
            arr[j] = arr[j - 1];
            j -= 1;
            stats.swaps += 1;
        }
        if j > 0 {
            stats.comparisons += 1;
        }
        arr[j] = key;
    }
}

fn generate_permutation(n: usize) -> Vec<usize> {
    let mut rng = thread_rng();
    let mut data: Vec<usize> = (1..=n).collect();
    data.shuffle(&mut rng);
    data
}

fn main() -> io::Result<()> {
    let mut file = File::create("insertion_sort_results.csv")?;
    writeln!(
        file,
        "n,rep,comparisons,swaps,cmp_n,cmp_n2,swaps_n,swaps_n2"
    )?;

    for n in (SIM_START_N..=SIM_END_N).step_by(SIM_STEP) {
        let mut avg_comparisons = 0;
        let mut avg_swaps = 0;

        for rep in 0..REPETITIONS {
            let mut data = generate_permutation(n);
            let mut stats = Stats::default();

            insertion_sort(&mut data, &mut stats);

            writeln!(
                file,
                "{},{},{},{},{},{},{},{}",
                n,
                rep + 1,
                stats.comparisons,
                stats.swaps,
                stats.comparisons as f64 / n as f64,
                stats.comparisons as f64 / (n as f64 * n as f64),
                stats.swaps as f64 / n as f64,
                stats.swaps as f64 / (n as f64 * n as f64)
            )?;

            avg_comparisons += stats.comparisons;
            avg_swaps += stats.swaps;
        }

        avg_comparisons /= REPETITIONS;
        avg_swaps /= REPETITIONS;

        println!(
            "n: {}, avg_comparisons: {}, avg_swaps: {}",
            n, avg_comparisons, avg_swaps
        );
    }

    Ok(())
}
