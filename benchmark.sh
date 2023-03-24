#!/usr/bin/env bash

set -euo pipefail

N_ITERATIONS=10000

codon build codon-primes.py
codon build python-primes.py
clang++ --std=c++20 -O2 cpp-primes.cc -o cpp-primes
clang++ --std=c++20 -O2 cpp-para.cc -o cpp-para

echo "Codon Parallel"
hyperfine "./codon-primes $N_ITERATIONS" --export-markdown codon-par.md

echo "Codon Sequential"
hyperfine "./python-primes $N_ITERATIONS" --export-markdown codon-seq.md

echo "Python3"
hyperfine "python3 ./python-primes.py $N_ITERATIONS" --export-markdown py3.md

echo "Pypy"
hyperfine "pypy3 ./python-primes.py $N_ITERATIONS" --export-markdown pypy.md

echo "C++ Sequential"
hyperfine "./cpp-primes $N_ITERATIONS"  --export-markdown cpp-seq.md

echo "C++ Parallel"
hyperfine "./cpp-para $N_ITERATIONS"  --export-markdown cpp-para.md

rm codon-primes
rm cpp-para
rm cpp-primes
rm python-primes