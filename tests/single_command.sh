# !/bin.bash

echo "starting single test"
cd ..
make
cd tests
../rshell.out < single.txt
cd ..
make clean
cd tests
echo "finished"
