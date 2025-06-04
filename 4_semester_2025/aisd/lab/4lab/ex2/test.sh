EXEC="test.out"
OUTPUT="output.txt"

if [ ! -f "${EXEC}" ]; then
  echo "Executable test.out not found. Please compile the code first."
  exit 1
fi
  
./${EXEC} | tee "${OUTPUT}" # print csv header
for N in {10000..100000..10000}; do
  for i in {1..20}; do
    ./${EXEC} $N | tee -a "${OUTPUT}"
  done
done