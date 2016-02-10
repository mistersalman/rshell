# !/bin.bash

echo "starting single test"
cd ..
make
cd tests
../rshell.out < single.txt
echo "finished"
