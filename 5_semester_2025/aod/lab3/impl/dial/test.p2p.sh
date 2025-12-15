test_dir="../../ch9-1.1"
inputs_dir="${test_dir}"/inputs
results_dir="${test_dir}"/results
binary=dial

echo "Dial on Random4-n.21.0.gr, sources Random4-n.21.0.p2p, output to random4n_21.dial"
./"${binary}" -d "${inputs_dir}"/Random4-n/Random4-n.21.0.gr -p2p "${inputs_dir}"/Random4-n/Random4-n.21.0.p2plohi -op2p "${results_dir}"/random4n_21.p2p.dial.lohi
./"${binary}" -d "${inputs_dir}"/Random4-n/Random4-n.21.0.gr -p2p "${inputs_dir}"/Random4-n/Random4-n.21.0.p2prand -op2p "${results_dir}"/random4n_21.p2p.dial.rand

echo "Dial on Random4-C.10.0.gr, sources Random4-n.10.0.p2p, output to random4n_10.dial"
./"${binary}" -d "${inputs_dir}"/Random4-C/Random4-C.10.0.gr -p2p "${inputs_dir}"/Random4-C/Random4-C.0.0.10.p2plohi -op2p "${results_dir}"/random4c_10.p2p.dial.lohi
./"${binary}" -d "${inputs_dir}"/Random4-C/Random4-C.10.0.gr -p2p "${inputs_dir}"/Random4-C/Random4-C.0.0.10.p2prand -op2p "${results_dir}"/random4c_10.p2p.dial.rand

echo "Dial on Long-n.21.0.gr, sources Long-n.21.0.p2p, output to longn_21.dial"
./"${binary}" -d "${inputs_dir}"/Long-n/Long-n.21.0.gr -p2p "${inputs_dir}"/Long-n/Long-n.21.0.p2plohi -op2p "${results_dir}"/longn_21.p2p.dial.lohi
./"${binary}" -d "${inputs_dir}"/Long-n/Long-n.21.0.gr -p2p "${inputs_dir}"/Long-n/Long-n.21.0.p2prand -op2p "${results_dir}"/longn_21.p2p.dial.rand

echo "Dial on Long-C.10.0.gr, sources Long-C.10.0.p2p, output to longc_10.dial"
./"${binary}" -d "${inputs_dir}"/Long-C/Long-C.10.0.gr -p2p "${inputs_dir}"/Long-C/Long-C.0.0.10.p2plohi -op2p "${results_dir}"/longc_10.p2p.dial.lohi
./"${binary}" -d "${inputs_dir}"/Long-C/Long-C.10.0.gr -p2p "${inputs_dir}"/Long-C/Long-C.0.0.10.p2prand -op2p "${results_dir}"/longc_10.p2p.dial.rand

echo "Dial on Square-n.21.0.gr, sources Square-n.21.0.p2p, output to squaren_21.dial"
./"${binary}" -d "${inputs_dir}"/Square-n/Square-n.21.0.gr -p2p "${inputs_dir}"/Square-n/Square-n.21.0.p2plohi -op2p "${results_dir}"/squaren_21.p2p.dial.lohi
./"${binary}" -d "${inputs_dir}"/Square-n/Square-n.21.0.gr -p2p "${inputs_dir}"/Square-n/Square-n.21.0.p2prand -op2p "${results_dir}"/squaren_21.p2p.dial.rand 

echo "Dial on Square-C.10.0.gr, sources Square-C.10.0.p2p, output to squarec_10.dial"
./"${binary}" -d "${inputs_dir}"/Square-C/Square-C.10.0.gr -p2p "${inputs_dir}"/Square-C/Square-C.0.0.10.p2plohi -op2p "${results_dir}"/squarec_10.p2p.dial.lohi
./"${binary}" -d "${inputs_dir}"/Square-C/Square-C.10.0.gr -p2p "${inputs_dir}"/Square-C/Square-C.0.0.10.p2prand -op2p "${results_dir}"/squarec_10.p2p.dial.rand

echo "All tests completed."
