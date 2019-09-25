#!/bin/sh
# Requires (in PATH):
# GNU coreutils (echo, date)
# GNU Time (time)
# Clang LLVM (clang++)
echo -n "When: " > procedure_results.txt
date -u >> procedure_results.txt
echo -n "Compiler: " >> procedure_results.txt
clang++ --version >> procedure_results.txt
clang++ -std=c++14 -pedantic -Wall -O -o test_procedure test_procedure.cpp test_extern.cpp
clang++ -std=c++14 -pedantic -Wall -O -o test_stdfunction test_stdfunction.cpp test_extern.cpp
loops=10
while [ $loops -gt 0 ]
do
    echo "test_procedure:" >> procedure_results.txt
    time -p -a -o procedure_results.txt ./test_procedure > /dev/null
    echo "test_stdfunction:" >> procedure_results.txt
    time -p -a -o procedure_results.txt ./test_stdfunction > /dev/null
    loops=$[$loops - 1]
done
