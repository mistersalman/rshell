# !/bin.bash

echo "starting single test"
cd ..
make
cd tests
../rshell.out < comment.txt 
echo "finished"
