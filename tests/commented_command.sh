# !/bin.bash

echo "starting commented test"
cd ..
make
cd tests
../bin/rshell < comment.txt 
cd ..
make clean
cd tests
echo "finished"
