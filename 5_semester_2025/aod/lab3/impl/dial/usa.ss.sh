test_dir="../../ch9-1.1"
inputs_dir="${test_dir}"/inputs
results_dir="${test_dir}"/results
binary=dial

echo "Dial on USA-road-d.USA.gr, sources USA-road-d.USA.ss, output to usa.dial"
./"${binary}" -d "${inputs_dir}"/USA-road-d/USA-road-d.USA.gr -ss "${inputs_dir}"/USA-road-d/test.ssm -oss "${results_dir}"/usa.dial.m
./"${binary}" -d "${inputs_dir}"/USA-road-d/USA-road-d.USA.gr -ss "${inputs_dir}"/USA-road-d/test.ssr -oss "${results_dir}"/usa.dial.r

for graph in USA-road-d.BAY.gr USA-road-d.COL.gr USA-road-d.E.gr USA-road-d.LKS.gr USA-road-d.NW.gr \
             USA-road-d.CAL.gr USA-road-d.CTR.gr USA-road-d.FLA.gr USA-road-d.NE.gr USA-road-d.NY.gr USA-road-d.W.gr; do
    ./"${binary}" -d "${inputs_dir}"/USA-road-d/"${graph}" -ss "${inputs_dir}"/USA-road-d/test.ssm -oss "${results_dir}"/"${graph}.dial.m"
    ./"${binary}" -d "${inputs_dir}"/USA-road-d/"${graph}" -ss "${inputs_dir}"/USA-road-d/test.ssr -oss "${results_dir}"/"${graph}.dial.r"
done


echo "All tests completed."
