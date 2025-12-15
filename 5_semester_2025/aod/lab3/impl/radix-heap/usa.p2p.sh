test_dir="../../ch9-1.1"
inputs_dir="${test_dir}"/inputs
results_dir="${test_dir}"/results
binary=radix_heap

echo "Radix Heap on USA-road-d.USA.gr, sources test.p2p, output to usa.p2p.radix_heap"
./"${binary}" -d "${inputs_dir}"/USA-road-d/USA-road-d.USA.gr -p2p "${inputs_dir}"/USA-road-d/test.p2plohi -op2p "${results_dir}"/usa.p2p.radix_heaplohi
./"${binary}" -d "${inputs_dir}"/USA-road-d/USA-road-d.USA.gr -p2p "${inputs_dir}"/USA-road-d/test.p2prand -op2p "${results_dir}"/usa.p2p.radix_heaprand

echo "All tests completed."
