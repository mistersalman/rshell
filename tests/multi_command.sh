# !/bin.bash

echo "starting single test"
cd ..
make
cd tests
../rshell.out < multiple.txt
echo "finished"
