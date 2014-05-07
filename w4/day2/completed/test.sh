echo "tests 1"
./kplc ../tests/example1.kpl>../tests/out.txt; diff ../tests/out.txt ../tests/result1.txt 

echo "tests 2"
./kplc ../tests/example2.kpl>../tests/out.txt; diff ../tests/out.txt ../tests/result2.txt 

echo "tests 3"
./kplc ../tests/example3.kpl>../tests/out.txt; diff ../tests/out.txt ../tests/result3.txt 

echo "tests 4"
./kplc ../tests/example4.kpl>../tests/out.txt; diff ../tests/out.txt ../tests/result4.txt 

echo "tests 5"
./kplc ../tests/example5.kpl>../tests/out.txt; diff ../tests/out.txt ../tests/result5.txt 

echo "tests 6"
./kplc ../tests/example6.kpl>../tests/out.txt; diff ../tests/out.txt ../tests/result6.txt 