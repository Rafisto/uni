test_dir="../../ch9-1.1"
inputs_dir="${test_dir}"/inputs
results_dir="${test_dir}"/results
binary=dial

# for i in {0..11}; do
#     echo "Dial on Random4-C.$i.0.gr, sources Random4-C.$i.0.ss, output to random4c_$i.dial"
#     ./"${binary}" -d "${inputs_dir}"/Random4-C/Random4-C.$i.0.gr -ss "${inputs_dir}"/Random4-C/Random4-C.$i.0.ssr -oss "${results_dir}"/random4c_$i.dial.r
#     ./"${binary}" -d "${inputs_dir}"/Random4-C/Random4-C.$i.0.gr -ss "${inputs_dir}"/Random4-C/Random4-C.$i.0.ssm -oss "${results_dir}"/random4c_$i.dial.m
# done
# wait

# for i in {10..21}; do
#     echo "Dial on Random4-n.$i.0.gr, sources Random4-n.$i.0.ss, output to random4n_$i.dial"
#     ./"${binary}" -d "${inputs_dir}"/Random4-n/Random4-n.$i.0.gr -ss "${inputs_dir}"/Random4-n/Random4-n.$i.0.ssr -oss "${results_dir}"/random4n_$i.dial.r
#     ./"${binary}" -d "${inputs_dir}"/Random4-n/Random4-n.$i.0.gr -ss "${inputs_dir}"/Random4-n/Random4-n.$i.0.ssm -oss "${results_dir}"/random4n_$i.dial.m
# done
# wait

# for i in {0..11}; do
#     echo "Dial on Long-C.$i.0.gr, sources Long-C.$i.0.ss, output to longc_$i.dial"
#     ./"${binary}" -d "${inputs_dir}"/Long-C/Long-C.$i.0.gr -ss "${inputs_dir}"/Long-C/Long-C.$i.0.ssr -oss "${results_dir}"/longc_$i.dial.r
#     ./"${binary}" -d "${inputs_dir}"/Long-C/Long-C.$i.0.gr -ss "${inputs_dir}"/Long-C/Long-C.$i.0.ssm -oss "${results_dir}"/longc_$i.dial.m
# done
# wait

# for i in {10..21}; do
#     echo "Dial on Long-n.$i.0.gr, sources Long-n.$i.0.ss, output to longn_$i.dial"
#     ./"${binary}" -d "${inputs_dir}"/Long-n/Long-n.$i.0.gr -ss "${inputs_dir}"/Long-n/Long-n.$i.0.ssr -oss "${results_dir}"/longn_$i.dial.r
#     ./"${binary}" -d "${inputs_dir}"/Long-n/Long-n.$i.0.gr -ss "${inputs_dir}"/Long-n/Long-n.$i.0.ssm -oss "${results_dir}"/longn_$i.dial.m
# done
# wait

for i in {0..11}; do
    echo "Dial on Square-C.$i.0.gr, sources Square-C.$i.0.ss, output to squarec_$i.dial"
    ./"${binary}" -d "${inputs_dir}"/Square-C/Square-C.$i.0.gr -ss "${inputs_dir}"/Square-C/Square-C.$i.0.ssr -oss "${results_dir}"/squarec_$i.dial.r
    ./"${binary}" -d "${inputs_dir}"/Square-C/Square-C.$i.0.gr -ss "${inputs_dir}"/Square-C/Square-C.$i.0.ssm -oss "${results_dir}"/squarec_$i.dial.m
done
wait

for i in {10..21}; do
    echo "Dial on Square-n.$i.0.gr, sources Square-n.$i.0.ss, output to squaren_$i.dial"
    ./"${binary}" -d "${inputs_dir}"/Square-n/Square-n.$i.0.gr -ss "${inputs_dir}"/Square-n/Square-n.$i.0.ssr -oss "${results_dir}"/squaren_$i.dial.r
    ./"${binary}" -d "${inputs_dir}"/Square-n/Square-n.$i.0.gr -ss "${inputs_dir}"/Square-n/Square-n.$i.0.ssm -oss "${results_dir}"/squaren_$i.dial.m
done
wait

echo "All tests completed."
