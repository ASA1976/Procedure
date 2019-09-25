#!/bin/sh
# Requires (in PATH):
# GNU coreutils (echo, date)
# GNU Time (time)
# Clang LLVM (clang++)
echo -n "When: " > comparable_results.txt
date -u >> comparable_results.txt
echo -n "Compiler: " >> comparable_results.txt
clang++ --version >> comparable_results.txt
clang++ -std=c++14 -pedantic -Wall -O -o test_comparable test_comparable.cpp test_extern.cpp
clang++ -std=c++14 -pedantic -Wall -O -o test_stdfunction test_stdfunction.cpp test_extern.cpp
loops=10
while [ $loops -gt 0 ]
do
    echo "test_comparable:" >> comparable_results.txt
    time -p -a -o comparable_results.txt ./test_comparable > /dev/null
    echo "test_stdfunction:" >> comparable_results.txt
    time -p -a -o comparable_results.txt ./test_stdfunction > /dev/null
    loops=$[$loops - 1]
done
