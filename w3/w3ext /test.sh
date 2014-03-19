echo "Test 1"
./parser example1.kpl>out.txt ; diff out.txt result1.txt 

echo "Test 2"
./parser example2.kpl>out.txt ; diff out.txt result2.txt 

echo "Test 3"
./parser example3.kpl>out.txt ; diff out.txt result3.txt 

echo "Test 4"
./parser example4.kpl>out.txt ; diff out.txt result4.txt 

echo "Test 5"
./parser example5.kpl>out.txt ; diff out.txt result5.txt 

echo "Test 6"
./parser example6.kpl>out.txt ; diff out.txt result6.txt 

echo "Test 7"
./parser example7.kpl>out.txt ; diff out.txt result7.txt 
