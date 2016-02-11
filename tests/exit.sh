# !/bin.bash
# test exit

cd ..
make
cd tests
echo test strating
../bin/rshell < exit.txt
cd ..
make clean
cd tests
echo "finished"
