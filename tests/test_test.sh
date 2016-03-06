# !/bin.bash

echo "starting test function test"
cd ..
make
cd tests
../bin/rshell < test_test.txt
cd ..
make clean
cd tests
echo "finished"
