/// Metrics for the balls and bins problem
///
/// Attributes
/// - b_factor: u32 - first collision (B_factor = k if the first collision occurs on k-th ball, see birthday paradox)
/// - u_factor: u32 - number of empty bins after all balls are placed
/// - c_factor: u32 - first all bins collision (C_factor = k if all bins have at least one ball after k-th ball is placed, coupon collector problem)
/// - d_factor: u32 - first double collision (D_factor = k if the first bin has two balls after k-th ball is placed, siblings of the coupon collector problem)
/// - m_factor: u32 - maximum number of balls in a bin after all n balls are placed
#[derive(Clone)]
pub struct Metrics {
    pub b_factor: u32,
    pub u_factor: u32,
    pub c_factor: u32,
    pub d_factor: u32,
    pub r_factor: u32,
    pub m_factor: u32,
}

impl Metrics {
    pub fn new() -> Self {
        Metrics {
            b_factor: 0,
            u_factor: 0,
            c_factor: 0,
            d_factor: 0,
            r_factor: 0,
            m_factor: 0,
        }
    }
}

pub struct AveragedMetrics {
    pub b_factor: f64,
    pub u_factor: f64,
    pub c_factor: f64,
    pub d_factor: f64,
    pub r_factor: f64,
    pub m_factor: f64,
}

impl AveragedMetrics {
    pub fn new() -> Self {
        AveragedMetrics {
            b_factor: 0.0,
            u_factor: 0.0,
            c_factor: 0.0,
            d_factor: 0.0,
            r_factor: 0.0,
            m_factor: 0.0,
        }
    }
}

/// Average over the metrics
/// Take a vector of metrics and average them returning a new AveragedMetrics struct
///
/// Arguments
/// - metrics: Vec<Metrics> - vector of metrics to average
pub fn average_over_metrics(metrics: Vec<Metrics>, n: u32) -> AveragedMetrics {
    let mut average_metrics: AveragedMetrics = AveragedMetrics::new();
    let mut b_factor_sum: u64 = 0;
    let mut u_factor_sum: u64 = 0;
    let mut c_factor_sum: u64 = 0;
    let mut d_factor_sum: u64 = 0;
    let mut r_factor_sum: u64 = 0; 
    let mut m_factor_sum: u64 = 0;

    for metric in metrics {
        b_factor_sum += metric.b_factor as u64;
        u_factor_sum += metric.u_factor as u64;
        c_factor_sum += metric.c_factor as u64;
        d_factor_sum += metric.d_factor as u64;
        r_factor_sum += metric.r_factor as u64;
        m_factor_sum += metric.m_factor as u64;
    }

    average_metrics.b_factor = b_factor_sum as f64 / n as f64;
    average_metrics.u_factor = u_factor_sum as f64 / n as f64;
    average_metrics.c_factor = c_factor_sum as f64 / n as f64;
    average_metrics.d_factor = d_factor_sum as f64 / n as f64;
    average_metrics.r_factor = r_factor_sum as f64 / n as f64;
    average_metrics.m_factor = m_factor_sum as f64 / n as f64;

    return average_metrics;
}