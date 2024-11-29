// mpis_hwk_2
// Rafal Wlodarczyk
// This program is used to simulate various balls and bins problems

use std::fs::File;
use std::io::{self, Write};

mod random;
mod simulation;
mod types;

const SIM_GROUP_START_N: u32 = 1000;
const SIM_GROUP_END_N: u32 = 100_000;
const SIM_GROUP_STEP_N: usize = 1000;

const SAME_SIM_REPS: usize = 50;

use rayon::prelude::*; // For parallelization

fn main() -> io::Result<()> {
    let sim_params: Vec<u32> = (SIM_GROUP_START_N..SIM_GROUP_END_N + 1)
        .step_by(SIM_GROUP_STEP_N)
        .collect();

    let mut file = File::create("results.csv")?;
    writeln!(file, "n,b_factor,u_factor,c_factor,d_factor,r_factor")?;

    let mut singular_file = File::create("results_intermediate.csv")?;
    writeln!(singular_file, "n,rep,b_factor,u_factor,c_factor,d_factor,r_factor")?;

    for n in sim_params {
        // Use parallel iteration for simulation reps
        let metrics_group: Vec<types::Metrics> = (0..SAME_SIM_REPS)
            .into_par_iter()
            .map(|_k| {
                let mut bins = simulation::create_bins(n);
                let mut metrics = types::Metrics::new();
                let mut count_0: u32 = n; // To count occurrences of 0
                let mut count_1: u32 = 0; // To count occurrences of 1
                let mut count_2: u32 = 0; // To count occurrences of 2

                let mut i = 0;
                while count_2 != n || count_1 != n {
                    let selected = simulation::randomly_place_ball(&mut bins, n);

                    match bins[selected] {
                        1 => {
                            count_1 += 1;
                            count_0 -= 1;
                        }
                        2 => count_2 += 1,
                        _ => {}
                    }

                    // Set metrics once conditions are met
                    if metrics.b_factor == 0 && bins[selected] == 2 {
                        metrics.b_factor = i;
                    }

                    if count_1 == n && metrics.c_factor == 0 {
                        metrics.c_factor = i;
                    }

                    if count_2 == n && metrics.d_factor == 0 {
                        metrics.d_factor = i;
                    }

                    if i == n - 1 {
                        metrics.u_factor = count_0;
                    }

                    // Early exit if all factors are found
                    if metrics.b_factor != 0 && metrics.c_factor != 0 && metrics.d_factor != 0 {
                        break;
                    }

                    i += 1;
                }

                metrics.r_factor = metrics.d_factor - metrics.c_factor;

                metrics
            })
            .collect();

        let averaged_metrics = types::average_over_metrics(metrics_group.clone(), SAME_SIM_REPS as u32);

        // Write averaged metrics to results.csv

        writeln!(
            file,
            "{},{},{},{},{},{}",
            n,
            averaged_metrics.b_factor,
            averaged_metrics.u_factor,
            averaged_metrics.c_factor,
            averaged_metrics.d_factor,
            averaged_metrics.r_factor
        )?;

        // Write all metrics to results_singular.csv
        for (i, metrics) in metrics_group.iter().enumerate() {
            writeln!(
                singular_file,
                "{},{},{},{},{},{},{}",
                n,
                i,
                metrics.b_factor,
                metrics.u_factor,
                metrics.c_factor,
                metrics.d_factor,
                metrics.r_factor
            )?;
        }
    }

    Ok(())
}