# !/bin.bash

echo "starting multiple test"
cd ..
make
cd tests
../bin/rshell < multiple.txt
cd ..
make clean
cd tests
echo "finished"
