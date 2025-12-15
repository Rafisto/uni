test_dir="../../ch9-1.1"
inputs_dir="${test_dir}"/inputs
results_dir="${test_dir}"/results
binary=dial

echo "Dial on USA-road-d.USA.gr, sources test.p2p, output to usa.p2p.dial"
./"${binary}" -d "${inputs_dir}"/USA-road-d/USA-road-d.USA.gr -p2p "${inputs_dir}"/USA-road-d/test.p2plohi -op2p "${results_dir}"/usa.p2p.diallohi
./"${binary}" -d "${inputs_dir}"/USA-road-d/USA-road-d.USA.gr -p2p "${inputs_dir}"/USA-road-d/test.p2prand -op2p "${results_dir}"/usa.p2p.dialrand

echo "All tests completed."
