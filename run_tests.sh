#!/bin/sh
echo -n "Compiler: " > test_results.txt
clang++ --version >> test_results.txt
clang++ -pedantic -Wall -O -o test_procedure test_procedure.cpp test_extern.cpp
clang++ -pedantic -Wall -O -o test_stdfunction test_stdfunction.cpp test_extern.cpp
loops=10
while [ $loops -gt 0 ]
do
    echo "test_procedure:" >> test_results.txt
    time -p -a -o test_results.txt ./test_procedure > /dev/null
    echo "test_stdfunction:" >> test_results.txt
    time -p -a -o test_results.txt ./test_stdfunction > /dev/null
    loops=$[$loops - 1]
done
