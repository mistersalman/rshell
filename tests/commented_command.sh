# !/bin.bash

echo "starting single test"
cd ..
make
cd tests
../bin/rshell < comment.txt 
cd ..
make clean
cd tests
echo "finished"
