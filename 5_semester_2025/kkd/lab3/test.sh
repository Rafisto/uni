file=$1

set -x

if [ -z "${file}" ]; then
    echo "$0 <input_file>"
    exit 1
fi

if [ ! -f "${file}" ]; then
    echo "not found: ${file}"
    exit 1
fi

python lzw.py encode "${file}" "${file}".gamma.out --coding gamma
python lzw.py decode "${file}".gamma.out "${file}".gamma.res --coding gamma
python lzw.py encode "${file}" "${file}".delta.out --coding delta
python lzw.py decode "${file}".delta.out "${file}".delta.res --coding delta
python lzw.py encode "${file}" "${file}".omega.out --coding omega
python lzw.py decode "${file}".omega.out "${file}".omega.res --coding omega
python lzw.py encode "${file}" "${file}".fib.out --coding fibonacci
python lzw.py decode "${file}".fib.out "${file}".fib.res --coding fibonacci

sha256sum "${file}" "${file}".gamma.res "${file}".delta.res  "${file}".omega.res "${file}".fib.res
ls -lah *.out *.res "${file}"

set +x