test_dir="../../ch9-1.1"
inputs_dir="${test_dir}"/inputs
results_dir="${test_dir}"/results
binary=radix_heap

echo "Radix Heap on Random4-n.21.0.gr, sources Random4-n.21.0.p2p, output to random4n_21.radix_heap"
./"${binary}" -d "${inputs_dir}"/Random4-n/Random4-n.21.0.gr -p2p "${inputs_dir}"/Random4-n/Random4-n.21.0.p2plohi -op2p "${results_dir}"/random4n_21.p2p.radix_heap.lohi
./"${binary}" -d "${inputs_dir}"/Random4-n/Random4-n.21.0.gr -p2p "${inputs_dir}"/Random4-n/Random4-n.21.0.p2prand -op2p "${results_dir}"/random4n_21.p2p.radix_heap.rand

echo "Radix Heap on Random4-C.15.0.gr, sources Random4-n.21.0.p2p, output to random4n_15.radix_heap"
./"${binary}" -d "${inputs_dir}"/Random4-C/Random4-C.15.0.gr -p2p "${inputs_dir}"/Random4-n/Random4-n.15.0.p2plohi -op2p "${results_dir}"/random4c_15.p2p.radix_heap.lohi
./"${binary}" -d "${inputs_dir}"/Random4-C/Random4-C.15.0.gr -p2p "${inputs_dir}"/Random4-n/Random4-n.15.0.p2prand -op2p "${results_dir}"/random4c_15.p2p.radix_heap.rand

echo "Radix Heap on Long-n.21.0.gr, sources Long-n.21.0.p2p, output to longn_21.radix_heap"
./"${binary}" -d "${inputs_dir}"/Long-n/Long-n.21.0.gr -p2p "${inputs_dir}"/Long-n/Long-n.21.0.p2plohi -op2p "${results_dir}"/longn_21.p2p.radix_heap.lohi
./"${binary}" -d "${inputs_dir}"/Long-n/Long-n.21.0.gr -p2p "${inputs_dir}"/Long-n/Long-n.21.0.p2prand -op2p "${results_dir}"/longn_21.p2p.radix_heap.rand

echo "Radix Heap on Long-C.15.0.gr, sources Long-C.15.0.p2p, output to longc_15.radix_heap"
./"${binary}" -d "${inputs_dir}"/Long-C/Long-C.15.0.gr -p2p "${inputs_dir}"/Long-C/Long-C.15.0.p2plohi -op2p "${results_dir}"/longc_15.p2p.radix_heap.lohi
./"${binary}" -d "${inputs_dir}"/Long-C/Long-C.15.0.gr -p2p "${inputs_dir}"/Long-C/Long-C.15.0.p2prand -op2p "${results_dir}"/longc_15.p2p.radix_heap.rand

echo "Radix Heap on Square-n.21.0.gr, sources Square-n.21.0.p2p, output to squaren_21.radix_heap"
./"${binary}" -d "${inputs_dir}"/Square-n/Square-n.21.0.gr -p2p "${inputs_dir}"/Square-n/Square-n.21.0.p2plohi -op2p "${results_dir}"/squaren_21.p2p.radix_heap.lohi
./"${binary}" -d "${inputs_dir}"/Square-n/Square-n.21.0.gr -p2p "${inputs_dir}"/Square-n/Square-n.21.0.p2prand -op2p "${results_dir}"/squaren_21.p2p.radix_heap.rand 

echo "Radix Heap on Square-C.15.0.gr, sources Square-C.15.0.p2p, output to squarec_15.radix_heap"
./"${binary}" -d "${inputs_dir}"/Square-C/Square-C.15.0.gr -p2p "${inputs_dir}"/Square-C/Square-C.15.0.p2plohi -op2p "${results_dir}"/squarec_15.p2p.radix_heap.lohi
./"${binary}" -d "${inputs_dir}"/Square-C/Square-C.15.0.gr -p2p "${inputs_dir}"/Square-C/Square-C.15.0.p2prand -op2p "${results_dir}"/squarec_15.p2p.radix_heap.rand

echo "All tests completed."
